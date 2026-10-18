# Runtime Benchmark

[Node.js](https://nodejs.org/) · [Deno](https://deno.com/) · [Bun](https://bun.sh/) 에서 같은 스크립트를 실행했을 때의 시작 시간, 연산 · I/O 처리 시간, 피크 메모리, HTTP 처리량을 비교한다.

벤치마크는 로컬에서 돌리고, 결과(`results.json`)를 커밋해 GitHub Pages 에서 `index.html` 로 보여준다. CI 에서는 측정하지 않는다. 런타임은 설치된 버전을 그대로 쓴다.

## 요구 사항

- node, deno, bun
- [hyperfine](https://github.com/sharkdp/hyperfine), [oha](https://github.com/hatoo/oha), jq, curl, git

## 측정

```bash
bun run bench    # 출력 일치 확인 → hyperfine → oha → results.json
```

| 환경변수    | 기본값                       | 설명                      |
| ----------- | ---------------------------- | ------------------------- |
| `HTTP_SECS` | `10`                         | HTTP 부하 시간(초)        |
| `CONNS`     | `64`                         | HTTP 동시 연결 수         |
| `PORT`      | `3456`                       | HTTP 서버 포트            |
| `BENCH_TMP` | `$TMPDIR/runtime-benchmark`  | hyperfine · oha 중간 결과 |

### 워크로드

`serve.js` 를 뺀 `workloads/` 의 파일은 표준 JS 와 `node:` 모듈만 써서 세 런타임에서 그대로 실행된다. 측정 전에 세 런타임의 stdout 이 같은지 먼저 확인하고, 다르면 중단한다.

| 파일            | 내용                                                 |
| --------------- | ---------------------------------------------------- |
| `startup.js`    | `console.log` 한 줄 — 기동 + 종료                    |
| `startup-ts.ts` | 타입 주석이 있는 `.ts` 직접 실행 (node 는 type stripping) |
| `fib.js`        | `fib(38)` 재귀 호출                                  |
| `json.js`       | 10만 객체 `JSON.stringify` → `JSON.parse` × 10       |
| `sort.js`       | 100만 객체 비교 정렬 + 30만 문자열 정렬              |
| `crypto.js`     | `node:crypto` sha256 512 MB                          |
| `fs.js`         | `node:fs` 동기 API 로 4 KB × 5000 쓰기 · 읽기 · 삭제 |
| `serve.js`      | HTTP 서버 (`HTTP_API=native` 기본 API / `node` node:http) |

### 방법

- 실행: `node 파일` · `deno run -A 파일` · `bun 파일`. `package.json` 의 `"type": "module"` 을 읽도록 이 디렉토리에서 실행한다.
- 속도 · 메모리: hyperfine `-N`, 시작 시간 워크로드는 워밍업 3회 · 30회, 나머지는 워밍업 1회 · 10회. 프로세스 전체 시간이라 시작 시간이 포함된다. 메모리는 피크 RSS(`memory_usage_byte`) 의 최댓값.
  - hyperfine 의 메모리 값은 자식 프로세스 누적 최댓값(`RUSAGE_CHILDREN`)이라 한 번에 여러 런타임을 재면 앞 런타임의 RSS 가 뒤로 이어진다. 그래서 런타임마다 hyperfine 을 따로 돌린다.
  - 같은 런타임의 반복 실행 안에서도 값이 누적 최댓값(워밍업 포함)이라 평균이 아닌 최댓값을 쓴다.
- HTTP: `oha -c $CONNS`, 워밍업 2초 후 `$HTTP_SECS` 초 측정. 런타임 기본 API(`Bun.serve` · `Deno.serve` · `node:http`) 와, 세 런타임 모두 `node:http` 로 띄운 경우를 잰다. node 의 기본 API 가 `node:http` 라 node 는 한 번만 재서 두 그룹에 같이 보여준다. 서버 RSS 는 부하 직후 `ps` 값.
  - oha 의 `successRate` 는 연결 수준이라 500 응답도 성공으로 센다. 그래서 응답 상태 코드가 모두 200 이 아니면 중단한다.
  - 중간에 실패하거나 Ctrl-C 로 멈추면 띄운 서버를 정리하고, 잘린 측정은 기록하지 않는다.
- 부하 생성기(oha)와 서버가 같은 머신에서 CPU 를 나눠 쓰므로 절대 수치보다 런타임 간 비율로 본다.

## 확인 (로컬)

`index.html` 이 `results.json` 을 fetch 하므로 파일로 직접 열지 말고 정적 서버로 연다.

```bash
bun run serve    # http://localhost:3000
```
