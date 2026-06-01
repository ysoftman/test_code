# CSS / UI Framework Comparison

MUI, Tailwind CSS, Panda CSS 등 7개 주요 스타일링 솔루션을 **같은 데모 UI**로 1:1 비교한다.

bun workspaces + Vite 로 프레임워크별 독립 앱을 두고(공정 비교), 빌드 결과를 GitHub Pages 로 서빙한다.

## 요구 사항

- [bun](https://bun.sh/) (워크스페이스 / 패키지 매니저)

## 빌드

설치는 이 디렉토리(`css-framework-comparison/`) 루트에서 **한 번만**:

```bash
bun install
```

전체 프레임워크 앱 빌드:

```bash
bun run build:all        # 각 앱이 자기 dist/ 생성
```

특정 앱만 빌드:

```bash
cd mui && bun run build  # mui/dist/ 생성
```

> 각 앱의 `vite.config.ts` 는 `base` 를 `/test_code/css-framework-comparison/<name>/` 로
> 설정한다 (GitHub Pages 하위 경로). 로컬에서 `dist/index.html` 을 파일로 직접 열면
> 경로가 맞지 않으니 아래 "확인" 방법을 사용한다.

## 확인 (로컬)

### 1) 개발 서버 (구현/디버깅용, HMR)

```bash
bun run dev:mui          # mui (그 외 dev:tailwind / dev:panda / dev:chakra / dev:shadcn / dev:styled / dev:vanilla)
```

→ 출력된 `http://localhost:5173` 접속. dev 모드는 `base` 가 `/` 라 바로 열린다. 소스 수정 시 즉시 반영(HMR).

### 2) 7개 한 화면 비교 (배포본과 동일)

```bash
bun run preview:all      # build:all → _site 조립 → 정적 서버
```

→ `http://localhost:3000/test_code/css-framework-comparison/` 에서 7개를 한 페이지에 비교.

- 내부적으로 `preview-all.sh` 가 빌드 결과를 `.preview/test_code/...` 로 모아 `python3 -m http.server` 로 서빙(`base` 경로 일치).
- 랜딩 HTML 은 심볼릭 링크라 **비교 페이지(index.html) 수정 → 새로고침만** 하면 반영(앱 소스는 재빌드 필요).
- 포트 변경: `PORT=8080 bash ./preview-all.sh`

### 비교 페이지 기능

- **한 화면 임베드**: 7개 데모를 iframe 으로 한 페이지에 표시(각 앱은 독립 빌드)
- **크기 조절**: 슬라이더/`±` 버튼으로 전체 확대·축소
- **전체 다크/라이트 토글**: `postMessage` 로 7개 앱 테마 일괄 전환
- **용어 설명**: CSS-in-JS / build-time / runtime / zero runtime 등 팝업 설명
- 각 앱 헤더에 **버전 + 분류** 표시(버전은 각 `package.json` 에서 import → 업그레이드 시 자동 반영)

## 배포 (GitHub Pages)

- 저장소 **Settings → Pages → Source: GitHub Actions** 1회 설정.
- `main` 브랜치에 `test_web_page/**` 변경을 push 하면
  `.github/workflows/pages.yml` 가 `bun install → build:all → _site 조립 → 배포` 수행.
- 배포 URL:
  - 랜딩: `https://ysoftman.github.io/test_code/css-framework-comparison/`
  - MUI: `https://ysoftman.github.io/test_code/css-framework-comparison/mui/`

## 새 프레임워크 추가하기

1. 폴더에 Vite 앱 생성 (`package.json`, `vite.config.ts` 의 `base` 설정, `index.html`, `src/`).
2. 루트 `package.json` 의 `workspaces` 에 폴더명 한 줄 추가.
3. `bun install` → `bun run build:all`.
   (워크플로우는 `dist/` 가 있는 앱을 자동으로 수집한다.)

## 대상 (버전은 측정 시점 기준)

| 폴더 | 이름 | 버전 | 분류 | 런타임 |
| --- | --- | --- | --- | --- |
| [`mui/`](./mui) | Material UI | 9.0 | 컴포넌트 라이브러리 (Emotion) | runtime |
| [`chakra-ui/`](./chakra-ui) | Chakra UI | 3.35 | 컴포넌트 라이브러리 (Panda 기반) | zero runtime |
| [`tailwind/`](./tailwind) | Tailwind CSS | 4.3 | 유틸리티 CSS | zero runtime |
| [`shadcn-ui/`](./shadcn-ui) | shadcn/ui | (Tailwind 4.3 + Radix) | 복붙형 컴포넌트 + 유틸리티 CSS | zero runtime |
| [`panda-css/`](./panda-css) | Panda CSS | 1.11 | CSS-in-JS (build-time) | zero runtime |
| [`vanilla-extract/`](./vanilla-extract) | vanilla-extract | 1.20 | CSS-in-JS (build-time) | zero runtime |
| [`styled-components/`](./styled-components) | styled-components | 6.4 | CSS-in-JS | runtime |

## 공통 데모 사양

모든 프레임워크가 동일하게 구현해 1:1 비교한다 (글자/간격/색/아이콘/폰트까지 통일, 스타일링 방식만 다름):

1. 다크모드 토글 (공통 SVG 아이콘)
2. Buttons — contained / outlined / text / with icon(공통 하트 SVG) / disabled
3. Card — title + body + actions
4. Form — text input · select · checkbox · submit → 제출 결과(JSON) 표시

## 측정 결과 (번들 사이즈)

프로덕션 빌드(`bun run build`) 기준, React 포함 전체 dist. **JS gzip 작은 순**.
(React 자체가 gzip ~45KB 의 공통 베이스)

| 프레임워크 | JS (gzip) | CSS (gzip) | 비고 |
| --- | --- | --- | --- |
| vanilla-extract | 148.4KB (47.9KB) | 2.6KB (0.8KB) | CSS 최소 — 사용분만 추출 |
| Tailwind | 149.6KB (48.2KB) | 11.7KB (3.2KB) | 사용한 유틸리티만 생성 |
| Panda CSS | 163.9KB (53.6KB) | 18.5KB (5.6KB) | 기본 디자인 토큰을 CSS 변수로 방출 + preflight |
| styled-components | 180.6KB (60.4KB) | — | 런타임 주입, 별도 CSS 없음 |
| shadcn/ui | 195.6KB (62.6KB) | 11.8KB (3.2KB) | Tailwind + Radix + lucide 아이콘 |
| MUI | 379.2KB (120.5KB) | — | 컴포넌트 라이브러리 + Emotion(runtime) |
| Chakra UI | 440.4KB (125.6KB) | — | 컴포넌트 라이브러리 v3 + 시스템 |

> 유틸리티/빌드타임 CSS-in-JS 가 가볍고, 완성형 컴포넌트 라이브러리(MUI·Chakra)가 무겁다.
> CSS 는 정적 추출 방식(vanilla-extract/Tailwind)이 작고, 토큰을 전부 방출하는 Panda 가 상대적으로 크다.

## 정성 비교 (런타임 / DX)

| 프레임워크 | 스타일 작성 방식 | 런타임 비용 | 타입 안전·자동완성 | 동적 스타일 | 컴포넌트 제공 | 셋업/학습 |
| --- | --- | --- | --- | --- | --- | --- |
| MUI | `sx` prop / `styled` (Emotion) | 있음 | 보통 | 자유 | ◎ 풍부(접근성 포함) | 쉬움 |
| Chakra UI | style props / 합성 컴포넌트 | 낮음(Panda) | 좋음 | 자유 | ◎ 풍부(접근성) | 보통(next-themes 등) |
| Tailwind | 유틸리티 클래스 | 없음 | 낮음(클래스 문자열) | 제한적(조건부 클래스) | ✕ 직접 작성 | 쉬움 |
| shadcn/ui | 유틸리티 + Radix(복붙 소유) | 없음 | 보통 | 제한적 | △ 복사해 소유 | 손 많음(CLI/별칭/토큰) |
| Panda CSS | `css()` 객체 (build-time) | 없음 | ◎ 토큰 검증/자동완성 | ✕ 정적 추출 제약 | ✕ 직접 작성 | 보통(codegen) |
| vanilla-extract | `.css.ts` (build-time) | 없음 | ◎ TS 그대로 | △ recipes/sprinkles 필요 | ✕ 직접 작성 | 보통 |
| styled-components | `styled\`\`` 템플릿 (runtime) | 있음 | △ DefaultTheme 보강 필요 | ◎ props 기반 최고 | ✕ 직접 작성 | 쉬움 |

핵심 트레이드오프:

- **런타임 비용 vs 동적 유연성**: runtime(MUI·styled)은 props 기반 동적 스타일에 자유롭지만 JS 비용이 있고, zero runtime(Tailwind·Panda·vanilla-extract)은 빠르지만 동적 스타일에 제약.
- **완성도 vs 가벼움**: 컴포넌트 라이브러리(MUI·Chakra)는 빨리 만들지만 번들이 크고, 유틸리티/CSS-in-JS 는 가볍지만 컴포넌트를 직접 만들어야 함.
- **타입 안전**: Panda·vanilla-extract 가 가장 강함(토큰/스타일이 TS), Tailwind 는 약함(클래스 문자열).

## 최종 비교 — 선택 가이드

- **빠른 완성형 UI / 관리자·대시보드** → **MUI** 또는 **Chakra UI** (완성 컴포넌트 + 접근성)
- **디자인 자유도 + 가벼움 + 빠른 프로토타이핑** → **Tailwind CSS**
- **Tailwind 기반인데 컴포넌트를 직접 소유·커스텀하고 싶다** → **shadcn/ui**
- **타입 안전 디자인 토큰 + zero runtime** → **Panda CSS** 또는 **vanilla-extract**
  (둘 중 번들 최소·CSS 최소가 중요하면 **vanilla-extract**)
- **props 기반 동적 스타일 / 기존 styled 코드 유지** → **styled-components**
- **번들 최소가 최우선** → **vanilla-extract** > **Tailwind**

> 정성 평가는 일반적 경향이며 프로젝트 요구(SSR/RSC, 팀 숙련도, 디자인 시스템 유무)에 따라 달라질 수 있다.

## 진행 상태

- [x] 폴더 스캐폴드
- [x] 빌드 / 배포 파이프라인 (bun + Vite + Pages)
- [x] 7개 프레임워크 구현 (MUI · Tailwind · Panda · Chakra · shadcn · styled-components · vanilla-extract)
- [x] 최신 버전 업그레이드
- [x] 데모 일관성 정렬 (크기/간격/색/아이콘/폰트 통일)
- [x] 비교 페이지 (한 화면 임베드 · 크기조절 · 일괄 테마 · 용어 설명)
- [x] 번들 사이즈 측정
- [x] 런타임/DX 정성 비교 정리
- [x] 최종 비교 / 선택 가이드 정리
