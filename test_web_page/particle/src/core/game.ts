// 게임 루프와 GameContext 구현: 물리 스텝, 엔티티 업데이트, 뷰 동기화,
// 화면 wrap, 지연 엔티티 제거를 하나로 묶는다.

import { Body } from "matter-js";
import type { Application, Ticker } from "pixi.js";
import type { CollisionHandler, Entity, GameContext, InputState } from "../types";
import { PhysicsWorld } from "./physics";

/** 백그라운드 탭 일시정지가 시뮬레이션을 폭주시키지 않도록 프레임 delta 를 클램프. */
const MAX_DT_MS = 50;

/**
 * Pixi ticker 가 구동하는 코어 게임 루프. GameContext 를 구현한다.
 *
 * 프레임 순서:
 *   1. dtMs 클램프 (최대 50ms)
 *   2. Matter.Engine.update (충돌 핸들러가 여기서 실행될 수 있음; kill() 은 지연 처리)
 *   3. 살아있는 모든 엔티티에 대해 entity.update(dtMs, ctx)
 *   4. 화면 밖 body 를 반대편으로 wrap 후 뷰 x/y/rotation 동기화
 *   5. alive=false 엔티티를 월드 + 스테이지에서 일괄 제거
 */
export class Game implements GameContext {
  readonly input: InputState;
  private readonly app: Application;
  private readonly physics: PhysicsWorld;
  private readonly entityList: Entity[] = [];

  constructor(app: Application, input: InputState) {
    this.app = app;
    this.input = input;
    this.physics = new PhysicsWorld();
  }

  get width(): number {
    return this.app.screen.width;
  }

  get height(): number {
    return this.app.screen.height;
  }

  get entities(): readonly Entity[] {
    return this.entityList;
  }

  /** 게임 규칙 충돌 핸들러를 등록한다 (ctx 로 this 가 전달됨). */
  setCollisionHandler(handler: CollisionHandler): void {
    this.physics.setCollisionHandler(handler, this);
  }

  /** 엔티티를 물리 월드(body 가 있다면)와 스테이지에 추가한다. */
  spawn(entity: Entity): void {
    this.entityList.push(entity);
    this.physics.add(entity);
    this.app.stage.addChild(entity.view);
  }

  /** 엔티티를 dead 표시한다; 실제 제거는 프레임 끝에 수행된다. */
  kill(entity: Entity): void {
    entity.alive = false;
  }

  /** Pixi ticker 에서 게임 루프를 시작한다. */
  start(): void {
    this.app.ticker.add(this.tick, this);
  }

  /** 게임 루프를 멈춘다 (엔티티와 월드는 그대로 유지). */
  stop(): void {
    this.app.ticker.remove(this.tick, this);
  }

  private tick(ticker: Ticker): void {
    const dtMs = Math.min(ticker.deltaMS, MAX_DT_MS);

    this.physics.update(dtMs);

    // 스냅샷 순회: update 중 스폰된 엔티티는 다음 프레임부터 update 된다.
    const snapshot = [...this.entityList];
    for (const entity of snapshot) {
      if (entity.alive) {
        entity.update(dtMs, this);
      }
    }

    for (const entity of this.entityList) {
      if (!entity.alive) continue;
      const body = entity.body;
      if (!body) continue;
      this.wrapBody(body);
      entity.view.x = body.position.x;
      entity.view.y = body.position.y;
      entity.view.rotation = body.angle;
    }

    this.removeDead();
  }

  /** 화면을 벗어난 body 를 반대편으로 순간이동시킨다 (토로이드 월드). */
  private wrapBody(body: Body): void {
    const w = this.width;
    const h = this.height;
    // body 자체 크기를 사용해 완전히 화면 밖일 때만 wrap 한다.
    const halfW = (body.bounds.max.x - body.bounds.min.x) / 2;
    const halfH = (body.bounds.max.y - body.bounds.min.y) / 2;

    let x = body.position.x;
    let y = body.position.y;
    if (x < -halfW) x = w + halfW;
    else if (x > w + halfW) x = -halfW;
    if (y < -halfH) y = h + halfH;
    else if (y > h + halfH) y = -halfH;

    if (x !== body.position.x || y !== body.position.y) {
      Body.setPosition(body, { x, y });
    }
  }

  /** alive=false 인 모든 엔티티를 월드, 스테이지, 리스트에서 제거한다. */
  private removeDead(): void {
    for (let i = this.entityList.length - 1; i >= 0; i--) {
      const entity = this.entityList[i];
      if (entity.alive) continue;
      this.entityList.splice(i, 1);
      this.physics.remove(entity);
      this.app.stage.removeChild(entity.view);
      entity.view.destroy({ children: true });
    }
  }
}
