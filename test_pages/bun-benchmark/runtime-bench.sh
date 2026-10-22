#!/usr/bin/env bash
# node · deno · bun 런타임 성능 벤치마크 → runtime-results.json
# 요구: node, deno, bun, hyperfine, oha, jq, curl
# 환경변수: HTTP_SECS=<HTTP 부하 시간(초)>(기본 10), CONNS=<동시 연결 수>(기본 64), PORT(기본 3456)
set -euo pipefail

HERE=$(cd "$(dirname "$0")" && pwd)
W=$HERE
TMP=${BENCH_TMP:-${TMPDIR:-/tmp}/runtime-benchmark}
HTTP_SECS=${HTTP_SECS:-10}
CONNS=${CONNS:-64}
PORT=${PORT:-3456}
WORKLOADS="runtime-startup.js runtime-startup-ts.ts runtime-fib.js runtime-json.js runtime-sort.js runtime-crypto.js runtime-fs.js"
mkdir -p "$TMP"
cd "$HERE" # 상위 package.json 의 "type": "module" 을 읽도록

# 런타임 실행 명령. 함수로 감싸 실행하면 `&` 의 $! 가 서브셸 PID 가 되므로 명령 문자열만 돌려준다
cmd() { if [[ $1 == deno ]]; then echo "deno run -A"; else echo "$1"; fi; }

# 띄운 HTTP 서버는 어떤 이유로 끝나든(set -e, Ctrl-C) 정리한다.
# Ctrl-C 를 받은 oha 는 그때까지의 결과로 exit 0 하므로, INT 를 받으면 잘린 결과를 기록하지 않고 바로 끝낸다
pid=
trap '[[ -z $pid ]] || kill "$pid" 2>/dev/null || true' EXIT
trap 'exit 130' INT TERM

# 0) 측정 환경: 측정을 다 돌린 뒤에 실패하지 않도록 먼저 모은다
os=$(sw_vers -productVersion 2>/dev/null | sed 's/^/macOS /' || uname -sr)
cpu=$(sysctl -n machdep.cpu.brand_string 2>/dev/null || grep -m1 'model name' /proc/cpuinfo | cut -d: -f2- || true)
cpu=${cpu:-$(uname -m)} # aarch64 Linux 의 /proc/cpuinfo 에는 model name 이 없다
jq -n \
    --arg date "$(date -u +%FT%TZ)" --arg os "$os ($(uname -m))" --arg cpu "${cpu# }" \
    --argjson cores "$(getconf _NPROCESSORS_ONLN)" --arg commit "$(git -C "$HERE" rev-parse --short HEAD)" \
    --arg node "$(node --version)" --arg deno "$(deno eval 'console.log(Deno.version.deno)')" \
    --arg bun "$(bun --revision)" \
    --arg nodeEngine "V8 $(node -p 'process.versions.v8')" \
    --arg denoEngine "V8 $(deno eval 'console.log(Deno.version.v8)')" \
    --arg bunEngine "JavaScriptCore $(bun -p 'process.versions.webkit.slice(0, 8)')" \
    '{$date, $os, $cpu, $cores, $commit,
      versions: {$node, $deno, $bun},
      engines: {node: $nodeEngine, deno: $denoEngine, bun: $bunEngine}}' >"$TMP/meta.json"

# 1) 출력 일치: 세 런타임이 같은 결과를 내는지 먼저 확인
for f in $WORKLOADS; do
    want=$(node "$W/$f")
    for rt in deno bun; do
        got=$($(cmd "$rt") "$W/$f")
        [[ $got == "$want" ]] || {
            echo "$f: $rt 출력 불일치 ($got ≠ $want)" >&2
            exit 1
        }
    done
done

