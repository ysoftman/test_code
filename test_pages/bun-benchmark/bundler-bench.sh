#!/usr/bin/env bash
# esbuild · rolldown · vite · rspack · rollup · webpack · bun build 번들링 속도 벤치마크 → bundler-results.json
# 요구: bun, node, hyperfine, jq, curl, gzip
# 환경변수: BUN=<bun 바이너리>(기본: PATH 의 bun), COPIES=<large 코퍼스 three.js 복제 수>(기본 10)
set -euo pipefail

HERE=$(cd "$(dirname "$0")" && pwd)
# repo 밖에서 돌린다 — 번들러가 상위 package.json · 설정 파일을 읽지 않도록
TMP=${BENCH_TMP:-${TMPDIR:-/tmp}/bundler-benchmark}
COPIES=${COPIES:-10}
BUN=${BUN:-bun}
BIN=$HERE/node_modules/.bin
TOOLS="esbuild rolldown vite rspack rollup webpack bun"
mkdir -p "$TMP"

[[ -x $BIN/rolldown ]] || (cd "$HERE" && bun install)
# esbuild 는 설치 스크립트가 막히면 .bin 에 Node 래퍼가 남으므로 플랫폼 네이티브 바이너리를 직접 쓴다
ESBUILD=$(echo "$HERE"/node_modules/@esbuild/*/bin/esbuild)

# 1) 코퍼스: esbuild 공식 벤치마크와 같은 three.js r108 src. small = 1벌, large = COPIES 벌
#   entry 가 사본마다 namespace 를 전역에 걸어 tree-shaking 으로 빠지는 코드가 없게 한다
[[ -d $TMP/three ]] || {
    curl -fsSL https://registry.npmjs.org/three/-/three-0.108.0.tgz | tar -xz -C "$TMP" package/src
    mv "$TMP/package/src" "$TMP/three"
    rm -rf "$TMP/package"
}
C=$TMP/corpus
rm -rf "$C"
for d in small large; do
    n=$COPIES
    [[ $d == small ]] && n=1
    w=$C/$d
    mkdir -p "$w"
    ln -s "$HERE/node_modules" "$w/node_modules" # rollup 설정이 @rollup/plugin-terser 를 찾도록
    for i in $(seq "$n"); do cp -R "$TMP/three" "$w/copy$i"; done
    {
        for i in $(seq "$n"); do echo "import * as copy$i from \"./copy$i/Three.js\";"; done
        echo "globalThis.copies = [$(printf 'copy%d, ' $(seq "$n"))];"
    } >"$w/entry.js"
    # 설정: 모두 minify + 외부 sourcemap, 결과는 out/<도구>/bundle.js 파일 하나
    for t in webpack rspack; do
        cat >"$w/$t.config.mjs" <<EOF
export default {
  mode: "production",
  entry: "./entry.js",
  devtool: "source-map",
  output: { path: "$w/out/$t", filename: "bundle.js" },
};
EOF
    done
    cat >"$w/rollup.config.mjs" <<'EOF'
import terser from "@rollup/plugin-terser";

export default {
  input: "entry.js",
  output: { file: "out/rollup/bundle.js", format: "iife", sourcemap: true },
  plugins: [terser()],
};
EOF
    # vite 는 html 없이 JS entry 하나를 묶을 때 lib 모드를 쓴다. minify 기본값(oxc)은 그대로
    cat >"$w/vite.config.mjs" <<'EOF'
export default {
  build: {
    outDir: "out/vite",
    sourcemap: true,
    lib: { entry: "entry.js", formats: ["iife"], name: "bench", fileName: () => "bundle.js" },
  },
};
EOF
done

cmd() { # 번들러별 명령. 모두 코퍼스 디렉토리에서 실행한다
    case $1 in
        esbuild) echo "$ESBUILD entry.js --bundle --minify --sourcemap --format=iife --outfile=out/esbuild/bundle.js" ;;
        rolldown) echo "$BIN/rolldown entry.js --format iife --minify --sourcemap --file out/rolldown/bundle.js" ;;
        vite) echo "$BIN/vite build -c vite.config.mjs" ;;
        rspack) echo "$BIN/rspack build -c rspack.config.mjs" ;;
        rollup) echo "$BIN/rollup -c rollup.config.mjs --silent" ;;
        webpack) echo "$BIN/webpack -c webpack.config.mjs" ;;
        # bun 1.4.4 는 --outfile 에 --sourcemap 을 같이 주면 디렉토리를 무시하고 cwd 에 쓰므로 --outdir 로 지정한다
        bun) echo "$BUN build entry.js --minify --sourcemap=linked --format=iife --outdir=out/bun --entry-naming=bundle.js" ;;
    esac
}

# 2) 검증: 번들을 node 로 실행해 사본 수만큼 three.js 가 들어 있는지, sourcemap 이 있는지 본다
#   small 의 결과물 크기(minify · gzip)도 함께 기록한다
: >"$TMP/outputs.jsonl"
for d in small large; do
    n=$COPIES
    [[ $d == small ]] && n=1
    for t in $TOOLS; do
        out=$C/$d/out/$t/bundle.js
        log=$(cd "$C/$d" && $(cmd "$t") 2>&1) || {
            echo "$d/$t 빌드 실패:" >&2
            echo "$log" | tail -20 >&2
            exit 1
        }
        node -e 'require(process.argv[1]); const c = globalThis.copies;
            if (c?.length !== +process.argv[2] || c.some((x) => x.REVISION !== "108")) process.exit(1)' "$out" "$n" || {
            echo "$d/$t: 번들 실행 결과가 다름" >&2
            exit 1
        }
        [[ -s $out.map ]] || {
            echo "$d/$t: sourcemap 없음" >&2
            exit 1
        }
        if [[ $d == small ]]; then
            jq -nc --arg tool "$t" --argjson bytes "$(wc -c <"$out")" \
                --argjson gzip "$(gzip -9c "$out" | wc -c)" '{$tool, $bytes, $gzip}' >>"$TMP/outputs.jsonl"
        fi
    done
done

# 3) 속도: 코퍼스 디렉토리에서 셸 없이 실행
for d in small large; do
    w=2 r=10
    [[ $d == large ]] && w=1 r=5
    args=()
    for t in $TOOLS; do args+=(-n "$t" "$(cmd "$t")"); done
    (cd "$C/$d" && hyperfine -N -w "$w" -r "$r" "${args[@]}" --export-json "$TMP/$d.json")
done

# 4) bundler-results.json (hyperfine 2.0 JSON: 통계는 .summary 아래, 이름은 .name)
#   memory 는 가장 큰 프로세스 하나의 피크 RSS 최댓값이다 (자식 워커 합계가 아님)
for d in small large; do
    files=$(find "$C/$d" -path '*/copy*' -name '*.js' | wc -l)
    bytes=$(find "$C/$d" -path '*/copy*' -name '*.js' -exec cat {} + | wc -c)
    jq -c --arg name "$d" --argjson files $((files)) --argjson bytes $((bytes)) \
        '{$name, $files, $bytes, runs: (.results[0].measurements | length),
      results: [.results[] | .summary as $s | $s.time_wall_clock as $t
        | {tool: .name, mean: $t.mean, stddev: $t.stddev, min: $t.min, max: $t.max,
           user: $s.time_user.mean, system: $s.time_system.mean, memory: $s.memory_peak_resident.max}]}' "$TMP/$d.json"
