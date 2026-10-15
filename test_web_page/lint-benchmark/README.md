# Lint Benchmark

`bun lint`(main 브랜치 canary 빌드) · [oxlint](https://oxc.rs/docs/guide/usage/linter) · [Biome](https://biomejs.dev/) · [ESLint](https://eslint.org/) 에 같은 규칙 세트를 걸었을 때의 린트 속도와 진단 결과를 비교한다.

`bun lint` 은 아직 태그 릴리스가 없어서, [formatter-benchmark](../formatter-benchmark/) 와 같이 main 최신 빌드인 [canary 릴리스](https://github.com/oven-sh/bun/releases/tag/canary) 바이너리를 내려받아 쓴다. main 을 직접 빌드한 바이너리는 `BUN=` 으로 넘긴다.

벤치마크는 로컬에서 돌리고, 결과(`results.json`)를 커밋해 GitHub Pages 에서 `index.html` 로 보여준다. CI 에서는 측정하지 않는다.

## 요구 사항

- [bun](https://bun.sh/), node
- [hyperfine](https://github.com/sharkdp/hyperfine), jq, rsync, git

## 측정

```bash
bun install      # eslint, typescript-eslint, oxlint, @biomejs/biome (버전 고정)
bun run bench    # canary bun 다운로드 → 규칙 세트·코퍼스 생성 → hyperfine → results.json
```

| 환경변수    | 기본값                     | 설명                                    |
| ----------- | -------------------------- | --------------------------------------- |
| `BUN`       | canary 다운로드            | 측정할 bun 바이너리                     |
| `COPIES`    | `40`                       | large 코퍼스 복제 수                    |
| `BENCH_TMP` | `$TMPDIR/lint-benchmark`   | 코퍼스·설정 디렉토리 (repo 밖이어야 함) |

### 방법

- 규칙: `eslint:recommended` 중 네 도구가 모두 지원하는 규칙만 전부 `warn` 으로 켠다.
  - Biome 대응은 규칙마다 `biome migrate eslint` 로 뽑는다 (`--include-inspired` 없이 = 동작이 같은 규칙만). 두 ESLint 규칙이 같은 Biome 규칙에 대응하면 뒤의 것을 뺀다.
  - 쓴 규칙과 뺀 규칙(이유 포함)은 `results.json` 의 `rules`, `excluded` 에 남는다.
- 설정: ESLint 와 bun lint 은 같은 `eslint.config.mjs`(TS 는 `typescript-eslint` 파서, 브라우저·Node 전역), oxlint 은 `oxlintrc.json`, Biome 은 `biome.json`(`preset: none`). 설정은 코퍼스 밖에 두고 `-c` / `--config-path` 로 넘긴다.
- 코퍼스: `test_web_page` 의 git 추적 소스(`js, jsx, ts, tsx`). 이 디렉토리와 formatter-benchmark, `.eslintrc*` 는 제외. Vue 는 bun lint · oxlint 대상이 아니라 뺐다.
  - `small` 원본 1벌, `large` 를 `COPIES` 벌 복제, `js` / `ts` 는 `large` 에서 언어별로 추림.
- 속도: hyperfine `-N`, 워밍업 1회. 파일을 바꾸지 않으므로 원복 없이 반복한다. ESLint 는 기본(싱글스레드)과 `--concurrency=auto` 를 둘 다 잰다. 캐시는 모든 도구에서 꺼진 상태(ESLint `--cache` 미사용, 나머지는 캐시 없음).
- 진단 일치: `small` 의 진단을 `(파일, 줄, ESLint 규칙명)` 으로 모아 ESLint 결과와 비교한다.
- oxlint 의 npm 배포본은 Node 래퍼 + napi 바인딩이라 Node 시작 시간이 측정에 포함된다. Biome 은 formatter-benchmark 와 같이 네이티브 바이너리를 직접 쓴다.
- type-aware 규칙(`bun lint --type-aware`, typescript-eslint `projectService`)은 재지 않는다.

## 확인 (로컬)

`index.html` 이 `results.json` 을 fetch 하므로 파일로 직접 열지 말고 정적 서버로 연다.

```bash
bun run serve    # http://localhost:3000
```