# 2) 프로세스 단위 실행 시간 · 피크 메모리 (시작 시간 포함)
#   hyperfine 의 메모리는 자식 프로세스 누적 최댓값(RUSAGE_CHILDREN)이라
#   한 번에 여러 런타임을 재면 앞 런타임의 RSS 가 뒤로 이어진다 → 런타임마다 따로 실행
for f in $WORKLOADS; do
    w=1 r=10
    [[ $f == startup* ]] && w=3 r=30
    for rt in node deno bun; do
        name=${f#runtime-}
        name=${name%.*}
        hyperfine -N -w "$w" -r "$r" -n "$rt" "$(cmd "$rt") $W/$f" \
            --export-json "$TMP/$name-$rt.json"
    done
done

# 3) HTTP 처리량: 런타임 기본 API(Bun.serve · Deno.serve · node:http) 와 node:http 호환 레이어
#   node 의 기본 API 가 node:http 라 node 는 한 번만 잰다
url=http://127.0.0.1:$PORT/
: >"$TMP/http.jsonl"
for target in node:node:node:http deno:native:Deno.serve bun:native:Bun.serve deno:node:node:http bun:node:node:http; do
    rt=${target%%:*}
    rest=${target#*:}
    mode=${rest%%:*}
    api=${rest#*:}
    # 상태 코드와 관계없이 응답이 오면 다른 프로세스가 포트를 쓰는 중
    if curl -s -o /dev/null "$url"; then
        echo "포트 $PORT 를 이미 다른 프로세스가 쓰고 있음" >&2
        exit 1
    fi
    HTTP_API=$mode PORT=$PORT $(cmd "$rt") "$W/runtime-serve.js" &
    pid=$!
    for _ in $(seq 100); do
        curl -fs -o /dev/null "$url" && break
        sleep 0.1
    done
    curl -fs -o /dev/null "$url" || {
        echo "$rt ($api) 서버가 10초 안에 정상 응답하지 않음" >&2
        exit 1
    }
    oha -z 2s -c "$CONNS" --no-tui --output-format quiet "$url" # 워밍업
    oha -z "${HTTP_SECS}s" -c "$CONNS" --no-tui --output-format json "$url" >"$TMP/http.json"
    # oha 의 successRate 는 연결 수준이라 500 응답도 성공으로 센다 → 상태 코드를 따로 확인
    jq -e '.statusCodeDistribution | keys == ["200"]' "$TMP/http.json" >/dev/null || {
        echo "$rt ($api) 200 이 아닌 응답: $(jq -c .statusCodeDistribution "$TMP/http.json")" >&2
        exit 1
    }
    rss=$(ps -o rss= -p "$pid")
    kill "$pid"
    wait "$pid" 2>/dev/null || true
    pid=
    jq -c --arg tool "$rt" --arg api "$api" --argjson rss "$rss" \
        '{$tool, $api, rps: .summary.requestsPerSec, successRate: .summary.successRate,
          p50: .latencyPercentiles.p50, p99: .latencyPercentiles.p99, memory: ($rss * 1024)}' \
        "$TMP/http.json" >>"$TMP/http.jsonl"
done

# 4) runtime-results.json
#   memory_usage_byte 는 hyperfine 한 번 안에서 누적 최댓값(워밍업 포함)이라 평균이 아닌 최댓값을 쓴다
for f in $WORKLOADS; do
    name=${f#runtime-}
    name=${name%.*}
    jq -sc --arg name "$name" 'map(.results[0]) | {$name, runs: (.[0].times | length),
      results: map({tool: .command, mean, stddev, min, max, user, system,
        memory: (.memory_usage_byte | max)})}' "$TMP/$name"-{node,deno,bun}.json
done >"$TMP/workloads.jsonl"

jq -n \
    --argjson secs "$HTTP_SECS" --argjson conns "$CONNS" --slurpfile meta "$TMP/meta.json" \
    --slurpfile workloads "$TMP/workloads.jsonl" --slurpfile http "$TMP/http.jsonl" \
    '{meta: $meta[0], $workloads, http: {$secs, $conns, results: $http}}' >"$HERE/runtime-results.json"

echo "→ $HERE/runtime-results.json"
