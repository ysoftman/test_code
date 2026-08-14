import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { GameState } from "../gameState";
import { retroStyle } from "../pixelart";
import { ENEMIES } from "../monsters";

const SPECIES = Object.values(ENEMIES);
const ROW_GAP = 36;
const PANEL_H = 40 + SPECIES.length * ROW_GAP;

export class BestiaryUI {
  private active = false;

  private dim: Phaser.GameObjects.Rectangle;
  private panel: Phaser.GameObjects.Rectangle;
  private title: Phaser.GameObjects.Text;
  private icons: Phaser.GameObjects.Sprite[] = [];
  private rows: Phaser.GameObjects.Text[] = [];

  private keyEsc: Phaser.Input.Keyboard.Key;
  private keyC: Phaser.Input.Keyboard.Key;
  private closeQueued = false;

  constructor(scene: Phaser.Scene) {
    this.dim = scene.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH, GAME_HEIGHT, 0x000000, 0.5)
      .setScrollFactor(0)
      .setDepth(150)
      .setVisible(false);
    this.panel = scene.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, 360, PANEL_H, 0x0b0b2b, 0.95)
      .setScrollFactor(0)
      .setDepth(151)
      .setStrokeStyle(2, 0xffffff)
      .setVisible(false);
    this.title = scene.add
      .text(GAME_WIDTH / 2, GAME_HEIGHT / 2 - PANEL_H / 2 + 18, "BESTIARY", retroStyle(8, "#ffd166"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);

    const startY = GAME_HEIGHT / 2 - PANEL_H / 2 + 48;
    SPECIES.forEach((def, i) => {
      const y = startY + i * ROW_GAP;
      const icon = scene.add
        .sprite(GAME_WIDTH / 2 - 130, y, def.texture)
        .setScale(1.4)
        .setScrollFactor(0)
        .setDepth(152)
        .setVisible(false);
      this.icons.push(icon);
      const row = scene.add
        .text(GAME_WIDTH / 2 - 90, y, "???", retroStyle(7, "#666666"))
        .setOrigin(0, 0.5)
        .setScrollFactor(0)
        .setDepth(152)
        .setVisible(false);
      this.rows.push(row);
    });

    const kb = scene.input.keyboard!;
    this.keyEsc = kb.addKey(Phaser.Input.Keyboard.KeyCodes.ESC);
    this.keyC = kb.addKey(Phaser.Input.Keyboard.KeyCodes.C);
    const queueClose = () => {
      this.closeQueued = true;
    };
    this.keyEsc.on(Phaser.Input.Keyboard.Events.DOWN, queueClose);
    this.keyC.on(Phaser.Input.Keyboard.Events.DOWN, queueClose);
  }

  open(): void {
    this.active = true;
    this.closeQueued = false;
    this.dim.setVisible(true);
    this.panel.setVisible(true);
    this.title.setVisible(true);
    for (const t of this.rows) t.setVisible(true);
    this.refresh();
  }

  close(): void {
    this.active = false;
    this.dim.setVisible(false);
    this.panel.setVisible(false);
    this.title.setVisible(false);
    for (const s of this.icons) s.setVisible(false);
    for (const t of this.rows) t.setVisible(false);
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
    SPECIES.forEach((def, i) => {
      const seen = GameState.seenMonsters.includes(def.name);
      const caught = GameState.caught.filter((n) => n === def.name).length;
      this.icons[i].setVisible(seen);
      this.rows[i].setText(seen ? `${def.name}${caught > 0 ? ` (x${caught})` : ""}` : "???");
      this.rows[i].setColor(seen ? "#ffffff" : "#666666");
    });
  }

  destroy(): void {
    this.dim.destroy();
    this.panel.destroy();
    this.title.destroy();
    for (const s of this.icons) s.destroy();
    for (const t of this.rows) t.destroy();
    this.keyEsc.destroy();
    this.keyC.destroy();
  }
}
