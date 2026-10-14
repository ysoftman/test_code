# Formatter Benchmark

`bun fmt`(main 브랜치 canary 빌드) · [Biome](https://biomejs.dev/) · [Prettier](https://prettier.io/) 의 포맷 속도와 출력을 비교한다.

`bun fmt` 은 [oven-sh/bun#44805](https://github.com/oven-sh/bun/pull/44805) 로 main 에 들어왔고 아직 태그 릴리스가 없어서, main 최신 빌드인 [canary 릴리스](https://github.com/oven-sh/bun/releases/tag/canary) 바이너리를 내려받아 쓴다.

벤치마크는 로컬에서 돌리고, 결과(`results.json`)를 커밋해 GitHub Pages 에서 `index.html` 로 보여준다. CI 에서는 측정하지 않는다.

## 요구 사항

- [bun](https://bun.sh/)
- [hyperfine](https://github.com/sharkdp/hyperfine), jq, rsync, git

## 측정

```bash
bun install      # prettier, @biomejs/biome (버전 고정)
bun run bench    # canary bun 다운로드 → 코퍼스 생성 → hyperfine → results.json
```

| 환경변수    | 기본값                           | 설명                                  |
| ----------- | -------------------------------- | ------------------------------------- |
| `BUN`       | canary 다운로드                  | 측정할 bun 바이너리                   |
| `COPIES`    | `40`                             | large 코퍼스 복제 수                  |
| `BENCH_TMP` | `$TMPDIR/formatter-benchmark`    | 코퍼스·작업 디렉토리 (repo 밖이어야 함) |

### 방법

- 코퍼스: `test_web_page` 의 git 추적 소스(`html, css, js, jsx, ts, tsx, vue, json`). 이 디렉토리와 하위 프로젝트의 `biome.json` 은 제외.
  - `small` 원본 1벌, `large` 를 `COPIES` 벌 복제, `html` / `css` / `js` 는 `large` 에서 언어별로 추림.
- 속도: hyperfine 쓰기 모드(`--write`), 워밍업 1회, 실행마다 `--prepare` 로 코퍼스 원복(측정 제외).
- 출력 일치: `small` 을 각 도구로 포맷한 결과를 Prettier 결과와 파일 단위로 바이트 비교.
- Biome 은 HTML 포맷터가 기본 off(실험적)라 켜고, Prettier 에 가깝도록 `indentStyle: space`, `indentScriptAndStyle`(.vue 는 끔 — Prettier 의 `vueIndentScriptAndStyle` 기본값이 false), `selfCloseVoidElements: always` 로 맞춘다 (`bench.sh` 안의 `biome.json`).

## 확인 (로컬)

`index.html` 이 `results.json` 을 fetch 하므로 파일로 직접 열지 말고 정적 서버로 연다.

```bash
bun run serve    # http://localhost:3000
```
