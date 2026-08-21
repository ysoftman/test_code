import Phaser from "phaser";
import { ACHIEVEMENTS } from "../achievements";
import { GAME_HEIGHT, GAME_WIDTH } from "../config";
import { GameState } from "../gameState";
import { retroStyle } from "../pixelart";

// 12 achievements in two columns of six; a single column of twelve needed a
// panel taller than the 720px screen (same constraint as BestiaryUI).
const COLS = 2;
const ROWS = Math.ceil(ACHIEVEMENTS.length / COLS);
const ROW_GAP = 84;
const PANEL_W = 1160;
const PANEL_H = 200 + ROWS * ROW_GAP;
const PANEL_TOP = GAME_HEIGHT / 2 - PANEL_H / 2;
const COL_W = 560;
const COL_X = GAME_WIDTH / 2 - PANEL_W / 2 + 40;
const NAME_DX = 30;

// Trophy board shown with A, listing every achievement as name + description,
// gold when earned and gray when still locked. Same dim + panel modal pattern
// as BestiaryUI; ESC or A (the opening key) closes.
export class AchievementsUI {
  private active = false;

  private dim: Phaser.GameObjects.Rectangle;
  private panel: Phaser.GameObjects.Rectangle;
  private title: Phaser.GameObjects.Text;
  private counter: Phaser.GameObjects.Text;
  private names: Phaser.GameObjects.Text[] = [];
  private descs: Phaser.GameObjects.Text[] = [];

  private keyEsc: Phaser.Input.Keyboard.Key;
  private keyA: Phaser.Input.Keyboard.Key;
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
      .text(GAME_WIDTH / 2, PANEL_TOP + 44, "ACHIEVEMENTS", retroStyle(8, "#ffd166"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);
    this.counter = scene.add
      .text(GAME_WIDTH / 2, PANEL_TOP + PANEL_H - 40, "", retroStyle(6, "#8ecbff"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);

    const startY = PANEL_TOP + 130;
    ACHIEVEMENTS.forEach((_a, i) => {
      const col = Math.floor(i / ROWS);
      const y = startY + (i % ROWS) * ROW_GAP;
      const x = COL_X + col * COL_W;
      this.names.push(
        scene.add
          .text(x + NAME_DX, y, "", retroStyle(6, "#666666"))
          .setOrigin(0, 0.5)
          .setScrollFactor(0)
          .setDepth(152)
          .setVisible(false),
      );
      this.descs.push(
        scene.add
          .text(x + NAME_DX, y + 30, "", retroStyle(5, "#444444"))
          .setOrigin(0, 0.5)
          .setScrollFactor(0)
          .setDepth(152)
          .setVisible(false),
      );
    });

    const kb = scene.input.keyboard!;
    this.keyEsc = kb.addKey(Phaser.Input.Keyboard.KeyCodes.ESC);
    this.keyA = kb.addKey(Phaser.Input.Keyboard.KeyCodes.A);
    const queueClose = () => {
      this.closeQueued = true;
    };
    this.keyEsc.on(Phaser.Input.Keyboard.Events.DOWN, queueClose);
    this.keyA.on(Phaser.Input.Keyboard.Events.DOWN, queueClose);
  }

  open(): void {
    this.active = true;
    // cleared here (not in the constructor) so the A keydown that opens the
    // panel — same event also sets closeQueued — doesn't immediately close it
    this.closeQueued = false;
    this.dim.setVisible(true);
    this.panel.setVisible(true);
    this.title.setVisible(true);
    this.counter.setVisible(true);
    for (const t of this.names) t.setVisible(true);
    for (const t of this.descs) t.setVisible(true);
    this.refresh();
  }

  close(): void {
    this.active = false;
    this.dim.setVisible(false);
    this.panel.setVisible(false);
    this.title.setVisible(false);
    this.counter.setVisible(false);
    for (const t of this.names) t.setVisible(false);
    for (const t of this.descs) t.setVisible(false);
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
    const earned = ACHIEVEMENTS.filter((a) => GameState.achievements.includes(a.id)).length;
    this.counter.setText(`EARNED ${earned}/${ACHIEVEMENTS.length}`);
    ACHIEVEMENTS.forEach((a, i) => {
      const got = GameState.achievements.includes(a.id);
      this.names[i].setText(got ? `★ ${a.name}` : a.name);
      this.names[i].setColor(got ? "#ffd166" : "#666666");
      this.descs[i].setText(a.desc);
      this.descs[i].setColor(got ? "#8ecbff" : "#444444");
    });
  }

  destroy(): void {
    this.dim.destroy();
    this.panel.destroy();
    this.title.destroy();
    this.counter.destroy();
    for (const t of this.names) t.destroy();
    for (const t of this.descs) t.destroy();
    // keys are shared instances from kb.addKey (same keycode → same object);
    // destroying them would wipe other panels' listeners. Scene shutdown
    // already tears every Key down via KeyboardPlugin.removeAllKeys(true).
  }
}
