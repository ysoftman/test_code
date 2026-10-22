#!/usr/bin/env bash
# eslint · oxlint · biome · bun lint(main canary) 린트 속도 벤치마크 → lint-results.json
# 요구: bun, node, hyperfine, jq, rsync, git
# 환경변수: BUN=<bun 바이너리>(기본: canary 다운로드), COPIES=<large 코퍼스 복제 수>(기본 40)
set -euo pipefail

HERE=$(cd "$(dirname "$0")" && pwd)
SRC=$(cd "$HERE/.." && pwd) # 코퍼스 원본: test_pages
# repo 밖에서 돌린다 — 도구가 .gitignore 나 상위 설정 파일을 읽지 않도록
TMP=${BENCH_TMP:-${TMPDIR:-/tmp}/lint-benchmark}
COPIES=${COPIES:-40}
ESLINT=$HERE/node_modules/.bin/eslint
OXLINT=$HERE/node_modules/.bin/oxlint # npm 배포본은 Node 래퍼 + napi 바인딩뿐이라 그대로 쓴다
mkdir -p "$TMP"

[[ -x $ESLINT ]] || (cd "$HERE" && bun install)
# .bin/biome 은 Node 래퍼(시작 ~50ms 추가)라 플랫폼 네이티브 바이너리를 직접 쓴다
BIOME=$(echo "$HERE"/node_modules/@biomejs/cli-*/biome)

# 1) bun: canary 릴리스 = main 브랜치 최신 빌드 (bun lint 는 아직 태그 릴리스에 없음)
if [[ -z ${BUN:-} ]]; then
    target=$(uname -s | tr '[:upper:]' '[:lower:]')-$(uname -m | sed 's/arm64/aarch64/; s/x86_64/x64/')
    curl -fsSL -o "$TMP/bun.zip" "https://github.com/oven-sh/bun/releases/download/canary/bun-$target.zip"
    unzip -oq "$TMP/bun.zip" -d "$TMP"
    BUN=$TMP/bun-$target/bun
fi
"$BUN" lint --help >/dev/null 2>&1 || {
    echo "bun lint 가 없는 빌드: $("$BUN" --revision)" >&2
    exit 1
}

# 2) 규칙: eslint:recommended 중 네 도구가 모두 지원하는 규칙만, 전부 warn
#   biome 대응은 규칙 하나씩 `biome migrate eslint` 로 뽑는다 (inspired 제외 = 동작이 같은 규칙만)
R=$TMP/rules
rm -rf "$R"
mkdir -p "$R"
touch "$R/rules.txt" "$R/excluded.jsonl"
(cd "$HERE" && node -p 'Object.keys(require("@eslint/js").configs.recommended.rules).join("\n")') | sort >"$R/recommended"
"$OXLINT" --rules -f json | jq -r '.[] | select(.scope == "eslint") | .value' | sort >"$R/oxlint"
"$BUN" lint --rules | sed -n 's#^eslint/##p' | sort >"$R/bun"
while read -r rule; do
    d=$R/migrate/$rule
    mkdir -p "$d"
    echo '{}' >"$d/biome.json"
    jq -n --arg r "$rule" '{rules: {($r): "error"}}' >"$d/.eslintrc.json"
    (cd "$d" && "$BIOME" migrate eslint --write >/dev/null 2>&1) || true
    biome=$(jq -r '[.linter.rules // {} | to_entries[] | select(.value | type == "object")
        | .key as $g | .value | keys[] | select(. != "recommended") | "\($g)/\(.)"] | first // ""' "$d/biome.json")
    reason=
    if ! grep -qx "$rule" "$R/bun"; then
        reason="bun 미지원"
    elif ! grep -qx "$rule" "$R/oxlint"; then
        reason="oxlint 미지원"
    elif [[ -z $biome ]]; then
        reason="biome 대응 규칙 없음"
    elif grep -q " $biome$" "$R/rules.txt"; then
        reason="biome 에서 $(grep " $biome$" "$R/rules.txt" | cut -d' ' -f1) 와 같은 규칙"
    fi
    if [[ -z $reason ]]; then echo "$rule $biome" >>"$R/rules.txt"; else
        jq -nc --arg rule "$rule" --arg reason "$reason" '{$rule, $reason}' >>"$R/excluded.jsonl"
    fi
