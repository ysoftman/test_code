# shadcn/ui

- 분류: 복붙형(copy-paste) 컴포넌트 + Tailwind CSS + Radix UI
- 런타임: zero runtime
- 공식 문서: <https://ui.shadcn.com/>

## 실행

워크스페이스 루트(`css-framework-comparison/`)에서 한 번만 설치:

```bash
bun install
```

이 앱만 개발 서버로 실행:

```bash
bun run dev          # 이 폴더에서
# 또는 루트에서: bun run dev:shadcn
```

프로덕션 빌드:

```bash
bun run build        # dist/ 생성 (base: /test_code/css-framework-comparison/shadcn-ui/)
```

## 셋업 메모

shadcn 은 설치형 라이브러리가 아니라 **컴포넌트 소스를 프로젝트로 복사**하는 방식.
여기서는 CLI(`shadcn init`) 대화형 절차 대신 동일 구조를 수동 구성:

- Tailwind v4(`@tailwindcss/vite`) + 경로 별칭 `@/* → src/*`(tsconfig + vite).
- `src/index.css` — CSS 변수 디자인 토큰(`:root` / `.dark`) + `@theme inline` 매핑
  (`bg-background`, `text-foreground` 등 유틸로 노출).
- `src/lib/utils.ts` — `cn()` (clsx + tailwind-merge).
- `src/components/ui/*` — Button(CVA), Card, Input, Label(Radix), Checkbox(Radix + lucide).
- 다크모드: 루트에 `.dark` 클래스 토글(CSS 변수 교체).

> 참고: shadcn 의 Select 는 Radix 기반으로 장황해서, 데모에선 input 스타일을 입힌
> native `<select>` 로 대체했다(다른 컴포넌트는 shadcn 구조 그대로).

## 데모 사양 (모든 프레임워크 공통)

1. 다크모드 토글
2. Buttons — default / outline / ghost / with icon / disabled
3. Card — title + body + actions
4. Form — text input · select · checkbox(Radix) · submit → 제출 결과(JSON) 표시

## 메모

- 번들(첫 빌드): JS ~185.4KB / gzip ~59.8KB + CSS ~11.8KB / gzip ~3.2KB
- 컴포넌트 소스를 직접 소유 → 완전 커스터마이즈 가능, 잠금(lock-in) 없음
- 셋업이 가장 손이 많이 감(별칭/토큰/컴포넌트 복사)
