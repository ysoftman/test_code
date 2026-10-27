#!/usr/bin/env bash
# jest · vitest · node --test · deno test · bun test 테스트 러너 속도 벤치마크 → test-results.json
# 요구: bun, node, deno, hyperfine, jq
# 환경변수: BUN=<bun 바이너리>(기본: PATH 의 bun), FILES=<suite 테스트 파일 수>(기본 200), TESTS=<파일당 테스트 수>(기본 20)
set -euo pipefail

HERE=$(cd "$(dirname "$0")" && pwd)
# repo 밖에서 돌린다 — 러너가 상위 package.json · 설정 파일을 읽지 않도록
TMP=${BENCH_TMP:-${TMPDIR:-/tmp}/test-benchmark}
FILES=${FILES:-200}
TESTS=${TESTS:-20}
BUN=${BUN:-bun}
JEST=$HERE/node_modules/.bin/jest
VITEST=$HERE/node_modules/.bin/vitest
RUNNERS="jest vitest node deno bun"
export NO_COLOR=1 # 통과 수를 출력에서 읽으므로 색 코드를 끈다
mkdir -p "$TMP"

[[ -x $VITEST ]] || (cd "$HERE" && bun install)

# 1) 코퍼스: 같은 TS 모듈과 테스트를 러너마다 import 한 줄만 바꿔 만든다
#   single = 테스트 파일 1개, suite = FILES 개. 파일마다 src 모듈 하나를 import 한다
cat >"$TMP/mod.ts" <<'EOF'
export interface Item {
  id: number;
  name: string;
  tags: string[];
}

export const sum = (xs: number[]): number => xs.reduce((a, b) => a + b, 0);

export const slugify = (s: string): string =>
  s.trim().toLowerCase().replace(/[^a-z0-9]+/g, "-").replace(/^-|-$/g, "");

export function groupBy<T>(xs: T[], key: (x: T) => string): Record<string, T[]> {
  const out: Record<string, T[]> = {};
  for (const x of xs) (out[key(x)] ??= []).push(x);
  return out;
}

export async function fetchItem(id: number): Promise<Item> {
  await Promise.resolve();
  return { id, name: `item-${id}`, tags: ["a", "b"] };
}

export function parse(json: string): unknown {
  return JSON.parse(json);
}
EOF
for k in $(seq "$TESTS"); do
    case $((k % 5)) in
        1) echo "test(\"sum $k\", () => { expect(sum([1, 2, 3, $k])).toBe($((6 + k))); });" ;;
        2) echo "test(\"slugify $k\", () => { expect(slugify(\" Hello World $k \")).toBe(\"hello-world-$k\"); });" ;;
        3) echo "test(\"groupBy $k\", () => { expect(groupBy([{ t: \"a\", v: $k }, { t: \"b\", v: 1 }, { t: \"a\", v: 2 }], (x) => x.t)).toEqual({ a: [{ t: \"a\", v: $k }, { t: \"a\", v: 2 }], b: [{ t: \"b\", v: 1 }] }); });" ;;
        4) echo "test(\"fetchItem $k\", async () => { await expect(fetchItem($k)).resolves.toEqual({ id: $k, name: \"item-$k\", tags: [\"a\", \"b\"] }); });" ;;
        0) echo "test(\"parse $k\", () => { expect(() => parse(\"{$k\")).toThrow(SyntaxError); });" ;;
    esac
done >"$TMP/body.ts"

header() { # 러너별 test · expect import. expect 는 러너 자체 것을 쓰고, 없는 node 만 jest 의 npm expect
    case $1 in
        bun) echo 'import { expect, test } from "bun:test";' ;;
        vitest) echo 'import { expect, test } from "vitest";' ;;
        jest) ;; # jest 는 test · expect 를 전역으로 주입한다
        node) printf '%s\n' 'import { test } from "node:test";' 'import { expect } from "expect";' ;;
        deno) printf '%s\n' 'import { test } from "node:test";' 'import { expect } from "jsr:@std/expect@1.0.20";' ;;
    esac
}

C=$TMP/corpus
rm -rf "$C"
for d in single suite; do
    n=$FILES
    [[ $d == single ]] && n=1
    for r in $RUNNERS; do
        w=$C/$d/$r
        mkdir -p "$w/src" "$w/test"
        echo '{ "type": "module" }' >"$w/package.json"
        ln -s "$HERE/node_modules" "$w/node_modules"
        for i in $(seq -w 1 "$n"); do
            cp "$TMP/mod.ts" "$w/src/m$i.ts"
            {
                header "$r"
                echo "import { fetchItem, groupBy, parse, slugify, sum } from \"../src/m$i.ts\";"
                cat "$TMP/body.ts"
            } >"$w/test/m$i.test.ts"
        done
    done
    # jest 는 TS 를 직접 못 읽는다 → 흔히 쓰는 변환기 중 가장 빠른 @swc/jest
    echo '{ "transform": { "\\.ts$": "@swc/jest" } }' >"$C/$d/jest/jest.config.json"
