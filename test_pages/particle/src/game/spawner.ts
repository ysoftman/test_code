// 웨이브 스포너 — 순수 로직 (렌더링/물리 import 없음).

import { ROCK } from "../constants";

/** 회피 지점(비행체)으로부터의 최소 스폰 거리. */
const SAFE_RADIUS = 200;

/** 스폰할 바위의 명세; main.ts 가 이를 Rock 엔티티로 변환한다. */
export interface RockSpawn {
  x: number;
  y: number;
  sizeLevel: number;
  vx: number;
  vy: number;
}

/**
 * 한 웨이브의 바위 스폰 목록을 생성한다.
 * - 개수 = ROCK.initialCount + (wave - 1)
 * - 모든 바위는 ROCK.maxLevel 로 스폰
 * - 위치는 랜덤이되 (avoidX, avoidY) 에서 최소 SAFE_RADIUS 이상 떨어짐
 * - 속도는 랜덤 방향, 크기 0.5..1.5
 */
export function waveSpawns(
  wave: number,
  width: number,
  height: number,
  avoidX: number,
  avoidY: number,
): RockSpawn[] {
  const count = ROCK.initialCount + (wave - 1);
  const spawns: RockSpawn[] = [];

  for (let i = 0; i < count; i++) {
    let x = 0;
    let y = 0;
    // 비행체 주변 안전 반경 밖의 위치를 rejection sampling 으로 고른다.
    // 아주 작은 뷰포트에서는 제한된 시도 후 그대로 통과한다.
    for (let attempt = 0; attempt < 100; attempt++) {
      x = Math.random() * width;
      y = Math.random() * height;
      const dx = x - avoidX;
      const dy = y - avoidY;
      if (dx * dx + dy * dy >= SAFE_RADIUS * SAFE_RADIUS) break;
    }

    const angle = Math.random() * Math.PI * 2;
    const speed = 0.5 + Math.random();
    spawns.push({
      x,
      y,
      sizeLevel: ROCK.maxLevel,
      vx: Math.cos(angle) * speed,
      vy: Math.sin(angle) * speed,
    });
  }

  return spawns;
}
