# Particle Blaster

비행체로 바위를 쏘아 잘게 쪼개 파괴하는 Asteroids 스타일 슈팅 게임.
바위는 총알에 맞을 때마다 더 작은 3조각으로 분열하고, 최소 크기에서는 먼지로 사라진다.

## 기술 스택

Vite + TypeScript + Pixi.js(렌더링) + Matter.js(물리) + Biome + bun

## 실행

```sh
bun install
bun run dev
```

## 조작

| 키 | 동작 |
|---|---|
| WASD / 방향키 | 이동 · 회전 |
| Space | 발사 |
| R | 게임 오버 후 재시작 |

## 구조

- `src/core/` — 물리 월드, 렌더러, 게임 루프
- `src/entities/` — 비행체, 총알, 바위(분열), 먼지
- `src/game/` — 키보드 입력, HUD, 웨이브 스포너
- `src/main.ts` — 충돌 규칙 등 통합 와이어링
- `src/constants.ts` — 색상/물리/게임플레이 튜닝 값

## 스크립트

```sh
bun run typecheck  # tsc --noEmit
bun run lint       # biome check
bun run format     # biome check --write
bun run build      # 프로덕션 빌드
```
