# vanilla-extract

- 분류: 빌드 타임 CSS-in-JS (.css.ts)
- 런타임: zero runtime
- 공식 문서: <https://vanilla-extract.style/>

## 실행

워크스페이스 루트(`css-framework-comparison/`)에서 한 번만 설치:

```bash
bun install
```

이 앱만 개발 서버로 실행:

```bash
bun run dev          # 이 폴더에서
# 또는 루트에서: bun run dev:vanilla
```

프로덕션 빌드:

```bash
bun run build        # dist/ 생성 (base: /test_code/css-framework-comparison/vanilla-extract/)
```

## 셋업 메모

- `vite.config.ts` 에 `@vanilla-extract/vite-plugin` 추가.
- 스타일은 `*.css.ts` 파일에 작성 → 빌드 타임에 정적 CSS 추출.
- 다크모드: `createTheme` 로 라이트 테마가 vars(contract) 를 정의하고,
  `createTheme(vars, {...})` 로 다크 테마 클래스를 생성 → 루트 클래스만 교체.
- `style` / `styleVariants` 로 컴포넌트 스타일, `globalStyle` 로 전역.

## 데모 사양 (모든 프레임워크 공통)

1. 다크모드 토글
2. Buttons — contained / outlined / text / with icon / disabled
3. Card — title + body + actions
4. Form — text input · select · checkbox · submit → 제출 결과(JSON) 표시

## 메모

- 번들(첫 빌드): JS ~146.6KB / gzip ~47.2KB + CSS ~2.64KB / gzip ~0.8KB
- **CSS 가 가장 작음** — 사용한 스타일만 추출, 토큰 전체 방출 안 함
- 타입 안전(.css.ts 가 TS) + zero runtime. 스타일을 별도 파일에 분리
