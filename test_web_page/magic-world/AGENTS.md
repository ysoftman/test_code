# Magic World 개발 규칙

## Dev 서버 관리

- dev 서버는 **항상 1개만** 띄운다. 포트는 5199 고정.
- 코드 수정 후에는 **기존 서버를 먼저 종료하고 새로 시작**한다:
  - 종료: `lsof -iTCP:5199-5206 -sTCP:LISTEN -P | awk 'NR>1 {print $2}' | sort -u | xargs kill`
  - 시작: `nohup bun run dev --port 5199 --strictPort > /tmp/pwcheck/devserver.log 2>&1 &`
- 여러 서버가 떠 있으면 사용자가 옛 탭/옛 코드를 볼 수 있어 혼란을 준다(실제 사례: hjkl 미동작 원인이 예전 탭의 예전 번들이었음).
- 사용자에게는 항상 `http://localhost:5199/` 한 URL만 안내한다.

## 작업 완료 후 중간 산출물 정리

- 작업 중 생성한 **중간 산출물**(디버그 스크린샷 png, 검증용 임시 파일, 임시 훅 등)은 작업이 끝나면 반드시 정리한다.
- 스크린샷/검증 산출물이 저장소 루트에 남지 않도록 확인하고, 필요 없어진 파일은 삭제하거나 `.gitignore`에 추가한다.
- 임시 디버그 훅(예: `Object.assign(window, { __game })`)은 커밋 전에 반드시 제거한다.
- `/tmp/pwcheck/` 등 임시 디렉터리의 파일은 저장소 정리 대상에서 제외한다.

## 기타

- 빌드: `bun run build` (tsc + vite build)
- 에셋/디버그 검증 스크립트는 `/tmp/pwcheck/`에 둔다 (png.mjs 디코더는 Paeth 필터 4 버그 수정본 사용)
