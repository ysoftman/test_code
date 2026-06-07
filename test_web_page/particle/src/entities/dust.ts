// 먼지 — 물리 body 가 없는 순수 시각 파티클 (body: null).
// 자체 속도로 움직이며 감속·페이드아웃 후 스스로 소멸한다.
import type { Container } from "pixi.js";
import { Graphics } from "pixi.js";
import { COLORS, DUST } from "../constants";
import type { Entity, GameContext } from "../types";

const FRAME_MS = 1000 / 60;
const DRAG = 0.94; // 60fps 프레임당 속도 감쇠 배율

export class Dust implements Entity {
  readonly kind = "dust" as const;
  readonly body: null = null;
  readonly view: Container;
  alive = true;

  private vx: number;
  private vy: number;
  private ageMs = 0;

  constructor(x: number, y: number, vx: number, vy: number, color: number = COLORS.dust) {
    this.vx = vx;
    this.vy = vy;

    const g = new Graphics();
    const size = 1 + Math.random() * 1.8;
    g.rect(-size / 2, -size / 2, size, size).fill(color);
    g.position.set(x, y);
    g.rotation = Math.random() * Math.PI; // 다양성을 위한 랜덤 방향
    this.view = g;
  }

  update(dtMs: number, ctx: GameContext): void {
    const dtScale = dtMs / FRAME_MS;

    // 물리 body 가 없으므로 뷰 위치를 직접 적분한다.
    this.view.x += this.vx * dtScale;
    this.view.y += this.vy * dtScale;
    const drag = DRAG ** dtScale;
    this.vx *= drag;
    this.vy *= drag;

    this.ageMs += dtMs;
    this.view.alpha = Math.max(0, 1 - this.ageMs / DUST.lifeMs);
    if (this.ageMs >= DUST.lifeMs) ctx.kill(this);
  }
}

/** 랜덤 방향으로 터져 나가는 먼지 파티클 `count` 개를 생성한다. */
export function createDustBurst(
  x: number,
  y: number,
  count: number,
  color: number = COLORS.dust,
): Dust[] {
  const burst: Dust[] = [];
  for (let i = 0; i < count; i++) {
    const angle = Math.random() * Math.PI * 2;
    const speed = (0.3 + Math.random() * 0.7) * DUST.speed;
    burst.push(new Dust(x, y, Math.cos(angle) * speed, Math.sin(angle) * speed, color));
  }
  return burst;
}
