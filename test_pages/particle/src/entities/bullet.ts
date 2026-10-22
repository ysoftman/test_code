// 총알 — 비행체 기수에서 발사되는 작은 노란색 발사체.
import { Bodies, Body } from "matter-js";
import type { Container } from "pixi.js";
import { Graphics } from "pixi.js";
import { BULLET, COLLISION, COLORS } from "../constants";
import type { Entity, GameContext } from "../types";

export class Bullet implements Entity {
  readonly kind = "bullet" as const;
  readonly body: Body;
  readonly view: Container;
  alive = true;

  private ageMs = 0;

  /**
   * @param angle 진행 방향 (라디안)
   * @param baseVx / baseVy 총알이 상속받는 발사체(비행체) 속도 (선택)
   */
  constructor(x: number, y: number, angle: number, baseVx = 0, baseVy = 0) {
    this.body = Bodies.circle(x, y, BULLET.radius, {
      frictionAir: BULLET.frictionAir,
      collisionFilter: { category: COLLISION.bullet, mask: COLLISION.rock },
    });
    Body.setVelocity(this.body, {
      x: baseVx + Math.cos(angle) * BULLET.speed,
      y: baseVy + Math.sin(angle) * BULLET.speed,
    });

    const g = new Graphics();
    g.circle(0, 0, BULLET.radius).fill(COLORS.bullet);
    this.view = g;
  }

  update(dtMs: number, ctx: GameContext): void {
    this.ageMs += dtMs;
    if (this.ageMs >= BULLET.lifeMs) ctx.kill(this);
  }
}
