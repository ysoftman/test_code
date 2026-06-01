# CSS / UI Framework Comparison

MUI, Tailwind CSS, Panda CSS 등 주요 스타일링 솔루션을 같은 UI 예제로 비교하기 위한 디렉토리.

bun workspaces + Vite 로 프레임워크별 독립 앱을 두고, 빌드 결과를 GitHub Pages 로 서빙한다.

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

### 1) 개발 서버 (구현/디버깅용, 핫리로드)

```bash
bun run dev:mui          # 루트에서 mui 개발 서버
# 또는
cd mui && bun run dev
```

→ 출력된 `http://localhost:5173` 접속. dev 모드는 `base` 가 `/` 라 바로 열린다.

### 2) 빌드 결과 미리보기 (배포본과 동일)

```bash
cd mui && bun run build && bun run preview
```

→ vite preview 가 `base` 경로까지 반영해 서빙한다. 출력된 URL 로 접속해 확인.

### 3) Pages 와 동일하게 전체 묶어서 확인

배포와 똑같이 정적 랜딩 + 각 빌드 결과를 한 폴더(`_site`)로 모아 정적 서버로 연다:

```bash
# css-framework-comparison/ 루트에서
bun run build:all

# 저장소 루트(test_code/)로 이동 후 _site 조립
cd ../..
rm -rf _site && mkdir -p _site/css-framework-comparison
cp test_web_page/index.html _site/index.html
cp test_web_page/css-framework-comparison/index.html _site/css-framework-comparison/index.html
for dir in test_web_page/css-framework-comparison/*/; do
  app=$(basename "$dir")
  [ -d "$dir/dist" ] && mkdir -p "_site/css-framework-comparison/$app" \
    && cp -r "$dir/dist/." "_site/css-framework-comparison/$app/"
done

# /test_code/ 하위 경로를 흉내내 정적 서버 실행
bunx serve _site            # 또는: python3 -m http.server --directory _site 8080
```

> base 경로가 `/test_code/...` 라서, 정확히 같게 확인하려면 `_site` 를
> `test_code/` 라는 폴더명 아래에 두고 그 상위에서 서버를 띄우면 된다.

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

## 대상

| 폴더 | 이름 | 분류 | 런타임 비용 | 상태 |
| --- | --- | --- | --- | --- |
| [`mui/`](./mui) | Material UI | 컴포넌트 라이브러리 | runtime CSS-in-JS (Emotion) | ✅ 구현 |
| [`tailwind/`](./tailwind) | Tailwind CSS | 유틸리티 CSS | zero runtime | ✅ 구현 |
| [`panda-css/`](./panda-css) | Panda CSS | CSS-in-JS (build-time) | zero runtime | ✅ 구현 |
| [`chakra-ui/`](./chakra-ui) | Chakra UI | 컴포넌트 라이브러리 | (v3) Panda 기반 | ✅ 구현 |
| [`shadcn-ui/`](./shadcn-ui) | shadcn/ui | 복붙형 컴포넌트 + Tailwind | zero runtime | ✅ 구현 |
| [`styled-components/`](./styled-components) | styled-components | CSS-in-JS | runtime | ✅ 구현 |
| [`vanilla-extract/`](./vanilla-extract) | vanilla-extract | CSS-in-JS (build-time) | zero runtime | ✅ 구현 |

## 공통 데모 사양

모든 프레임워크가 동일하게 구현해 1:1 비교한다:

1. 다크모드 토글
2. Buttons — contained / outlined / text / with icon / disabled
3. Card — title + body + actions
4. Form — text input · select · checkbox · submit → 제출 결과(JSON) 표시

## 측정 결과 (번들 사이즈)

프로덕션 빌드(`bun run build`) 기준. React 포함 전체 dist 크기.

JS 작은 순으로 정렬. (React ~140KB(gzip ~45KB)가 공통 베이스)

| 프레임워크 | JS (gzip) | CSS (gzip) | 비고 |
| --- | --- | --- | --- |
| vanilla-extract | 146.6KB (47.2KB) | 2.6KB (0.8KB) | CSS 최소 — 사용분만 추출 |
| Tailwind | 147.9KB (47.5KB) | 11.7KB (3.2KB) | 유틸리티만 생성 |
| Panda CSS | 162.1KB (53.0KB) | 18.4KB (5.6KB) | 토큰 CSS 변수 전체 방출 + preflight |
| styled-components | 178.8KB (59.7KB) | — | 런타임 주입, 별도 CSS 없음 |
| shadcn/ui | 185.4KB (59.8KB) | 11.8KB (3.2KB) | Tailwind + Radix + lucide 아이콘 |
| MUI | 374.9KB (117.3KB) | — | 컴포넌트 라이브러리 + Emotion(runtime) |
| Chakra UI | 438.4KB (124.9KB) | — | 컴포넌트 라이브러리 v3 + 시스템(런타임 주입) |

> 같은 데모(버튼/카드/폼)를 구현했을 때 수치. 프레임워크 추가 시 갱신.

## 비교 기준 (작성 예정)

- 번들 사이즈 / 런타임 오버헤드
- DX (타입 안전성, 자동완성, 학습 곡선)
- 테마/디자인 토큰 지원
- 다크 모드 처리
- SSR / RSC 호환성
- 동일 컴포넌트(버튼, 카드, 폼) 구현 비교

## 진행 상태

- [x] 폴더 스캐폴드
- [x] 빌드 / 배포 파이프라인 (bun + Vite + Pages)
- [x] MUI 구현
- [x] Tailwind 구현
- [x] Panda 구현
- [x] 후보 4종 구현 (styled-components / vanilla-extract / Chakra UI / shadcn/ui)
- [x] 번들 사이즈 측정
- [ ] 런타임/DX 정성 비교 정리
- [ ] 최종 비교 정리
