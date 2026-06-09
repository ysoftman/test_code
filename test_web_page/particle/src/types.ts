// 공유 계약(인터페이스) 정의.
// 모듈 의존 규칙:
//   core/**      import 가능: types, constants, matter-js, pixi.js  (entities/, game/ 금지)
//   entities/**  import 가능: types, constants, matter-js, pixi.js  (core/, game/ 금지)
//   game/**      import 가능: types, constants, pixi.js             (core/, entities/ 금지)
//   main.ts      모든 모듈을 와이어링하는 통합 지점

import type { Body } from "matter-js";
import type { Container } from "pixi.js";

export type EntityKind = "ship" | "bullet" | "rock" | "dust";

/**
 * 모든 게임 오브젝트는 Entity 를 구현한다.
 * - `body`: Matter.js 물리 body (먼지처럼 순수 시각 엔티티는 null).
 * - `view`: Pixi 디스플레이 오브젝트; core 가 매 프레임 body 기준으로 x/y/rotation 동기화.
 * - `alive = false` 설정(또는 ctx.kill 호출) 시 다음 프레임에 월드+스테이지에서 제거된다.
 */
export interface Entity {
  readonly kind: EntityKind;
  readonly body: Body | null;
  readonly view: Container;
  alive: boolean;
  /** 프레임별 로직. dtMs = 직전 프레임 이후 경과 ms (core 에서 이미 클램프됨). */
  update(dtMs: number, ctx: GameContext): void;
}

/** 바위 전용 계약 — 충돌 규칙이 구체 클래스를 몰라도 split 을 호출할 수 있게 한다. */
export interface RockEntity extends Entity {
  readonly kind: "rock";
  readonly sizeLevel: number; // maxLevel (최대) .. 0 (최소)
  /**
   * 월드 좌표 (x, y) 에서의 총알 피격을 처리한다.
   * 스폰할 대체 엔티티(조각 바위 그리고/또는 먼지)를 반환한다.
   * 바위는 스스로 dead 표시하며, 제거는 core/main 이 수행한다.
   */
  split(hitX: number, hitY: number): Entity[];
}

/** 아날로그 조준/추진 상태 — 터치 조이스틱이 쓴다. angle=라디안, magnitude=0..1. */
export interface AimState {
  angle: number;
  magnitude: number;
}

/** 입력 상태 — game/input.ts(키보드)와 game/touch.ts(터치)가 쓰고 비행체가 읽는다. */
export interface InputState {
  thrust: boolean;
  reverse: boolean;
  turnLeft: boolean;
  turnRight: boolean;
  fire: boolean;
  /**
   * 터치 조이스틱의 아날로그 조준/추진. 비활성 시 null.
   * 설정되면 비행체는 angle 방향을 향하고 magnitude 에 비례해 추진한다(키보드 회전/추진 무시).
   */
  aim: AimState | null;
}

/** core/game.ts 가 모든 엔티티와 충돌 핸들러에 제공한다. */
export interface GameContext {
  readonly width: number;
  readonly height: number;
  readonly input: InputState;
  /** 엔티티를 물리 월드 + 스테이지에 추가. */
  spawn(entity: Entity): void;
  /** 엔티티를 dead 표시; 프레임 끝에 월드 + 스테이지에서 제거된다. */
  kill(entity: Entity): void;
  /** 현재 살아있는 모든 엔티티 (읽기 전용 순회). */
  readonly entities: readonly Entity[];
}

/**
 * 두 엔티티 body 의 충돌 시작 시 core 가 호출한다.
 * main.ts 가 등록하며 게임 규칙(총알+바위 -> 분열, 비행체+바위 -> 피해)을 구현한다.
 */
export type CollisionHandler = (a: Entity, b: Entity, ctx: GameContext) => void;

/** HUD/점수용 게임플레이 이벤트 — game/hud.ts 가 구현하고 main.ts 와이어링에서 발생시킨다. */
export interface GameEvents {
  rockDestroyed(sizeLevel: number): void;
  shipHit(livesLeft: number): void;
  waveCleared(wave: number): void;
}