done >"$TMP/corpora.jsonl"

v() { jq -r .version "$HERE/node_modules/$1/package.json"; }
os=$(sw_vers -productVersion 2>/dev/null | sed 's/^/macOS /' || uname -sr)
cpu=$(sysctl -n machdep.cpu.brand_string 2>/dev/null || grep -m1 'model name' /proc/cpuinfo | cut -d: -f2- || true)
cpu=${cpu:-$(uname -m)} # aarch64 Linux 의 /proc/cpuinfo 에는 model name 이 없다
jq -n \
    --arg date "$(date -u +%FT%TZ)" --arg os "$os ($(uname -m))" --arg cpu "${cpu# }" \
    --argjson cores "$(getconf _NPROCESSORS_ONLN)" --arg commit "$(git -C "$HERE" rev-parse --short HEAD)" \
    --arg node "$(node --version)" --argjson copies "$COPIES" \
    --arg esbuild "$("$ESBUILD" --version)" --arg rolldown "$(v rolldown)" --arg vite "$(v vite)" --arg rspack "$(v @rspack/core)" \
    --arg rollup "$(v rollup)" --arg terser "$(v terser)" --arg webpack "$(v webpack)" \
    --arg bun "$("$BUN" --revision)" \
    --slurpfile corpora "$TMP/corpora.jsonl" --slurpfile outputs "$TMP/outputs.jsonl" \
    '{meta: {$date, $os, $cpu, $cores, $commit, $node, $copies,
           versions: {$esbuild, $rolldown, $vite, $rspack, $rollup, $terser, $webpack, $bun}},
    $corpora, $outputs}' >"$HERE/bundler-results.json"

echo "→ $HERE/bundler-results.json"
