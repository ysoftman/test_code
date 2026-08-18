import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { GameState } from "../gameState";
import { retroStyle } from "../pixelart";
import { getRanks, MAX_RANKS } from "../ranking";

const PANEL_W = 960;
const PANEL_H = 640;
const PANEL_TOP = GAME_HEIGHT / 2 - PANEL_H / 2;
const PANEL_LEFT = GAME_WIDTH / 2 - PANEL_W / 2;
const ROW_H = 46;
const ROWS_START = PANEL_TOP + 140;
const COL_RANK = PANEL_LEFT + 56;
const COL_NAME = PANEL_LEFT + 140;
const COL_LEVEL = PANEL_LEFT + 520;
const COL_DATE = PANEL_LEFT + 680;

// Top-10 level leaderboard shown by the RANK BOARD sign in the village.
// Follows the BestiaryUI modal pattern: dim + panel, ESC (or Z, since Z is
// the key that opens it) closes, and it re-reads the board on every open.
export class RankingUI {
  private active = false;

  private dim: Phaser.GameObjects.Rectangle;
  private panel: Phaser.GameObjects.Rectangle;
  private title: Phaser.GameObjects.Text;
  private headers: Phaser.GameObjects.Text[] = [];
  private footer: Phaser.GameObjects.Text;
  private rankCells: Phaser.GameObjects.Text[] = [];
  private nameCells: Phaser.GameObjects.Text[] = [];
  private levelCells: Phaser.GameObjects.Text[] = [];
  private dateCells: Phaser.GameObjects.Text[] = [];

  private keyEsc: Phaser.Input.Keyboard.Key;
  private keyZ: Phaser.Input.Keyboard.Key;
  private closeQueued = false;

  constructor(scene: Phaser.Scene) {
    this.dim = scene.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH, GAME_HEIGHT, 0x000000, 0.5)
      .setScrollFactor(0)
      .setDepth(150)
      .setVisible(false);
    this.panel = scene.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, PANEL_W, PANEL_H, 0x0b0b2b, 0.95)
      .setScrollFactor(0)
      .setDepth(151)
      .setStrokeStyle(2, 0xffffff)
      .setVisible(false);
    this.title = scene.add
      .text(GAME_WIDTH / 2, PANEL_TOP + 44, "RANKING", retroStyle(8, "#ffd166"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);

    const headerY = ROWS_START - 32;
    const headers: Array<{ x: number; label: string }> = [
      { x: COL_RANK, label: "RK" },
      { x: COL_NAME, label: "NAME" },
      { x: COL_LEVEL, label: "LV" },
      { x: COL_DATE, label: "DATE" },
    ];
    for (const h of headers) {
      this.headers.push(
        scene.add
          .text(h.x, headerY, h.label, retroStyle(5, "#8ecbff"))
          .setOrigin(0, 0.5)
          .setScrollFactor(0)
          .setDepth(152)
          .setVisible(false)
      );
    }
    this.footer = scene.add
      .text(GAME_WIDTH / 2, PANEL_TOP + PANEL_H - 36, "TOP 10 BY LEVEL   ESC/Z: CLOSE", retroStyle(5, "#9f9fd0"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);

    for (let i = 0; i < MAX_RANKS; i++) {
      const y = ROWS_START + i * ROW_H;
      this.rankCells.push(
        scene.add
          .text(COL_RANK, y, `${i + 1}.`, retroStyle(6, "#9f9fd0"))
          .setOrigin(0, 0.5)
          .setScrollFactor(0)
          .setDepth(152)
          .setVisible(false)
      );
      this.nameCells.push(
        scene.add
          .text(COL_NAME, y, "", retroStyle(6, "#ffffff"))
          .setOrigin(0, 0.5)
          .setScrollFactor(0)
          .setDepth(152)
          .setVisible(false)
      );
      this.levelCells.push(
        scene.add
          .text(COL_LEVEL, y, "", retroStyle(6, "#ffffff"))
          .setOrigin(0, 0.5)
          .setScrollFactor(0)
          .setDepth(152)
          .setVisible(false)
      );
      this.dateCells.push(
        scene.add
          .text(COL_DATE, y, "", retroStyle(6, "#ffffff"))
          .setOrigin(0, 0.5)
          .setScrollFactor(0)
          .setDepth(152)
          .setVisible(false)
      );
    }

    const kb = scene.input.keyboard!;
    this.keyEsc = kb.addKey(Phaser.Input.Keyboard.KeyCodes.ESC);
    this.keyZ = kb.addKey(Phaser.Input.Keyboard.KeyCodes.Z);
    const queueClose = () => {
      this.closeQueued = true;
    };
    this.keyEsc.on(Phaser.Input.Keyboard.Events.DOWN, queueClose);
    this.keyZ.on(Phaser.Input.Keyboard.Events.DOWN, queueClose);
  }

  open(): void {
    this.active = true;
    // cleared here (not in the constructor) so the Z keydown that opens the
    // panel — same event also sets closeQueued — doesn't immediately close it
    this.closeQueued = false;
    this.dim.setVisible(true);
    this.panel.setVisible(true);
    this.title.setVisible(true);
    this.footer.setVisible(true);
    for (const t of this.headers) t.setVisible(true);
    for (const arr of [this.rankCells, this.nameCells, this.levelCells, this.dateCells]) {
      for (const t of arr) t.setVisible(true);
    }
    this.refresh();
  }

  close(): void {
    this.active = false;
    this.dim.setVisible(false);
    this.panel.setVisible(false);
    this.title.setVisible(false);
    this.footer.setVisible(false);
    for (const t of this.headers) t.setVisible(false);
    for (const arr of [this.rankCells, this.nameCells, this.levelCells, this.dateCells]) {
      for (const t of arr) t.setVisible(false);
    }
  }

  isActive(): boolean {
    return this.active;
  }

  update(): void {
    if (!this.active || !this.closeQueued) return;
    this.closeQueued = false;
    this.close();
  }

  private refresh(): void {
    const ranks = getRanks();
    for (let i = 0; i < MAX_RANKS; i++) {
      const e = ranks[i];
      const isMe = !!e && e.name === GameState.player.name;
      this.rankCells[i].setColor(
        i === 0 && e ? "#ffd166" : isMe ? "#8ecbff" : e ? "#9f9fd0" : "#666666"
      );
      if (e) {
        this.nameCells[i].setText(e.name).setColor(isMe ? "#8ecbff" : "#ffffff");
        this.levelCells[i].setText(`LV ${e.level}`).setColor(isMe ? "#8ecbff" : "#ffffff");
        this.dateCells[i].setText(e.date).setColor(isMe ? "#8ecbff" : "#ffffff");
      } else {
        this.nameCells[i].setText("---").setColor("#666666");
        this.levelCells[i].setText("").setColor("#666666");
        this.dateCells[i].setText("").setColor("#666666");
      }
    }
  }

  destroy(): void {
    this.dim.destroy();
    this.panel.destroy();
    this.title.destroy();
    this.footer.destroy();
    for (const t of this.headers) t.destroy();
    for (const arr of [this.rankCells, this.nameCells, this.levelCells, this.dateCells]) {
      for (const t of arr) t.destroy();
    }
    // keys are shared instances from kb.addKey (same keycode → same object);
    // destroying them would wipe other panels' listeners. Scene shutdown
    // already tears every Key down via KeyboardPlugin.removeAllKeys(true).
  }
}
