#!/usr/bin/env bash
# 배포본과 같은 경로(/test_code/design-skill-comparison/...)로 조립해 정적 서버로 띄운다.
# package.json 이 있는 폴더는 빌드 후 dist 를, 없는 폴더는 그대로 연결한다(심볼릭 링크라 정적 페이지는 새로고침만 하면 반영).
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"
OUT="$HERE/.preview"
SITE="$OUT/test_code/design-skill-comparison"
PORT="${PORT:-3001}"

rm -rf "$OUT"
mkdir -p "$SITE"
ln -s "$HERE/../index.html" "$OUT/test_code/index.html"
ln -s "$HERE/index.html" "$SITE/index.html"

for dir in "$HERE"/*/; do
    dir="${dir%/}"
    app="$(basename "$dir")"
    if [ -f "$dir/package.json" ]; then
        echo "▶ build $app"
        (cd "$dir" && bun install && bun run build) || {
            echo "✗ $app build failed, skip"
            continue
        }
        ln -s "$dir/dist" "$SITE/$app"
    else
        ln -s "$dir" "$SITE/$app"
    fi
done

echo ""
echo "✅ open: http://localhost:$PORT/test_code/design-skill-comparison/"
exec python3 -m http.server "$PORT" --directory "$OUT"
