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
# 랜딩 HTML 은 정적이라 심볼릭 링크 → 수정 후 브라우저 새로고침만 하면 반영됨
ln -sf "$SRC/index.html" "$SITE/index.html"
ln -sf "$SRC/css-framework-comparison/index.html" "$SITE/css-framework-comparison/index.html"

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
echo "   (랜딩 index.html 은 심볼릭 링크 → 수정 후 브라우저 새로고침만 하면 반영)"
echo ""
# python http.server 는 심볼릭 링크를 따라가서, 랜딩 수정이 새로고침만으로 반영됨.
# (serve 는 심볼릭 링크를 막아 landing live-edit 가 안 됨)
if command -v python3 >/dev/null 2>&1; then
  exec python3 -m http.server "$PORT" --directory "$OUT"
else
  echo "python3 없음 → bunx serve 로 폴백 (랜딩 live-edit 는 비활성)"
  exec bunx serve -l "$PORT" "$OUT"
fi
