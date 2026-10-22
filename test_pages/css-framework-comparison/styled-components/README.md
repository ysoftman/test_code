# styled-components

- 분류: CSS-in-JS
- 런타임: runtime
- 버전: styled-components v6
- 공식 문서: <https://styled-components.com/>

## 실행

워크스페이스 루트(`css-framework-comparison/`)에서 한 번만 설치:

```bash
bun install
```

이 앱만 개발 서버로 실행:

```bash
bun run dev          # 이 폴더에서
# 또는 루트에서: bun run dev:styled
```

프로덕션 빌드:

```bash
bun run build        # dist/ 생성 (base: /test_code/css-framework-comparison/styled-components/)
```

## 셋업 메모

- `ThemeProvider` + theme 객체(light/dark)로 다크모드 처리 → 동적 값도 자유롭게 사용.
- `createGlobalStyle` 로 body 전역 스타일.
- theme 타입은 `src/styled.d.ts` 에서 `DefaultTheme` 모듈 보강.
- transient props(`$variant`)로 DOM 에 안 새는 prop 전달.

## 데모 사양 (모든 프레임워크 공통)

1. 다크모드 토글
2. Buttons — contained / outlined / text / with icon / disabled
3. Card — title + body + actions
4. Form — text input · select · checkbox · submit → 제출 결과(JSON) 표시

## 메모

- 번들(첫 빌드): JS ~178.8KB / gzip ~59.7KB (별도 CSS 없음 — 런타임 주입)
- 동적 스타일이 가장 자유로움(props 기반). 런타임 비용 존재
