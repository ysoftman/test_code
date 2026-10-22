// 바위 — 파괴 가능한 소행성. 총알에 맞으면 더 작은 조각들(+먼지)로
// 분열하고, 최소 크기에서는 먼지로만 흩어져 사라진다.
import { Bodies, Body } from "matter-js";
import type { Container } from "pixi.js";
import { Graphics } from "pixi.js";
import { COLLISION, COLORS, DUST, ROCK } from "../constants";
import type { Entity, GameContext, RockEntity } from "../types";
import { createDustBurst } from "./dust";

const SIZE_FACTOR = 1.7; // 반지름 = baseRadius * SIZE_FACTOR ** sizeLevel
const BODY_RADIUS_RATIO = 0.9; // 물리 원은 시각 폴리곤보다 약간 작게
const FRAGMENT_PLACEMENT_RATIO = 0.55; // 분열 조각은 부모 반지름 안쪽에서 시작
const MAX_INITIAL_SPIN = 0.05; // 틱당 회전(rad)

function rockRadius(sizeLevel: number): number {
  return ROCK.baseRadius * SIZE_FACTOR ** sizeLevel;
}

function rockColor(sizeLevel: number): number {
  const index = Math.max(0, Math.min(sizeLevel, COLORS.rockLevels.length - 1));
  return COLORS.rockLevels[index];
}

function clampSpeed(vx: number, vy: number): { x: number; y: number } {
  const speed = Math.hypot(vx, vy);
  if (speed <= ROCK.maxSpeed) return { x: vx, y: vy };
  const k = ROCK.maxSpeed / speed;
  return { x: vx * k, y: vy * k };
}

export class Rock implements RockEntity {
  readonly kind = "rock" as const;
  readonly sizeLevel: number;
  readonly body: Body;
  readonly view: Container;
  alive = true;

  private readonly radius: number;

  constructor(x: number, y: number, sizeLevel: number, vx = 0, vy = 0) {
    this.sizeLevel = sizeLevel;
    this.radius = rockRadius(sizeLevel);

    // 원형 body(시각보다 약간 작게)를 사용해 오목 폴리곤 분해를 피하면서도
    // 게임플레이에 충분한 충돌 정확도를 유지한다.
    this.body = Bodies.circle(x, y, this.radius * BODY_RADIUS_RATIO, {
      frictionAir: ROCK.frictionAir,
      restitution: ROCK.restitution,
      collisionFilter: {
        category: COLLISION.rock,
        mask: COLLISION.ship | COLLISION.bullet | COLLISION.rock,
      },
    });
    Body.setVelocity(this.body, clampSpeed(vx, vy));
    Body.setAngularVelocity(this.body, (Math.random() * 2 - 1) * MAX_INITIAL_SPIN);

    // 울퉁불퉁한 폴리곤: 랜덤 꼭짓점 개수 + 반지름 지터.
    const span = ROCK.vertexCount.max - ROCK.vertexCount.min;
    const count = ROCK.vertexCount.min + Math.floor(Math.random() * (span + 1));
    const points: number[] = [];
    for (let i = 0; i < count; i++) {
      const angle = (i / count) * Math.PI * 2;
      const r = this.radius * (1 + (Math.random() * 2 - 1) * ROCK.radiusJitter);
      points.push(Math.cos(angle) * r, Math.sin(angle) * r);
    }
    const g = new Graphics();
    g.poly(points).fill(rockColor(sizeLevel));
    this.view = g;
  }

  update(_dtMs: number, _ctx: GameContext): void {
    // 충돌로 바위가 가속될 수 있으므로 속도를 한도 내로 유지한다.
    const v = this.body.velocity;
    if (Math.hypot(v.x, v.y) > ROCK.maxSpeed) {
      Body.setVelocity(this.body, clampSpeed(v.x, v.y));
    }
  }

  split(hitX: number, hitY: number): Entity[] {
    this.alive = false;
    const { x: cx, y: cy } = this.body.position;
    const color = rockColor(this.sizeLevel);

    // 최소 크기 바위는 큰 먼지 버스트로 흩어져 사라진다.
    if (this.sizeLevel <= 0) {
      return createDustBurst(cx, cy, DUST.countFinal, color);
    }

    const spawned: Entity[] = [];
    // 조각들은 방사형으로 퍼진다; 첫 조각은 피격 지점 반대 방향으로 날아간다.
    const awayAngle = Math.atan2(cy - hitY, cx - hitX);
    const n = ROCK.splitCount;
    for (let i = 0; i < n; i++) {
      const angle = awayAngle + (i / n) * Math.PI * 2 + (Math.random() - 0.5) * 0.5;
      const dx = Math.cos(angle);
      const dy = Math.sin(angle);
      // 조각이 겹쳐 스폰되지 않도록 부모 내부에 분산 배치한다.
      const fx = cx + dx * this.radius * FRAGMENT_PLACEMENT_RATIO;
      const fy = cy + dy * this.radius * FRAGMENT_PLACEMENT_RATIO;
      const vx = this.body.velocity.x + dx * ROCK.splitImpulse;
      const vy = this.body.velocity.y + dy * ROCK.splitImpulse;
      spawned.push(new Rock(fx, fy, this.sizeLevel - 1, vx, vy));
    }
    spawned.push(...createDustBurst(hitX, hitY, DUST.countSmall, color));
    return spawned;
  }
}

/** 통합 시 합의된 시그니처의 팩토리 함수. */
export function createRock(x: number, y: number, sizeLevel: number, vx = 0, vy = 0): Rock {
  return new Rock(x, y, sizeLevel, vx, vy);
}
