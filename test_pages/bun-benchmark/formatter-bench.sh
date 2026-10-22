#!/usr/bin/env bash
# prettier · biome · bun fmt(main canary) 포맷 속도 벤치마크 → formatter-results.json
# 요구: bun, hyperfine, jq, rsync, git
# 환경변수: BUN=<bun 바이너리>(기본: canary 다운로드), COPIES=<large 코퍼스 복제 수>(기본 40)
set -euo pipefail

HERE=$(cd "$(dirname "$0")" && pwd)
SRC=$(cd "$HERE/.." && pwd) # 코퍼스 원본: test_pages
# repo 밖에서 돌린다 — prettier/bun 이 .gitignore 를 읽어 코퍼스를 건너뛰지 않도록
TMP=${BENCH_TMP:-${TMPDIR:-/tmp}/formatter-benchmark}
COPIES=${COPIES:-40}
PRETTIER=$HERE/node_modules/.bin/prettier
mkdir -p "$TMP"

[[ -x $PRETTIER ]] || (cd "$HERE" && bun install)
# .bin/biome 은 Node 래퍼(시작 ~50ms 추가)라 플랫폼 네이티브 바이너리를 직접 쓴다
BIOME=$(echo "$HERE"/node_modules/@biomejs/cli-*/biome)

# 1) bun: canary 릴리스 = main 브랜치 최신 빌드 (bun fmt 는 아직 태그 릴리스에 없음)
if [[ -z ${BUN:-} ]]; then
    target=$(uname -s | tr '[:upper:]' '[:lower:]')-$(uname -m | sed 's/arm64/aarch64/; s/x86_64/x64/')
    curl -fsSL -o "$TMP/bun.zip" "https://github.com/oven-sh/bun/releases/download/canary/bun-$target.zip"
    unzip -oq "$TMP/bun.zip" -d "$TMP"
    BUN=$TMP/bun-$target/bun
fi
"$BUN" fmt --help >/dev/null 2>&1 || {
    echo "bun fmt 가 없는 빌드: $("$BUN" --revision)" >&2
    exit 1
}

# 2) 코퍼스: test_pages 의 git 추적 소스 (하위 프로젝트 biome.json, 이 디렉토리 제외)
#   small = 원본 1벌, large = COPIES 벌, html/css/js = large 에서 언어별로 추림
C=$TMP/corpus
rm -rf "$C"
mkdir -p "$C/small" "$C/large"
git -C "$SRC" ls-files | grep -E '\.(html|css|js|jsx|ts|tsx|vue|json)$' |
    grep -vE '(^bun-benchmark/|biome\.json$)' >"$TMP/files.txt"
rsync -a --files-from="$TMP/files.txt" "$SRC/" "$C/small/"
for i in $(seq -w 1 "$COPIES"); do rsync -a "$C/small/" "$C/large/c$i/"; done
pick() { # pick <코퍼스명> <확장자...>
    local d=$1
    shift
    rsync -a --prune-empty-dirs --include='*/' "${@/#/--include=*.}" --exclude='*' "$C/large/" "$C/$d/"
}
pick html html
pick css css
pick js js jsx ts tsx

# biome 은 HTML 포맷터가 기본 off(실험적) → 켜고, 출력이 prettier 에 가깝도록 맞춘다
for d in small large html css js; do
    cat >"$C/$d/biome.json" <<'EOF'
{
  "formatter": { "indentStyle": "space" },
  "css": { "parser": { "tailwindDirectives": true } },
  "html": {
    "experimentalFullSupportEnabled": true,
    "formatter": {
      "enabled": true,
      "indentScriptAndStyle": true,
      "selfCloseVoidElements": "always"
    }
  },
  "overrides": [
    {
      "includes": ["**/*.vue"],
      "html": { "formatter": { "indentScriptAndStyle": false } }
    }
  ],
  "files": { "maxSize": 10485760 }
}
EOF
done

# 3) 속도: 쓰기 모드, 매 실행 전 코퍼스 원복(--prepare, 측정 제외)
W=$TMP/work
for d in small html css js large; do
    runs=10
    [[ $d == js || $d == large ]] && runs=5
    hyperfine -w 1 -r "$runs" --prepare "rsync -a --delete $C/$d/ $W/" \
        -n prettier "cd $W && $PRETTIER --write . --log-level=silent" \
        -n biome "cd $W && $BIOME format --write ." \
        -n bun "cd $W && $BUN fmt . --log-level=silent" \
        --export-json "$TMP/$d.json"
done

# 4) 출력 일치: small 을 각 도구로 포맷해 prettier 결과와 바이트 비교
for t in prettier biome bun; do rsync -a --delete "$C/small/" "$TMP/out-$t/"; done
(cd "$TMP/out-prettier" && "$PRETTIER" --write . --log-level=silent)
(cd "$TMP/out-biome" && "$BIOME" format --write . >/dev/null)
(cd "$TMP/out-bun" && "$BUN" fmt . --log-level=silent)
for ext in html vue css js jsx ts tsx json; do
    total=$(grep -c "\.$ext\$" "$TMP/files.txt" || true)
    for t in biome bun; do
        diffs=$(diff -rq -x biome.json "$TMP/out-prettier" "$TMP/out-$t" | grep -c "\.$ext and " || true)
        jq -nc --arg ext "$ext" --arg tool "$t" --argjson same $((total - diffs)) --argjson total "$total" \
            '{$ext, $tool, $same, $total}'
    done
done >"$TMP/parity.jsonl"

# 5) formatter-results.json
for d in small html css js large; do
    files=$(find "$C/$d" -type f ! -name biome.json | wc -l)
    bytes=$(find "$C/$d" -type f ! -name biome.json -exec cat {} + | wc -c)
    jq -c --arg name "$d" --argjson files $((files)) --argjson bytes $((bytes)) \
        '{$name, $files, $bytes, runs: (.results[0].times | length),
      results: [.results[] | {tool: .command, mean, stddev, min, max}]}' "$TMP/$d.json"
done >"$TMP/corpora.jsonl"

os=$(sw_vers -productVersion 2>/dev/null | sed 's/^/macOS /' || uname -sr)
cpu=$(sysctl -n machdep.cpu.brand_string 2>/dev/null || grep -m1 'model name' /proc/cpuinfo | cut -d: -f2- || true)
cpu=${cpu:-$(uname -m)} # aarch64 Linux 의 /proc/cpuinfo 에는 model name 이 없다
jq -n \
    --arg date "$(date -u +%FT%TZ)" --arg os "$os ($(uname -m))" --arg cpu "${cpu# }" \
    --argjson cores "$(getconf _NPROCESSORS_ONLN)" --arg node "$(node --version)" \
    --arg prettier "$("$PRETTIER" --version)" --arg biome "$("$BIOME" --version | awk '{print $2}')" \
    --arg bun "$("$BUN" --revision)" --arg commit "$(git -C "$SRC" rev-parse --short HEAD)" \
    --argjson copies "$COPIES" \
    --slurpfile corpora "$TMP/corpora.jsonl" --slurpfile parity "$TMP/parity.jsonl" \
    '{meta: {$date, $os, $cpu, $cores, $node, $commit, $copies,
           versions: {$prettier, $biome, $bun}},
    $corpora, $parity}' >"$HERE/formatter-results.json"

echo "→ $HERE/formatter-results.json"