done

# 2) 측정 명령: 기본 설정 그대로. 파일을 직렬로 도는 deno · bun 은 병렬 옵션도 함께 잰다
#   deno test 는 기본으로 타입 검사를 하므로 다른 러너와 맞춰 --no-check
names=(jest vitest node deno deno-parallel bun bun-parallel)
cmds=(
    "$JEST"
    "$VITEST run"
    "node --test"
    "deno test --no-check"
    "deno test --no-check --parallel"
    "$BUN test"
    "$BUN test --parallel"
)

# 3) 통과 수 확인: 모든 러너가 모든 테스트를 실제로 돌렸는지 먼저 본다
#   출력의 "N pass…" · "pass N" 중 가장 큰 수 = 테스트 수 (파일 · suite 수는 그보다 작다)
for d in single suite; do
    n=$FILES
    [[ $d == single ]] && n=1
    for i in "${!names[@]}"; do
        dir=$C/$d/${names[i]%-parallel}
        out=$(cd "$dir" && ${cmds[i]} 2>&1) || {
            echo "$d/${names[i]} 실패:" >&2
            echo "$out" | tail -20 >&2
            exit 1
        }
        got=$(echo "$out" | grep -Eo '[0-9]+ pass|pass [0-9]+' | grep -Eo '[0-9]+' | sort -n | tail -1)
        [[ $got == $((TESTS * n)) ]] || {
            echo "$d/${names[i]}: 통과 ${got:-0} ≠ $((TESTS * n))" >&2
            exit 1
        }
    done
done

# 4) 속도: cd 를 셸로 붙인다. hyperfine 이 셸 기동 시간을 재서 빼 준다 (2.0 부터 && 를 쓰면 셸을 명시해야 한다)
for d in single suite; do
    w=3 r=20
    [[ $d == suite ]] && w=1 r=10
    args=()
    for i in "${!names[@]}"; do
        args+=(-n "${names[i]}" "cd $C/$d/${names[i]%-parallel} && ${cmds[i]}")
    done
    hyperfine --shell=default -w "$w" -r "$r" "${args[@]}" --export-json "$TMP/$d.json"
done

# 5) test-results.json (hyperfine 2.0 JSON: 통계는 .summary 아래, 이름은 .name)
for d in single suite; do
    files=$(find "$C/$d/bun/test" -type f | wc -l)
    jq -c --arg name "$d" --argjson files $((files)) --argjson tests $((files * TESTS)) \
        '{$name, $files, $tests, runs: (.results[0].measurements | length),
      results: [.results[] | .summary as $s | $s.time_wall_clock as $t
        | {tool: .name, mean: $t.mean, stddev: $t.stddev, min: $t.min, max: $t.max,
           user: $s.time_user.mean, system: $s.time_system.mean}]}' "$TMP/$d.json"
done >"$TMP/corpora.jsonl"

v() { node -p "require('$HERE/node_modules/$1/package.json').version"; }
os=$(sw_vers -productVersion 2>/dev/null | sed 's/^/macOS /' || uname -sr)
cpu=$(sysctl -n machdep.cpu.brand_string 2>/dev/null || grep -m1 'model name' /proc/cpuinfo | cut -d: -f2- || true)
cpu=${cpu:-$(uname -m)} # aarch64 Linux 의 /proc/cpuinfo 에는 model name 이 없다
jq -n \
    --arg date "$(date -u +%FT%TZ)" --arg os "$os ($(uname -m))" --arg cpu "${cpu# }" \
    --argjson cores "$(getconf _NPROCESSORS_ONLN)" --arg commit "$(git -C "$HERE" rev-parse --short HEAD)" \
    --arg jest "$(v jest)" --arg vitest "$(v vitest)" --arg swc "$(v @swc/core)" \
    --arg node "$(node --version)" --arg deno "$(deno eval 'console.log(Deno.version.deno)')" \
    --arg bun "$("$BUN" --revision)" --argjson testsPerFile "$TESTS" \
    --slurpfile corpora "$TMP/corpora.jsonl" \
    '{meta: {$date, $os, $cpu, $cores, $commit, $testsPerFile,
           versions: {$jest, $vitest, $node, $deno, $bun, "@swc/core": $swc}},
    $corpora}' >"$HERE/test-results.json"

echo "→ $HERE/test-results.json"
