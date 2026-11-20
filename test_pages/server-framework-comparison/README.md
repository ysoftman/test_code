# Server Framework Comparison

Express · Fastify · Hono · Koa · Elysia · NestJS 의 특징·장단점 비교와, 이 머신에서 실측한 HTTP 벤치마크 결과를 보여 주는 단일 정적 페이지.

- `index.html` — 비교표, 프레임워크별 카드, 벤치마크 차트 (빌드 단계 없음)
- `results.json` — `bench.sh` 가 만든 실측 결과. 페이지가 `fetch` 해서 렌더링한다
- `bench.sh`, `server-*.js` — 측정 스크립트와 프레임워크별 서버

NestJS 는 실측 대상이 아니다 (비교표와 카드에만 있다).

## 재측정

`node`, `bun`, `oha`, `jq`, `curl` 이 필요하다.

```bash
bun install
bun run bench
```

부하 시간과 동시 연결 수는 환경변수로 바꾼다 (기본 10초, 64).

```bash
HTTP_SECS=30 CONNS=128 bun run bench
```

결과는 `results.json` 에 덮어쓰이고, 페이지는 수정 없이 새 값을 그린다.

## 로컬에서 보기

`results.json` 을 `fetch` 하므로 파일을 직접 열지 말고 정적 서버로 연다.

```bash
cd test_pages
python3 -m http.server 8000
# http://localhost:8000/server-framework-comparison/
```
