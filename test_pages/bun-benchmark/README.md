# Bun Benchmark

Formatter, lint, runtime, test, bundler 벤치마크는 각각 별도 결과 페이지에서 확인한다. 상위 `test_pages` 페이지에서 다섯 결과 페이지로 바로 이동할 수 있고, 측정 파일은 접두사로 구분한다.

## 설치 및 실행

의존성을 설치한다.

```bash
cd bun-benchmark
bun install
```

필요한 벤치마크만 실행한다. 결과는 각각 `formatter-results.json`, `lint-results.json`, `runtime-results.json`, `test-results.json`, `bundler-results.json`에 기록한다.

```bash
bun run bench:formatter
bun run bench:lint
bun run bench:runtime
bun run bench:test
bun run bench:bundler
```

`bun run serve`를 실행하면 `http://localhost:3000/`에서 Formatter 페이지가 열린다. Formatter, Lint, Runtime, Test, Bundler 페이지는 각각 `/formatter`, `/lint`, `/runtime`, `/test`, `/bundler`에서 볼 수 있으며, 상위 `test_pages` 목록에서도 다섯 페이지로 바로 이동할 수 있다.

- [`formatter.html`](formatter.html): Prettier · Biome · bun fmt의 포맷 속도와 출력 일치율
- [`lint.html`](lint.html): ESLint · oxlint · Biome · bun lint의 린트 속도와 진단 결과
- [`runtime.html`](runtime.html): Node.js · Deno · Bun의 시작 시간, 연산, 메모리, HTTP 처리량
- [`test.html`](test.html): Jest · Vitest · node --test · Deno · Bun 테스트 러너의 실행 시간
- [`bundler.html`](bundler.html): esbuild · Rolldown · Vite · Rspack · Rollup · webpack · bun build의 번들링 시간과 결과물 크기

## Formatter

`bun fmt`은 main 브랜치 canary 빌드를 내려받아 사용한다. `BUN`으로 직접 빌드한 바이너리를 지정할 수 있다. 코퍼스는 저장소의 추적된 HTML, CSS, JS, TS, Vue, JSON 파일로 구성하며 `bun-benchmark/`는 제외한다. 속도 측정은 hyperfine 쓰기 모드로 수행하고, Prettier 결과와 Biome·Bun 출력의 일치율도 비교한다.

큰 코퍼스는 `COPIES`만큼 복제하며 기본값은 40이다. 각 실행 전 코퍼스를 원복하고 워밍업 1회 후 측정한다. Biome HTML 포맷터를 켜고, Prettier와 가깝도록 공백 들여쓰기와 void element self-close 설정을 맞춘다.

```bash
bun run bench:formatter
```

## Lint

`bun lint`도 main 브랜치 canary 빌드를 사용하며 `BUN`으로 직접 지정할 수 있다. ESLint recommended 중 Bun, oxlint, Biome이 모두 지원하는 규칙을 비교하고, 같은 코퍼스의 속도와 ESLint 진단 일치율을 측정한다. 캐시는 끈 상태로 측정한다.

규칙은 각 도구에서 같은 의미로 지원되는 것만 `warn`으로 활성화한다. 진단은 파일, 줄, ESLint 규칙 이름으로 비교하고, 포함·제외 규칙을 `lint-results.json`에 기록한다. ESLint 기본 단일 스레드와 `--concurrency=auto`를 모두 측정한다. Type-aware lint는 측정하지 않는다.

```bash
bun run bench:lint
```

## Runtime

설치된 Node.js, Deno, Bun 버전을 그대로 사용한다. 공통 워크로드의 출력 일치 여부를 먼저 확인한 뒤 hyperfine으로 시간과 피크 메모리를 측정하고, oha로 HTTP 처리량을 측정한다. 워크로드 파일은 `runtime-` 접두사를 사용한다.

| 파일 | 워크로드 |
| --- | --- |
| `runtime-startup.js` | 한 줄 출력 후 종료 |
| `runtime-startup-ts.ts` | 타입 주석이 있는 TypeScript 직접 실행 |
| `runtime-fib.js` | 재귀 `fib(38)` |
| `runtime-json.js` | 10만 객체 stringify/parse 반복 |
| `runtime-sort.js` | 객체와 문자열 정렬 |
| `runtime-crypto.js` | `node:crypto` SHA-256 해시 |
| `runtime-fs.js` | 동기 파일 쓰기·읽기·삭제 |
| `runtime-serve.js` | 기본 HTTP API 및 `node:http` 서버 |

