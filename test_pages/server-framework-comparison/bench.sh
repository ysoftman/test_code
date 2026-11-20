#!/usr/bin/env bash
# JS/TS 서버 프레임워크 HTTP 처리량 벤치마크 → results.json
# 요구: node, bun, oha, jq, curl (macOS)
# 환경변수: HTTP_SECS=<시나리오별 부하 시간(초)>(기본 10), CONNS=<동시 연결 수>(기본 64), PORT(기본 3456)
set -euo pipefail

HERE=$(cd "$(dirname "$0")" && pwd)
HTTP_SECS=${HTTP_SECS:-10}
CONNS=${CONNS:-64}
PORT=${PORT:-3456}
BASE=http://127.0.0.1:$PORT
TMP=$(mktemp -d)
cd "$HERE"

for tool in node bun oha jq curl; do
    command -v "$tool" >/dev/null || {
        echo "$tool 이(가) 없음" >&2
        exit 1
    }
done

SCENARIOS='[
  {"id": "plaintext", "path": "/", "expect": "Hello World", "description": "GET / → 평문 Hello World"},
  {"id": "json", "path": "/json", "expect": "{\"message\":\"Hello World\"}", "description": "GET /json → 작은 JSON 객체"},
  {"id": "param", "path": "/user/123", "expect": "{\"id\":\"123\"}", "description": "GET /user/:id → 경로 파라미터를 JSON 으로 반환"}
]'

# 런타임:서버 파일:표시 이름:npm 패키지(없으면 런타임 내장)
COMBOS="
node:server-node-http.js:node:http:
node:server-express.js:Express:express
node:server-fastify.js:Fastify:fastify
node:server-koa.js:Koa:koa
node:server-hono.js:Hono:hono
bun:server-bun-serve.js:Bun.serve:
bun:server-hono.js:Hono:hono
bun:server-elysia.js:Elysia:elysia
bun:server-express.js:Express:express
bun:server-fastify.js:Fastify:fastify
bun:server-koa.js:Koa:koa
"

# 띄운 서버는 어떤 이유로 끝나든(set -e, Ctrl-C) 정리한다.
# Ctrl-C 를 받은 oha 는 그때까지의 결과로 exit 0 하므로, INT 를 받으면 잘린 결과를 기록하지 않고 바로 끝낸다
pid=
trap '[[ -z $pid ]] || kill "$pid" 2>/dev/null || true; rm -rf "$TMP"' EXIT
trap 'exit 130' INT TERM

pkgver() { jq -r .version "node_modules/$1/package.json"; }

# 서버 하나를 검증·측정해 $TMP/<시나리오>.json 과 rss 를 남긴다. 실패하면 reason 에 이유를 담고 1 을 돌려준다
measure() {
    local rt=$1 file=$2 id path want got
    # 상태 코드와 관계없이 응답이 오면 다른 프로세스가 포트를 쓰는 중
    if curl -s -o /dev/null "$BASE/"; then
        echo "포트 $PORT 를 이미 다른 프로세스가 쓰고 있음" >&2
        exit 1
    fi
    NODE_ENV=production PORT=$PORT "$rt" "$file" >/dev/null &
    pid=$!
    for _ in $(seq 100); do
        curl -fs -o /dev/null "$BASE/" && break
        sleep 0.1
    done
    curl -fs -o /dev/null "$BASE/" || {
        reason="서버가 10초 안에 정상 응답하지 않음"
        return 1
    }
    # 응답 본문·상태 코드가 기대값과 같은지 먼저 확인
    while IFS=$'\t' read -r id path want <&3; do
        got=$(curl -s -w '\n%{http_code}' "$BASE$path")
        [[ $got == "$want"$'\n200' ]] || {
            reason="$path 응답 불일치: ${got//$'\n'/ }"
            return 1
        }
    done 3< <(jq -r '.[] | [.id, .path, .expect] | @tsv' <<<"$SCENARIOS")
    while IFS=$'\t' read -r id path <&3; do
        oha -z 2s -c "$CONNS" --no-tui --output-format quiet "$BASE$path" # 워밍업
        oha -z "${HTTP_SECS}s" -c "$CONNS" --no-tui --output-format json "$BASE$path" >"$TMP/oha.json"
        # oha 의 successRate 는 연결 수준이라 500 응답도 성공으로 센다 → 상태 코드를 따로 확인
        jq -e '.statusCodeDistribution | keys == ["200"]' "$TMP/oha.json" >/dev/null || {
            reason="$path 부하 중 200 이 아닌 응답: $(jq -c .statusCodeDistribution "$TMP/oha.json")"
            return 1
        }
        jq -c --arg id "$id" 'def r3: (. * 1000 | round) / 1000;
          {($id): {rps: (.summary.requestsPerSec | round), avgMs: (.summary.average * 1000 | r3),
            p50Ms: (.latencyPercentiles.p50 * 1000 | r3), p99Ms: (.latencyPercentiles.p99 * 1000 | r3),
            successRate: .summary.successRate}}' "$TMP/oha.json" >"$TMP/scenario-$id.json"
    done 3< <(jq -r '.[] | [.id, .path] | @tsv' <<<"$SCENARIOS")
    rss=$(ps -o rss= -p "$pid")
}

