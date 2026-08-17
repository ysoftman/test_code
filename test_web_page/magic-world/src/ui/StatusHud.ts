import Phaser from "phaser";
import { GAME_WIDTH } from "../config";
import { GameState, QuestState, clock, expToNext, isNight } from "../gameState";
import { PixelMap, makeTexture, retroStyle } from "../pixelart";

export const STATUS_HUD_HEIGHT = 88;
export const STATUS_HUD_TOAST_Y = STATUS_HUD_HEIGHT + 12;

// The single quest slot shows whichever chapter is currently open.
function questLabel(q: QuestState): string {
  if (!q.bossDefeated) return `SLIMES ${q.slimes}/5`;
  if (!q.forestBoss) return "FIND GOLEM";
  if (!q.forestReward) return "SEE ELDER";
  return "QUEST DONE";
}

const COLORS = {
  name: "#ffffff",
  lv: "#fbbf24",
  hp: "#4ade80",
  mp: "#60a5fa",
  gold: "#fde047",
  time: "#e2e8f0",
  quest: "#fb923c",
  caught: "#67e8f9",
  exp: "#86efac",
};

// Day/night indicator icons (8x8 rows = 32x32px at PIXEL=4): a yellow sun with
// a circle-ish core and corner/edge rays, and a pale crescent moon. Drawn as a
// right-anchored image on row 1 so it can't overlap the GOLD segment.
const SUN_ROWS = [
  ".X....X.",
  "..X..X..",
  ".XXXXXX.",
  "XXXXXXXX",
  "XXXXXXXX",
  ".XXXXXX.",
  "..X..X..",
  ".X....X.",
];
const SUN_PALETTE: PixelMap = { X: 0xfde047 };

const MOON_ROWS = [
  "..XXXX..",
  ".XXXXXX.",
  "XXXXXX..",
  "XXXX....",
  "XXXX....",
  "XXXXXX..",
  ".XXXXXX.",
  "..XXXX..",
];
const MOON_PALETTE: PixelMap = { X: 0xcbd5e1 };

// Compact top-of-screen overlay: colored stat segments on row 1, quest/caught
// and the EXP bar on row 2, HP/MP thin bars under the values. Everything is
// scroll-locked and drawn above the night/dungeon overlays so it stays legible;
// a sun/moon image in the top-right corner marks the day/night state.
export class StatusHud {
  private scene: Phaser.Scene;
  private panel!: Phaser.GameObjects.Rectangle;
  private accent!: Phaser.GameObjects.Rectangle;
  private hpBar!: Phaser.GameObjects.Rectangle;
  private mpBar!: Phaser.GameObjects.Rectangle;
  private expBar!: Phaser.GameObjects.Rectangle;
  private dayNightIcon!: Phaser.GameObjects.Image;
  private lastNight = false;
  private segments: Phaser.GameObjects.Text[] = [];
  private lastTexts: string[] = [];
  private lastColors: string[] = [];

  constructor(scene: Phaser.Scene) {
    this.scene = scene;
    this.panel = scene.add
      .rectangle(GAME_WIDTH / 2, STATUS_HUD_HEIGHT / 2, GAME_WIDTH - 2, STATUS_HUD_HEIGHT, 0x0b0b2b, 0.6)
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setStrokeStyle(1, 0xffffff)
      .setDepth(110);
    this.accent = scene.add
      .rectangle(0, 0, GAME_WIDTH, 4, 0xfbbf24, 0.9)
      .setOrigin(0, 0)
      .setScrollFactor(0)
      .setDepth(111);

    this.makeDayNightTextures();
    this.dayNightIcon = scene.add
      .image(GAME_WIDTH - 24, 26, "sun")
      .setOrigin(1, 0.5)
      .setScrollFactor(0)
      .setDepth(111);

    // Row 1 is laid out on even 40px-gap slots between 24px side margins,
    // using each segment's max span so the gaps stay uniform at max values:
    // name(96) | LV(120, right-anchored) | HP(240) | MP(240) | G(144) |
    // clock(120, right-anchored) | icon(32).
    this.addSegment(24, 14, 6, COLORS.name);
    this.addSegment(280, 14, 6, COLORS.lv, 1);
    this.addSegment(320, 14, 6, COLORS.hp);
    this.addSegment(600, 14, 6, COLORS.mp);
    this.addSegment(880, 14, 6, COLORS.gold);
    this.addSegment(1184, 14, 6, COLORS.time, 1);
    this.addSegment(24, 58, 5, COLORS.quest);
    this.addSegment(248, 58, 5, COLORS.caught);
    this.addSegment(452, 58, 5, COLORS.exp);

    this.hpBar = scene.add
      .rectangle(320, 46, 192, 5, 0x4ade80, 1)
      .setOrigin(0, 0.5)
      .setScrollFactor(0)
      .setDepth(110);
    this.mpBar = scene.add
      .rectangle(600, 46, 192, 5, 0x60a5fa, 1)
      .setOrigin(0, 0.5)
      .setScrollFactor(0)
      .setDepth(110);
    this.expBar = scene.add
      .rectangle(516, 68, 740, 8, 0x22c55e, 1)
      .setOrigin(0, 0.5)
      .setScrollFactor(0)
      .setDepth(110);

    this.setVisible(GameState.hudVisible);
    this.update();
  }

