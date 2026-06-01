# Chakra UI

- 분류: React 컴포넌트 라이브러리
- 버전: v3 (Panda CSS 기반, zero-runtime 스타일 엔진)
- 색상 모드: next-themes
- 공식 문서: <https://chakra-ui.com/>

## 실행

워크스페이스 루트(`css-framework-comparison/`)에서 한 번만 설치:

```bash
bun install
```

이 앱만 개발 서버로 실행:

```bash
bun run dev          # 이 폴더에서
# 또는 루트에서: bun run dev:chakra
```

프로덕션 빌드:

```bash
bun run build        # dist/ 생성 (base: /test_code/css-framework-comparison/chakra-ui/)
```

## 셋업 메모 (v3)

- `<ChakraProvider value={defaultSystem}>` 로 시스템 주입.
- 색상 모드는 `next-themes` 로 처리 — `src/color-mode.tsx` 에 `ColorModeProvider`,
  `useColorMode` 정의(html 의 `.dark`/`.light` 클래스 토글).
- v3 컴포넌트는 합성 패턴: `Card.Root/Body/Title/...`, `NativeSelect.Root/Field`,
  `Checkbox.Root/Control/Label`. `colorPalette`, `variant` props 사용.

## 데모 사양 (모든 프레임워크 공통)

1. 다크모드 토글
2. Buttons — solid / outline / ghost / with icon / disabled
3. Card — title + body + actions
4. Form — text input · native select · checkbox · submit → 제출 결과(JSON) 표시

## 메모

- 번들(첫 빌드): JS ~438KB / gzip ~124.9KB (별도 CSS 없음 — 엔진이 런타임 주입)
- 컴포넌트 라이브러리 중 번들이 가장 큼(접근성 포함 풍부한 컴포넌트 + 시스템)
- v2 는 Emotion(runtime) 기반 — 여기서는 v3 사용
