// 플레이어 비행체 — ctx.input 의 키보드 입력으로 조종되는 시안색 삼각형.
import { Bodies, Body } from "matter-js";
import { Container, Graphics } from "pixi.js";
import { playFire } from "../audio";
import { BULLET, COLLISION, COLORS, SHIP } from "../constants";
import type { Entity, GameContext } from "../types";
import { Bullet } from "./bullet";

const FRAME_MS = 1000 / 60;
const BLINK_INTERVAL_MS = 120;
const REVERSE_FORCE_RATIO = 0.5;

export class Ship implements Entity {
  readonly kind = "ship" as const;
  readonly body: Body;
  readonly view: Container;
  alive = true;

  private readonly flame: Graphics;
  private readonly noseOffset: number;
  private fireCooldownLeft = 0;
  private invulnerableLeft = 0;

  constructor(x: number, y: number) {
    // +x 방향(angle 0)을 향하는 삼각형. Pixi 뷰 원점이 Matter 질량 중심과
    // 일치하도록 꼭짓점들을 무게중심 기준으로 재정렬한다.
    const s = SHIP.size;
    const raw = [
      { x: s, y: 0 },
      { x: -s * 0.7, y: -s * 0.62 },
      { x: -s * 0.7, y: s * 0.62 },
    ];
    const cx = (raw[0].x + raw[1].x + raw[2].x) / 3;
    const cy = (raw[0].y + raw[1].y + raw[2].y) / 3;
    const verts = raw.map((v) => ({ x: v.x - cx, y: v.y - cy }));
    this.noseOffset = verts[0].x;
    const backX = verts[1].x;

    this.body = Bodies.fromVertices(x, y, [verts], {
      frictionAir: SHIP.frictionAir,
      collisionFilter: { category: COLLISION.ship, mask: COLLISION.rock },
    });

    const hull = new Graphics();
    hull
      .poly([verts[0].x, verts[0].y, verts[1].x, verts[1].y, verts[2].x, verts[2].y])
      .fill(COLORS.ship);

    // 엔진 화염 — 뒤쪽(-x)을 향해 그리며 추진 중에만 표시된다.
    this.flame = new Graphics();
    this.flame.poly([0, -s * 0.28, 0, s * 0.28, -s * 0.9, 0]).fill(COLORS.shipThrust);
    this.flame.position.set(backX, 0);
    this.flame.visible = false;

    const view = new Container();
    view.addChild(this.flame);
    view.addChild(hull);
    this.view = view;
  }

  update(dtMs: number, ctx: GameContext): void {
    const dtScale = dtMs / FRAME_MS;
    const { input } = ctx;
    const body = this.body;

    // 즉답성 있는 회전을 위해 각도를 직접 제어; 충돌로 비행체가 회전하지 않는다.
    let angle = body.angle;
    let thrusting = false;

    if (input.aim) {
      // 터치 조이스틱: 비행체를 조이스틱 방향(360°)으로 향하게 하고 세기에 비례해 추진.
      angle = input.aim.angle;
      Body.setAngle(body, angle);
      Body.setAngularVelocity(body, 0);
      const f = SHIP.thrustForce * input.aim.magnitude;
      Body.applyForce(body, body.position, {
        x: Math.cos(angle) * f,
        y: Math.sin(angle) * f,
      });
      thrusting = input.aim.magnitude > 0;
    } else {
      // 키보드: 좌우 회전 + 전/후진.
      if (input.turnLeft) angle -= SHIP.turnSpeed * dtScale;
      if (input.turnRight) angle += SHIP.turnSpeed * dtScale;
      if (angle !== body.angle) Body.setAngle(body, angle);
      Body.setAngularVelocity(body, 0);

      const dirX = Math.cos(angle);
      const dirY = Math.sin(angle);
      if (input.thrust) {
        Body.applyForce(body, body.position, {
          x: dirX * SHIP.thrustForce,
          y: dirY * SHIP.thrustForce,
        });
        thrusting = true;
      }
      if (input.reverse) {
        const f = SHIP.thrustForce * REVERSE_FORCE_RATIO;
        Body.applyForce(body, body.position, { x: -dirX * f, y: -dirY * f });
      }
    }

    const dirX = Math.cos(angle);
    const dirY = Math.sin(angle);

    this.flame.visible = thrusting;
    if (thrusting) {
      // 약간의 랜덤 깜빡임으로 화염을 생동감 있게 만든다.
      this.flame.scale.set(0.85 + Math.random() * 0.3, 1);
    }

    this.fireCooldownLeft -= dtMs;
    if (input.fire && this.fireCooldownLeft <= 0) {
      this.fireCooldownLeft = SHIP.fireCooldownMs;
      const muzzle = this.noseOffset + BULLET.radius + 2;
      ctx.spawn(
        new Bullet(
          body.position.x + dirX * muzzle,
          body.position.y + dirY * muzzle,
          angle,
          body.velocity.x,
          body.velocity.y,
        ),
      );
      playFire();
    }

    if (this.invulnerableLeft > 0) {
      this.invulnerableLeft -= dtMs;
      if (this.invulnerableLeft <= 0) {
        this.view.alpha = 1;
      } else {
        // 무적 시간 동안 깜빡임.
        this.view.alpha =
          Math.floor(this.invulnerableLeft / BLINK_INTERVAL_MS) % 2 === 0 ? 1 : 0.25;
      }
    }
  }

  /**
   * 바위 피격을 처리한다. 이전 피격으로 아직 무적 상태면 false 를 반환하고,
   * 아니면 무적 시간(깜빡임 포함)을 시작하며 true 를 반환한다.
   */
  hit(): boolean {
    if (this.invulnerableLeft > 0) return false;
    this.invulnerableLeft = SHIP.invulnerableMs;
    return true;
  }
}