  private makeDayNightTextures(): void {
    // World and Dungeon scenes both construct a StatusHud, so generate the
    // icon textures only once per game.
    if (!this.scene.textures.exists("sun")) {
      makeTexture(this.scene, "sun", SUN_ROWS, SUN_PALETTE);
    }
    if (!this.scene.textures.exists("moon")) {
      makeTexture(this.scene, "moon", MOON_ROWS, MOON_PALETTE);
    }
  }

  private addSegment(x: number, y: number, size: number, color: string, originX = 0): void {
    const t = this.scene.add
      .text(x, y, "", retroStyle(size, color))
      .setOrigin(originX, 0)
      .setScrollFactor(0)
      .setDepth(111);
    this.segments.push(t);
    this.lastTexts.push("");
    this.lastColors.push("");
  }

  setVisible(visible: boolean): void {
    this.panel.setVisible(visible);
    this.accent.setVisible(visible);
    this.hpBar.setVisible(visible);
    this.mpBar.setVisible(visible);
    this.expBar.setVisible(visible);
    this.dayNightIcon.setVisible(visible);
    for (const t of this.segments) t.setVisible(visible);
  }

  isVisible(): boolean {
    return this.panel.visible;
  }

  forceRefresh(): void {
    this.lastTexts = this.lastTexts.map(() => "");
    this.lastColors = this.lastColors.map(() => "");
  }

  update(): void {
    const p = GameState.player;
    const q = GameState.quest;
    const maxHp = GameState.effMaxHp();
    const hpRatio = maxHp > 0 ? p.hp / maxHp : 0;
    const mpRatio = p.maxMp > 0 ? p.mp / p.maxMp : 0;
    const hpColor = hpRatio < 0.25 ? "#ef4444" : hpRatio < 0.5 ? "#fbbf24" : COLORS.hp;

    this.setSegment(0, p.name, COLORS.name);
    this.setSegment(1, `LV ${p.level}`, COLORS.lv);
    this.setSegment(2, `HP ${p.hp}/${maxHp}`, hpColor);
    this.setSegment(3, `MP ${p.mp}/${p.maxMp}`, COLORS.mp);
    this.setSegment(4, `G ${GameState.gold}`, COLORS.gold);
    this.setSegment(5, clock(), COLORS.time);
    this.setSegment(6, questLabel(q), COLORS.quest);
    this.setSegment(7, `CAUGHT ${GameState.caught.length}`, COLORS.caught);
    this.setSegment(8, "EXP", COLORS.exp);

    // Swap sun/moon only when the night state flips, to avoid per-frame churn.
    const night = isNight();
    if (night !== this.lastNight) {
      this.lastNight = night;
      this.dayNightIcon.setTexture(night ? "moon" : "sun");
    }

    this.hpBar.setScale(Math.max(0, hpRatio), 1);
    this.mpBar.setScale(Math.max(0, mpRatio), 1);
    this.expBar.setScale(Math.min(1, Math.max(0, p.exp / expToNext(p.level))), 1);
  }

  private setSegment(index: number, text: string, color: string): void {
    if (text === this.lastTexts[index] && color === this.lastColors[index]) return;
    this.lastTexts[index] = text;
    this.lastColors[index] = color;
    this.segments[index].setText(text).setColor(color);
  }
}