done <"$R/recommended"

# 설정은 코퍼스 밖에 두고 -c 로 넘긴다 (코퍼스 안에 두면 설정 파일까지 린트된다)
CF=$TMP/config
mkdir -p "$CF"
cat >"$CF/eslint.config.mjs" <<EOF
import { createRequire } from "node:module";

const require = createRequire("$HERE/");
const globals = require("globals");
const tseslint = require("typescript-eslint");

export default [
  {
    files: ["**/*.{js,jsx,ts,tsx}"],
    linterOptions: { reportUnusedDisableDirectives: "off" },
    languageOptions: {
      globals: { ...globals.browser, ...globals.node },
      parserOptions: { ecmaFeatures: { jsx: true } },
    },
    rules: $(cut -d' ' -f1 "$R/rules.txt" | jq -Rn '[inputs | {(.): "warn"}] | add'),
  },
  { files: ["**/*.{ts,tsx}"], languageOptions: { parser: tseslint.parser } },
];
EOF
cut -d' ' -f1 "$R/rules.txt" | jq -Rn '{categories: {correctness: "off"}, env: {browser: true, node: true},
    rules: ([inputs | {("eslint/" + .): "warn"}] | add)}' >"$CF/oxlintrc.json"
cut -d' ' -f2 "$R/rules.txt" | jq -Rn '[inputs | split("/") | {(.[0]): {(.[1]): "warn"}}]
    | reduce .[] as $x ({preset: "none"}; . * $x) | {linter: {rules: .}, files: {maxSize: 10485760}}' >"$CF/biome.json"

# 3) 코퍼스: test_pages 의 git 추적 JS/TS 소스 (vue 는 bun lint·oxlint 대상이 아니라 제외)
#   small = 원본 1벌, large = COPIES 벌, js / ts 는 large 에서 언어별로 추림
C=$TMP/corpus
rm -rf "$C"
mkdir -p "$C/small" "$C/large"
git -C "$SRC" ls-files | grep -E '\.(js|jsx|ts|tsx)$' |
    grep -vE '^bun-benchmark/|\.eslintrc' >"$TMP/files.txt"
rsync -a --files-from="$TMP/files.txt" "$SRC/" "$C/small/"
for i in $(seq -w 1 "$COPIES"); do rsync -a "$C/small/" "$C/large/c$i/"; done
pick() { # pick <코퍼스명> <확장자...>
    local d=$1
    shift
    rsync -a --prune-empty-dirs --include='*/' "${@/#/--include=*.}" --exclude='*' "$C/large/" "$C/$d/"
}
pick js js jsx
pick ts ts tsx

ESLINT_CMD="$ESLINT -c $CF/eslint.config.mjs"
BUN_CMD="$BUN lint -c $CF/eslint.config.mjs"
OXLINT_CMD="$OXLINT -c $CF/oxlintrc.json"
BIOME_CMD="$BIOME lint --config-path=$CF"

# 4) 속도: 읽기 전용이라 원복 없이 같은 코퍼스를 반복 린트. eslint 는 단일 스레드(기본)와 --concurrency=auto 둘 다
for d in small js ts large; do
    runs=10
    [[ $d == small ]] || runs=5
    (cd "$C/$d" && hyperfine -N -w 1 -r "$runs" \
        -n eslint "$ESLINT_CMD ." \
        -n eslint-mt "$ESLINT_CMD --concurrency=auto ." \
        -n oxlint "$OXLINT_CMD ." \
        -n biome "$BIOME_CMD ." \
        -n bun "$BUN_CMD ." \
        --export-json "$TMP/$d.json")
done

