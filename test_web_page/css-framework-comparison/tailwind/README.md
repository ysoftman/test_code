# Tailwind CSS

- 분류: 유틸리티 우선 CSS 프레임워크
- 런타임: zero runtime (빌드 타임 생성)
- 버전: Tailwind v4 (`@tailwindcss/vite` 플러그인)
- 공식 문서: <https://tailwindcss.com/>

## 실행

워크스페이스 루트(`css-framework-comparison/`)에서 한 번만 설치:

```bash
bun install
```

이 앱만 개발 서버로 실행:

```bash
bun run dev          # 이 폴더에서
# 또는 루트에서: bun run dev:tailwind
```

프로덕션 빌드:

```bash
bun run build        # dist/ 생성 (base: /test_code/css-framework-comparison/tailwind/)
```

## 셋업 메모 (v4)

- `vite.config.ts` 에 `@tailwindcss/vite` 플러그인만 추가 (PostCSS/`tailwind.config.js` 불필요).
- `src/index.css` 는 `@import "tailwindcss";` 한 줄.
- 클래스 기반 다크모드는 `@custom-variant dark (&:where(.dark, .dark *));` 로 정의하고
  루트 요소에 `.dark` 클래스를 토글한다.

## 데모 사양 (모든 프레임워크 공통)

1. 다크모드 토글
2. Buttons — contained / outlined / text / with icon / disabled
3. Card — title + body + actions
4. Form — text input · select · checkbox · submit → 제출 결과(JSON) 표시

## 메모

- 번들(첫 빌드): JS ~148KB / gzip ~47.5KB + CSS ~11.7KB / gzip ~3.2KB
  (JS 대부분은 React, 스타일은 사용한 유틸리티만 생성됨)
- 컴포넌트 라이브러리가 없어 버튼/입력 등을 직접 마크업 — 코드량은 많지만 자유도 높음
- 런타임 스타일 비용 없음
