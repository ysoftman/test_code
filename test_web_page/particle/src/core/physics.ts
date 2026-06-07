// Matter.js 엔진 래퍼: 무중력 월드, body→entity 매핑, 충돌 디스패치.

import { type Body, Composite, Engine, Events } from "matter-js";
import type { CollisionHandler, Entity, GameContext } from "../types";

/**
 * Matter.Engine 과 Body→Entity 매핑을 소유한다.
 * 중력은 비활성화(우주 공간). 등록된 두 body 의 충돌이 시작되면
 * 매핑된 엔티티들로 등록된 CollisionHandler 를 호출한다.
 */
export class PhysicsWorld {
  readonly engine: Engine;
  private readonly bodyToEntity = new Map<Body, Entity>();
  private handler: CollisionHandler | null = null;
  private context: GameContext | null = null;

  constructor() {
    this.engine = Engine.create();
    // 우주 공간: 어느 방향으로도 중력 없음.
    this.engine.gravity.x = 0;
    this.engine.gravity.y = 0;

    Events.on(this.engine, "collisionStart", (event) => {
      const handler = this.handler;
      const context = this.context;
      if (!handler || !context) return;
      for (const pair of event.pairs) {
        const a = this.bodyToEntity.get(pair.bodyA);
        const b = this.bodyToEntity.get(pair.bodyB);
        // 매핑되지 않은 body 와 이번 프레임에 이미 죽은 엔티티는 건너뛴다.
        if (a && b && a.alive && b.alive) {
          handler(a, b, context);
        }
      }
    });
  }

  /** 게임 규칙 충돌 핸들러와 핸들러가 받을 컨텍스트를 등록한다. */
  setCollisionHandler(handler: CollisionHandler, context: GameContext): void {
    this.handler = handler;
    this.context = context;
  }

  /** 엔티티의 body 를 월드에 추가하고 충돌 조회용으로 인덱싱한다. */
  add(entity: Entity): void {
    if (!entity.body) return;
    this.bodyToEntity.set(entity.body, entity);
    Composite.add(this.engine.world, entity.body);
  }

  /** 엔티티의 body 를 월드에서 제거하고 매핑도 삭제한다. */
  remove(entity: Entity): void {
    if (!entity.body) return;
    this.bodyToEntity.delete(entity.body);
    Composite.remove(this.engine.world, entity.body);
  }

  /** body 를 소유한 엔티티 조회 (디버깅이나 커스텀 쿼리용). */
  entityOf(body: Body): Entity | undefined {
    return this.bodyToEntity.get(body);
  }

  /** 물리 시뮬레이션을 dtMs 밀리초만큼 진행한다. */
  update(dtMs: number): void {
    Engine.update(this.engine, dtMs);
  }
}
