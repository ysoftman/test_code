// 통합 엔트리포인트 — 코어 엔진, 엔티티, 게임플레이 모듈을 와이어링한다.
import { Body } from "matter-js";
import "./style.css";
import { playHit, unlockAudio } from "./audio";
import { COLORS } from "./constants";
import { Game } from "./core/game";
import { createRenderer } from "./core/renderer";
import { createDustBurst } from "./entities/dust";
import { createRock } from "./entities/rock";
import { Ship } from "./entities/ship";
import { Hud } from "./game/hud";
import { createInput } from "./game/input";
import { waveSpawns } from "./game/spawner";
import { createTouchControls } from "./game/touch";
import type { Entity, GameContext, RockEntity } from "./types";

const INITIAL_LIVES = 3;
const HUD_Z_INDEX = 1000;
const WAVE_DELAY_MS = 1600; // HUD 배너 표시 시간과 동일

async function bootstrap(): Promise<void> {
  const app = await createRenderer();
  // 나중에 스폰되는 게임 엔티티들보다 HUD 가 항상 위에 오도록 한다.
  app.stage.sortableChildren = true;

  const input = createInput();
  // 터치 기기에서는 화면 위 가상 버튼 오버레이를 추가한다 (키보드와 동일한 InputState 공유).
  // 데스크탑에서는 null 을 반환하고 아무 DOM 도 만들지 않는다.
  createTouchControls(input);

  // 브라우저 자동재생 정책: 첫 사용자 제스처에서 오디오 컨텍스트를 깨운다.
  const unlock = (): void => unlockAudio();
  for (const ev of ["keydown", "pointerdown", "touchstart"] as const) {
    window.addEventListener(ev, unlock, { once: true });
  }
  const game = new Game(app, input);

  const hud = new Hud(app.screen.width, app.screen.height, INITIAL_LIVES);
  hud.view.zIndex = HUD_Z_INDEX;
  app.stage.addChild(hud.view);
  app.renderer.on("resize", (w: number, h: number) => hud.resize(w, h));

  // --- 게임 상태 ---
  let lives = INITIAL_LIVES;
  let wave = 1;
  let isGameOver = false;

  const ship = new Ship(app.screen.width / 2, app.screen.height / 2);
  Body.setAngle(ship.body, -Math.PI / 2); // 위쪽을 향한 채 시작
  game.spawn(ship);

  function spawnWave(ctx: GameContext): void {
    if (isGameOver) return;
    const { x, y } = ship.alive ? ship.body.position : { x: ctx.width / 2, y: ctx.height / 2 };
    for (const s of waveSpawns(wave, ctx.width, ctx.height, x, y)) {
      ctx.spawn(createRock(s.x, s.y, s.sizeLevel, s.vx, s.vy));
    }
  }

  // --- 충돌 규칙 ---

  function onBulletHitsRock(bullet: Entity, rock: RockEntity, ctx: GameContext): void {
    ctx.kill(bullet);
    const hitX = bullet.body?.position.x ?? rock.body?.position.x ?? 0;
    const hitY = bullet.body?.position.y ?? rock.body?.position.y ?? 0;
    for (const fragment of rock.split(hitX, hitY)) {
      ctx.spawn(fragment);
    }
    playHit();
    hud.rockDestroyed(rock.sizeLevel);

    // 살아있는 바위가 하나도 없으면 웨이브 클리어 (분열 조각도 바위로 집계).
    const rocksLeft = ctx.entities.some((e) => e.alive && e.kind === "rock");
    if (!rocksLeft) {
      hud.waveCleared(wave);
      wave += 1;
      setTimeout(() => spawnWave(ctx), WAVE_DELAY_MS);
    }
  }

  function onShipHitsRock(ctx: GameContext): void {
    if (!ship.alive || !ship.hit()) return; // 무적 상태면 무시
    lives -= 1;
    hud.shipHit(lives);
    const { x, y } = ship.body.position;
    for (const dust of createDustBurst(x, y, 12, COLORS.ship)) {
      ctx.spawn(dust);
    }
    if (lives <= 0) {
      isGameOver = true;
      ctx.kill(ship);
      for (const dust of createDustBurst(x, y, 30, COLORS.ship)) {
        ctx.spawn(dust);
      }
      hud.gameOver();
    }
  }

  game.setCollisionHandler((a, b, ctx) => {
    if (a.kind === "bullet" && b.kind === "rock") {
      onBulletHitsRock(a, b as RockEntity, ctx);
    } else if (a.kind === "rock" && b.kind === "bullet") {
      onBulletHitsRock(b, a as RockEntity, ctx);
    } else if (
      (a.kind === "ship" && b.kind === "rock") ||
      (a.kind === "rock" && b.kind === "ship")
    ) {
      onShipHitsRock(ctx);
    }
  });

  // 게임 오버 후 재시작: 데스크탑은 R 키, 터치 기기는 화면 탭.
  window.addEventListener("keydown", (e) => {
    if (isGameOver && e.code === "KeyR") {
      window.location.reload();
    }
  });
  // 터치 기기에서는 게임 오버 후 화면 어디든 탭하면 재시작 (HUD 의 "TAP TO RESTART" 와 일치).
  window.addEventListener("touchend", () => {
    if (isGameOver) window.location.reload();
  });

  spawnWave(game);
  game.start();
}

bootstrap();