: >"$TMP/results.jsonl"
: >"$TMP/excluded.jsonl"
for combo in $COMBOS; do
    rt=${combo%%:*}
    rest=${combo#*:}
    file=${rest%%:*}
    rest=${rest#*:}
    name=${rest%:*}
    pkg=${rest##*:}
    if [[ -n $pkg ]]; then version=$(pkgver "$pkg"); else version=$("$rt" --version); fi
    version=${version#v}
    echo "== $name ($rt)" >&2
    rm -f "$TMP"/scenario-*.json
    reason=
    if measure "$rt" "$file"; then
        jq -sc --arg framework "$name" --arg runtime "$rt" --arg version "$version" --argjson rss "$rss" \
            '{$framework, $runtime, $version} + add + {rssMb: ($rss / 1024 * 10 | round / 10)}' \
            "$TMP"/scenario-*.json >>"$TMP/results.jsonl"
    else
        echo "제외: $reason" >&2
        jq -nc --arg framework "$name" --arg runtime "$rt" --arg version "$version" --arg reason "$reason" \
            '{$framework, $runtime, $version, $reason}' >>"$TMP/excluded.jsonl"
    fi
    if [[ -n $pid ]]; then
        kill "$pid" 2>/dev/null || true
        wait "$pid" 2>/dev/null || true
        pid=
    fi
done

jq -n --tab \
    --arg date "$(date -u +%FT%TZ)" --arg os "macOS $(sw_vers -productVersion) ($(uname -m))" \
    --arg cpu "$(sysctl -n machdep.cpu.brand_string)" --argjson cores "$(getconf _NPROCESSORS_ONLN)" \
    --argjson memBytes "$(sysctl -n hw.memsize)" \
    --arg node "$(node --version)" --arg bun "$(bun --version)" --arg oha "$(oha --version)" \
    --argjson httpSecs "$HTTP_SECS" --argjson conns "$CONNS" \
    --argjson scenarios "$SCENARIOS" --slurpfile results "$TMP/results.jsonl" --slurpfile excluded "$TMP/excluded.jsonl" \
    --arg express "$(pkgver express)" --arg fastify "$(pkgver fastify)" --arg koa "$(pkgver koa)" \
    --arg koaRouter "$(pkgver @koa/router)" --arg hono "$(pkgver hono)" \
    --arg honoNodeServer "$(pkgver @hono/node-server)" --arg elysia "$(pkgver elysia)" \
    '{env: {$date, $os, $cpu, $cores, memoryGb: ($memBytes / 1073741824), node: $node[1:], $bun, oha: $oha[4:],
        $httpSecs, $conns,
        packages: {$express, $fastify, $koa, "@koa/router": $koaRouter, $hono,
          "@hono/node-server": $honoNodeServer, $elysia}},
      scenarios: ($scenarios | map(del(.expect))), $results, $excluded}' >results.json

echo "→ $HERE/results.json"