# 5) 진단 일치: small 의 진단을 (파일, 줄, eslint 규칙명) 으로 모아 eslint 결과와 비교
P=$TMP/parity
rm -rf "$P"
mkdir -p "$P"
cd "$C/small"
strip() { sed "s#^$PWD/##; s#^\./##" | sort; }
$ESLINT_CMD -f json . | jq -r '.[] | .filePath as $f | .messages[] | [$f, .line, .ruleId // "parse"] | @tsv' | strip >"$P/eslint"
$BUN_CMD -f json . | jq -r '.[] | .filePath as $f | .messages[] | [$f, .line, .ruleId // "parse"] | @tsv' | strip >"$P/bun"
$OXLINT_CMD -f json . | jq -r '.diagnostics[] | [.filename, .labels[0].span.line,
    ((.code // "parse") as $c | ($c | capture("\\((?<r>.*)\\)").r) // $c)] | @tsv' | strip >"$P/oxlint"
$BIOME_CMD --reporter=json --max-diagnostics=none . 2>/dev/null |
    jq -r --rawfile map "$R/rules.txt" '($map | split("\n") | map(select(. != "") | split(" ") | {("lint/" + .[1]): .[0]}) | add) as $m
    | .diagnostics[] | [.location.path, .location.start.line, ($m[.category] // .category)] | @tsv' | strip >"$P/biome"
cd "$HERE"
for t in eslint oxlint biome bun; do
    comm -12 "$P/eslint" "$P/$t" | cut -f3 | sort | uniq -c | awk -v t="$t" '{print t, $2, "matched", $1}'
    cut -f3 "$P/$t" | sort | uniq -c | awk -v t="$t" '{print t, $2, "count", $1}'
done | jq -Rn '[inputs | split(" ") | {tool: .[0], rule: .[1], (.[2]): (.[3] | tonumber)}]
    | group_by([.tool, .rule]) | map({count: 0, matched: 0} + add)' >"$TMP/parity.json"

# 6) lint-results.json
for d in small js ts large; do
    files=$(find "$C/$d" -type f | wc -l)
    bytes=$(find "$C/$d" -type f -exec cat {} + | wc -c)
    jq -c --arg name "$d" --argjson files $((files)) --argjson bytes $((bytes)) \
        '{$name, $files, $bytes, runs: (.results[0].times | length),
      results: [.results[] | {tool: .command, mean, stddev, min, max}]}' "$TMP/$d.json"
done >"$TMP/corpora.jsonl"

v() { node -p "require('$HERE/node_modules/$1/package.json').version"; }
os=$(sw_vers -productVersion 2>/dev/null | sed 's/^/macOS /' || uname -sr)
cpu=$(sysctl -n machdep.cpu.brand_string 2>/dev/null || grep -m1 'model name' /proc/cpuinfo | cut -d: -f2- || true)
cpu=${cpu:-$(uname -m)} # aarch64 Linux 의 /proc/cpuinfo 에는 model name 이 없다
jq -n \
    --arg date "$(date -u +%FT%TZ)" --arg os "$os ($(uname -m))" --arg cpu "${cpu# }" \
    --argjson cores "$(getconf _NPROCESSORS_ONLN)" --arg node "$(node --version)" \
    --arg eslint "$(v eslint)" --arg tseslint "$(v typescript-eslint)" --arg oxlint "$(v oxlint)" \
    --arg biome "$("$BIOME" --version | awk '{print $2}')" --arg bun "$("$BUN" --revision)" \
    --arg commit "$(git -C "$SRC" rev-parse --short HEAD)" --argjson copies "$COPIES" \
    --rawfile rules "$R/rules.txt" --slurpfile excluded "$R/excluded.jsonl" \
    --slurpfile corpora "$TMP/corpora.jsonl" --slurpfile parity "$TMP/parity.json" \
    '{meta: {$date, $os, $cpu, $cores, $node, $commit, $copies,
           versions: {$eslint, "typescript-eslint": $tseslint, $oxlint, $biome, $bun}},
    rules: ($rules | split("\n") | map(select(. != "") | split(" ") | {eslint: .[0], biome: .[1]})),
    $excluded, $corpora, parity: $parity[0]}' >"$HERE/lint-results.json"

echo "→ $HERE/lint-results.json"