시작 시간 워크로드는 워밍업 3회와 30회 측정, 나머지는 워밍업 1회와 10회 측정이다. hyperfine의 메모리 값은 자식 프로세스의 누적 최댓값이므로 런타임마다 따로 실행한다. HTTP는 2초 워밍업 후 `HTTP_SECS` 동안 `CONNS` 연결로 측정하고, 응답 코드가 모두 200인지 확인한다.

```bash
bun run bench:runtime
```

## Test

설치된 Node.js, Deno, Bun과 `package.json`에 고정한 Jest, Vitest를 사용한다. 같은 TS 테스트를 러너마다 `test`·`expect` import 한 줄만 바꿔 만들고, 테스트 파일마다 `src` 모듈 하나를 import 한다. `expect`는 러너 자체 것을 쓴다. Jest는 `@swc/jest`로 TS를 변환하고, Deno는 `node:test`와 `jsr:@std/expect`, 자체 `expect`가 없는 Node.js만 `node:test`와 npm `expect`를 쓴다.

러너 기본 설정 그대로 측정하되, Deno는 다른 러너처럼 타입 검사를 건너뛰도록 `--no-check`를 준다. 파일을 직렬로 도는 Deno·Bun은 `--parallel`도 함께 측정한다. 측정 전에 각 러너의 통과 수가 전체 테스트 수와 같은지 확인한다. 파일 1개 코퍼스는 워밍업 3회와 20회, 스위트는 워밍업 1회와 10회 측정이다.

```bash
bun run bench:test
```

## Bundler

설치된 Bun과 `package.json`에 고정한 esbuild, Rolldown, Vite, Rspack, Rollup, webpack을 사용한다. 코퍼스는 esbuild 공식 벤치마크와 같은 three.js r108 `src`이며, npm 레지스트리에서 내려받아 1벌(small)과 `COPIES`벌(large)로 복제한다. entry가 사본마다 namespace를 전역에 걸어 tree-shaking으로 빠지는 코드가 없게 한다.

모든 번들러를 minify와 외부 sourcemap으로 실행하고, Rollup은 `@rollup/plugin-terser`, webpack·Rspack은 production 기본 minifier, Vite는 lib 모드(`iife`)에 기본 minifier(Oxc)를 쓴다. 측정 전에 각 번들을 node로 실행해 사본 수만큼 three.js가 들어 있는지 확인하고, small 결과물의 minify·gzip 크기를 기록한다. small은 워밍업 2회와 10회, large는 워밍업 1회와 5회 측정이다.

```bash
bun run bench:bundler
```

## 실행 환경 변수

| 변수 | 적용 대상 | 기본값 | 설명 |
| --- | --- | --- | --- |
| `COPIES` | Formatter, Lint / Bundler | `40` / `10` | 큰 코퍼스 복제 수 |
| `BENCH_TMP` | 전체 | `$TMPDIR/<벤치마크>-benchmark` (예: `$TMPDIR/bundler-benchmark`) | 임시 작업 디렉토리 |
| `BUN` | 전체(Runtime 제외) | canary 다운로드 (Test·Bundler 는 PATH 의 `bun`) | 측정할 Bun 바이너리 |
| `HTTP_SECS` | Runtime | `10` | HTTP 부하 시간(초) |
| `CONNS` | Runtime | `64` | HTTP 동시 연결 수 |
| `PORT` | Runtime | `3456` | HTTP 서버 포트 |
| `FILES` | Test | `200` | 스위트 테스트 파일 수 |
| `TESTS` | Test | `20` | 파일당 테스트 수 |

필요한 도구는 Bun, Node.js, Deno, hyperfine, jq, rsync, git이며 Runtime HTTP 측정에는 oha와 curl, Bundler에는 curl과 gzip도 필요하다. 각 결과 페이지는 대응하는 `*-results.json`을 fetch하므로 정적 서버로 열어야 한다.
