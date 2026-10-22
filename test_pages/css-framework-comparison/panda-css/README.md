# Panda CSS

- 분류: 빌드 타임 CSS-in-JS
- 런타임: zero runtime
- 동작: PostCSS(`@pandacss/dev/postcss`) + codegen
- 공식 문서: <https://panda-css.com/>

## 실행

워크스페이스 루트(`css-framework-comparison/`)에서 한 번만 설치:

```bash
bun install
```

이 앱만 개발 서버로 실행:

```bash
bun run dev          # 이 폴더에서 (panda codegen 후 vite)
# 또는 루트에서: bun run dev:panda
```

프로덕션 빌드:

```bash
bun run build        # panda codegen && vite build
```

## 셋업 메모

- `panda.config.ts` — `include`, `outdir: "styled-system"`, `preflight: true`.
- `postcss.config.cjs` — `@pandacss/dev/postcss` 플러그인.
- `src/index.css` — `@layer reset, base, tokens, recipes, utilities;` 한 줄.
- `panda codegen` 이 `styled-system/` 생성 → `import { css, cx } from "../styled-system/css"`.
  (`styled-system/` 는 gitignore, dev/build 스크립트가 매번 codegen)

### 다크모드 처리 (중요)

Panda 는 **빌드 타임 정적 추출**이라 `css()` 인자는 정적 리터럴이어야 한다
(`css({ bg: someVar })` 처럼 동적 값은 추출 안 됨).
그래서 다크모드는 색상 토큰을 **CSS 변수**로 두고, 루트의 `inline style` 로
변수 값만 교체한다. `css()` 에서는 `var(--bg)` 같은 정적 문자열만 참조.

## 데모 사양 (모든 프레임워크 공통)

1. 다크모드 토글
2. Buttons — contained / outlined / text / with icon / disabled
3. Card — title + body + actions
4. Form — text input · select · checkbox · submit → 제출 결과(JSON) 표시

## 메모

- 번들(첫 빌드): JS ~162KB / gzip ~53KB + CSS ~18.4KB / gzip ~5.6KB
- CSS 가 Tailwind 보다 큰 이유: 기본 디자인 토큰을 CSS 변수로 모두 방출 + preflight
- 타입 안전한 스타일 작성(자동완성/토큰 검증), 런타임 비용 없음
- 정적 추출 제약(동적 값 불가)에 주의 필요
