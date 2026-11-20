# Language History

[Go](https://go.dev/) · [Rust](https://www.rust-lang.org/) · [Python](https://www.python.org/) · [JavaScript](https://tc39.es/) 의 버전별 굵직한 변화(문법 · 표준 라이브러리 · 툴체인 · 런타임)와, 서드파티 툴이 난립하다가 빠르거나 공식 내장된 하나로 수렴하는 흐름을 언어별로 정리한다.

빌드 없는 정적 HTML 묶음이다. 데이터는 각 페이지에 인라인으로 들어 있고, GitHub Pages 배포 시 디렉토리를 그대로 복사한다. 기본 스타일은 test_pages 공용 `../common/doc.css` 를 불러쓰므로 `common/` 이 이 디렉토리와 같은 깊이에 함께 있어야 한다.

## 구성

| 경로                                  | 내용                                                                                                                            |
| ------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------- |
| `index.html`                          | Overview. 언어 횡단 요약표(패키지 관리 · 린트 · 포맷 · 빌드 등)                                                                 |
| `go/` `rust/` `python/` `javascript/` | 언어별 페이지 (`index.html` 하나)                                                                                               |
| `../common/doc.css`                   | test_pages 문서 공용 스타일. 색 · 폰트 토큰(light / dark 는 `:root[data-theme]` 로 분기), 기본 타이포, 네비바, 히어로, 표, 푸터 |
| `style.css`                           | 이 문서 고유 컴포넌트(통계 카드, 타임라인, 태그, 툴 교체 차트, 상세 시트)와 태그 계열색. `doc.css` 다음에 불러온다              |
| `theme.js`                            | 테마 토글. `localStorage` 에 저장, 없으면 OS 설정을 따름                                                                        |

페이지 사이 이동은 상단 네비바의 Overview / Go / Rust / Python / JavaScript 링크로 한다. 언어별 페이지는 세 부분으로 되어 있다.

- **Releases**: 버전 타임라인. 항목마다 `lang` · `std` · `tool` · `rt` 태그로 변화 종류를 표시한다.
- **Tooling**: 카테고리별 툴 교체 차트. CSS grid 막대로, 굵기는 사용량 근사치이고 `dominant` / `common` / `niche` 로 지배적 · 병존 · 소수를, `end` 로 종료를 나타낸다.
- **상세 시트**: 타임라인 항목이나 막대를 클릭하면 열리는 배경 · 이유 설명. JS 없이 [Popover API](https://developer.mozilla.org/en-US/docs/Web/API/Popover_API)(`popovertarget`)로 띄운다.

항목을 추가할 때는 해당 페이지의 `<li class="release">` 또는 `<button class="bar">` 에 `popovertarget` 을 달고, 같은 id 의 `<aside popover>` 시트를 페이지 하단에 추가하면 된다.

출처는 각 페이지 하단 footer 에 있다. 막대 굵기는 설문 · 다운로드 통계 · GitHub 스타 · 커뮤니티 언급을 바탕으로 한 근사치이며 정확한 점유율이 아니다.

## 확인 (로컬)

링크가 디렉토리 경로(`go/`, `../`)라 파일로 직접 열면 디렉토리 목록이 나온다. 정적 서버로 연다. `../common/doc.css` 를 불러쓰므로 `serve` 스크립트는 이 디렉토리가 아니라 상위 `test_pages` 를 루트로 띄운다. 접속 주소는 `http://localhost:3000/lang-history/` 이다.

```bash
bun run serve    # http://localhost:3000/lang-history/
```
