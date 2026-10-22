// HUD 레이어 — 점수, 생명, 웨이브, 조작 안내, 배너.
// GameEvents 를 구현하며 main.ts 가 게임플레이 이벤트를 여기로 전달한다.

import { Container, Text, type TextStyleOptions } from "pixi.js";
import { COLORS, SCORE_PER_LEVEL } from "../constants";
import type { GameEvents } from "../types";

const FONT_FAMILY = '"Courier New", Courier, monospace';
const MARGIN = 16;
const BANNER_MS = 1600;

// 기준 폰트 크기 (scale=1 일 때). layout() 에서 화면 비례로 스케일된다.
const BASE_SCORE_FONT = 20;
const BASE_CONTROLS_FONT = 14;
const BASE_BANNER_FONT = 48;

// 터치 기기 감지 — 터치면 하단 조작 안내를 숨기고 재시작 문구를 바꾼다.
const IS_TOUCH =
  typeof window !== "undefined" &&
  ("ontouchstart" in window || (typeof navigator !== "undefined" && navigator.maxTouchPoints > 0));

const RESTART_PROMPT = IS_TOUCH ? "TAP TO RESTART" : "PRESS R TO RESTART";

/**
 * 화면 최소 변(min(width,height))을 720 기준으로 정규화한 스케일.
 * 작은 모바일에서도 너무 작아지지 않게 [0.7, 1.4] 로 클램프한다.
 */
function computeScale(width: number, height: number): number {
  const minDim = Math.min(width, height);
  return Math.max(0.7, Math.min(1.4, minDim / 720));
}

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
    this.scoreText = new Text({ text: "", style: makeStyle(BASE_SCORE_FONT, true) });
    this.scoreText.position.set(MARGIN, MARGIN);

    // 우상단: 생명
    this.livesText = new Text({ text: "", style: makeStyle(BASE_SCORE_FONT, true) });
    this.livesText.anchor.set(1, 0);

    // 중앙 상단: 현재 웨이브
    this.waveText = new Text({ text: "", style: makeStyle(BASE_SCORE_FONT, true) });
    this.waveText.anchor.set(0.5, 0);

    // 중앙 하단: 조작 안내. 터치 기기에서는 터치 버튼이 그 자리에 오므로 숨긴다.
    this.controlsText = new Text({
      text: "WASD / ARROWS : MOVE & TURN    SPACE : FIRE",
      style: makeStyle(BASE_CONTROLS_FONT),
    });
    this.controlsText.anchor.set(0.5, 1);
    this.controlsText.alpha = 0.7;
    this.controlsText.visible = !IS_TOUCH;

    // 중앙: 일시 배너 ("WAVE N", "GAME OVER")
    this.banner = new Text({ text: "", style: makeStyle(BASE_BANNER_FONT, true) });
    this.banner.anchor.set(0.5);
    this.banner.visible = false;
    // 작은 화면에서 좌우로 넘치지 않게 줄바꿈/가운데 정렬.
    this.banner.style.align = "center";
    this.banner.style.wordWrap = true;

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
    this.banner.text = `GAME OVER\nSCORE ${this.score}\n\n${RESTART_PROMPT}`;
    this.banner.visible = true;
  }

  // --- 내부 구현 ---

  private layout(): void {
    const scale = computeScale(this.width, this.height);
    const margin = MARGIN * scale;

    // 화면 크기에 비례해 폰트 크기 갱신.
    this.scoreText.style.fontSize = BASE_SCORE_FONT * scale;
    this.livesText.style.fontSize = BASE_SCORE_FONT * scale;
    this.waveText.style.fontSize = BASE_SCORE_FONT * scale;
    this.controlsText.style.fontSize = BASE_CONTROLS_FONT * scale;
    this.banner.style.fontSize = BASE_BANNER_FONT * scale;
    this.banner.style.wordWrapWidth = this.width * 0.9;

    this.scoreText.position.set(margin, margin);
    this.livesText.position.set(this.width - margin, margin);
    this.waveText.position.set(this.width / 2, margin);
    this.controlsText.position.set(this.width / 2, this.height - margin);
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
