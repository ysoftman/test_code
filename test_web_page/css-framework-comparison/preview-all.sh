#!/usr/bin/env bash
# 모든 프레임워크를 빌드한 결과를 GitHub Pages 와 동일한 경로(/test_code/...)로
# 모아서 정적 서버로 띄운다. base 경로가 그대로 맞아 배포본과 똑같이 비교 가능.
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)" # css-framework-comparison/
SRC="$(cd "$HERE/.." && pwd)"         # test_web_page/
OUT="$HERE/.preview"                  # 임시 출력 (gitignore)
SITE="$OUT/test_code"                 # base 가 /test_code/... 라서 이 폴더명 사용
PORT="${PORT:-3000}"

echo "▶ assembling into $SITE"
rm -rf "$OUT"
mkdir -p "$SITE/css-framework-comparison"
cp "$SRC/index.html" "$SITE/index.html"
cp "$SRC/css-framework-comparison/index.html" "$SITE/css-framework-comparison/index.html"

for dir in "$SRC"/css-framework-comparison/*/; do
  app="$(basename "$dir")"
  if [ -d "$dir/dist" ]; then
    echo "  + $app"
    mkdir -p "$SITE/css-framework-comparison/$app"
    cp -r "$dir/dist/." "$SITE/css-framework-comparison/$app/"
  fi
done

echo ""
echo "✅ open:  http://localhost:$PORT/test_code/css-framework-comparison/"
echo ""
exec bunx serve -l "$PORT" "$OUT"
