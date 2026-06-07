// HUD 레이어 — 점수, 생명, 웨이브, 조작 안내, 배너.
// GameEvents 를 구현하며 main.ts 가 게임플레이 이벤트를 여기로 전달한다.

import { Container, Text, type TextStyleOptions } from "pixi.js";
import { COLORS, SCORE_PER_LEVEL } from "../constants";
import type { GameEvents } from "../types";

const FONT_FAMILY = '"Courier New", Courier, monospace';
const MARGIN = 16;
const BANNER_MS = 1600;

function makeStyle(fontSize: number, bold = false): TextStyleOptions {
  return {
    fontFamily: FONT_FAMILY,
    fontSize,
    fontWeight: bold ? "bold" : "normal",
    fill: COLORS.hudText,
  };
}

/**
 * 헤드업 디스플레이. `hud.view` 를 게임 스테이지 맨 위에 추가할 것.
 * 점수/생명/웨이브는 GameEvents 메서드를 통해 갱신된다.
 */
export class Hud implements GameEvents {
  readonly view: Container;

  private width: number;
  private height: number;
  private score = 0;
  private lives: number;
  private wave = 1;

  private readonly scoreText: Text;
  private readonly livesText: Text;
  private readonly waveText: Text;
  private readonly controlsText: Text;
  private readonly banner: Text;
  private bannerTimer: ReturnType<typeof setTimeout> | null = null;

  constructor(width: number, height: number, initialLives = 3) {
    this.width = width;
    this.height = height;
    this.lives = initialLives;
    this.view = new Container();

    // 좌상단: 점수
    this.scoreText = new Text({ text: "", style: makeStyle(20, true) });
    this.scoreText.position.set(MARGIN, MARGIN);

    // 우상단: 생명
    this.livesText = new Text({ text: "", style: makeStyle(20, true) });
    this.livesText.anchor.set(1, 0);

    // 중앙 상단: 현재 웨이브
    this.waveText = new Text({ text: "", style: makeStyle(20, true) });
    this.waveText.anchor.set(0.5, 0);

    // 중앙 하단: 조작 안내
    this.controlsText = new Text({
      text: "WASD / ARROWS : MOVE & TURN    SPACE : FIRE",
      style: makeStyle(14),
    });
    this.controlsText.anchor.set(0.5, 1);
    this.controlsText.alpha = 0.7;

    // 중앙: 일시 배너 ("WAVE N", "GAME OVER")
    this.banner = new Text({ text: "", style: makeStyle(48, true) });
    this.banner.anchor.set(0.5);
    this.banner.visible = false;

    this.view.addChild(
      this.scoreText,
      this.livesText,
      this.waveText,
      this.controlsText,
      this.banner,
    );

    this.layout();
    this.refresh();
    this.showBanner(`WAVE ${this.wave}`);
  }

  /** HUD 요소들을 재배치한다; 렌더러 리사이즈 시 호출할 것. */
  resize(width: number, height: number): void {
    this.width = width;
    this.height = height;
    this.layout();
  }

  // --- GameEvents 구현 ---

  rockDestroyed(sizeLevel: number): void {
    this.score += SCORE_PER_LEVEL[sizeLevel] ?? 0;
    this.refresh();
  }

  shipHit(livesLeft: number): void {
    this.lives = livesLeft;
    this.refresh();
  }

  waveCleared(wave: number): void {
    this.wave = wave + 1;
    this.refresh();
    this.showBanner(`WAVE ${this.wave}`);
  }

  // --- 오버레이 ---

  /** GAME OVER 오버레이를 영구 표시한다 (배너가 계속 남는다). */
  gameOver(): void {
    if (this.bannerTimer !== null) {
      clearTimeout(this.bannerTimer);
      this.bannerTimer = null;
    }
    this.banner.text = `GAME OVER\nSCORE ${this.score}\n\nPRESS R TO RESTART`;
    this.banner.visible = true;
  }

  // --- 내부 구현 ---

  private layout(): void {
    this.livesText.position.set(this.width - MARGIN, MARGIN);
    this.waveText.position.set(this.width / 2, MARGIN);
    this.controlsText.position.set(this.width / 2, this.height - MARGIN);
    this.banner.position.set(this.width / 2, this.height / 2);
  }

  private refresh(): void {
    this.scoreText.text = `SCORE ${this.score}`;
    this.livesText.text = `LIVES ${this.lives}`;
    this.waveText.text = `WAVE ${this.wave}`;
  }

  private showBanner(text: string): void {
    if (this.bannerTimer !== null) clearTimeout(this.bannerTimer);
    this.banner.text = text;
    this.banner.visible = true;
    this.bannerTimer = setTimeout(() => {
      this.banner.visible = false;
      this.bannerTimer = null;
    }, BANNER_MS);
  }
}
