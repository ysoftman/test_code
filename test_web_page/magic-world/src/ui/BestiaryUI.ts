import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { GameState } from "../gameState";
import { retroStyle, showToast } from "../pixelart";
import { CATCHABLE, ENEMIES } from "../monsters";

const SPECIES = Object.values(ENEMIES);
const ROW_GAP = 72;
const PANEL_H = 80 + SPECIES.length * ROW_GAP;

export class BestiaryUI {
  private scene: Phaser.Scene;
  private active = false;
  private allCaughtToastShown = false;

  private dim: Phaser.GameObjects.Rectangle;
  private panel: Phaser.GameObjects.Rectangle;
  private title: Phaser.GameObjects.Text;
  private counter: Phaser.GameObjects.Text;
  private icons: Phaser.GameObjects.Sprite[] = [];
  private rows: Phaser.GameObjects.Text[] = [];

  private keyEsc: Phaser.Input.Keyboard.Key;
  private keyB: Phaser.Input.Keyboard.Key;
  private closeQueued = false;

  constructor(scene: Phaser.Scene) {
    this.scene = scene;
    this.dim = scene.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH, GAME_HEIGHT, 0x000000, 0.5)
      .setScrollFactor(0)
      .setDepth(150)
      .setVisible(false);
    this.panel = scene.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, 720, PANEL_H, 0x0b0b2b, 0.95)
      .setScrollFactor(0)
      .setDepth(151)
      .setStrokeStyle(2, 0xffffff)
      .setVisible(false);
    this.title = scene.add
      .text(GAME_WIDTH / 2, GAME_HEIGHT / 2 - PANEL_H / 2 + 36, "BESTIARY", retroStyle(8, "#ffd166"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);
    this.counter = scene.add
      .text(GAME_WIDTH / 2, GAME_HEIGHT / 2 + PANEL_H / 2 - 28, "", retroStyle(5, "#8ecbff"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);

    const startY = GAME_HEIGHT / 2 - PANEL_H / 2 + 96;
    SPECIES.forEach((def, i) => {
      const y = startY + i * ROW_GAP;
      const icon = scene.add
        .sprite(GAME_WIDTH / 2 - 260, y, def.texture)
        .setScale(1.4)
        .setScrollFactor(0)
        .setDepth(152)
        .setVisible(false);
      this.icons.push(icon);
      const row = scene.add
        .text(GAME_WIDTH / 2 - 180, y, "???", retroStyle(7, "#666666"))
        .setOrigin(0, 0.5)
        .setScrollFactor(0)
        .setDepth(152)
        .setVisible(false);
      this.rows.push(row);
    });

    const kb = scene.input.keyboard!;
    this.keyEsc = kb.addKey(Phaser.Input.Keyboard.KeyCodes.ESC);
    this.keyB = kb.addKey(Phaser.Input.Keyboard.KeyCodes.B);
    const queueClose = () => {
      this.closeQueued = true;
    };
    this.keyEsc.on(Phaser.Input.Keyboard.Events.DOWN, queueClose);
    this.keyB.on(Phaser.Input.Keyboard.Events.DOWN, queueClose);
  }

  open(): void {
    this.active = true;
    this.closeQueued = false;
    this.dim.setVisible(true);
    this.panel.setVisible(true);
    this.title.setVisible(true);
    this.counter.setVisible(true);
    for (const t of this.rows) t.setVisible(true);
    this.refresh();
  }

  close(): void {
    this.active = false;
    this.dim.setVisible(false);
    this.panel.setVisible(false);
    this.title.setVisible(false);
    this.counter.setVisible(false);
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
    // CAUGHT is scored against CATCHABLE — bosses appear in the list but can
    // never be caught, so counting them would make 100% unreachable.
    const seen = SPECIES.filter((def) => GameState.seenMonsters.includes(def.name)).length;
    const caught = CATCHABLE.filter((def) => GameState.caught.includes(def.name)).length;
    this.counter.setText(`SEEN ${seen}/${SPECIES.length}  CAUGHT ${caught}/${CATCHABLE.length}`);
    if (caught === CATCHABLE.length && !this.allCaughtToastShown) {
      this.allCaughtToastShown = true;
      showToast(this.scene, "ALL CAUGHT! SEE THE ELDER");
    }
    SPECIES.forEach((def, i) => {
      const rowSeen = GameState.seenMonsters.includes(def.name);
      const rowCaught = GameState.caught.filter((n) => n === def.name).length;
      this.icons[i].setVisible(rowSeen);
      this.rows[i].setText(rowSeen ? `${def.name}${rowCaught > 0 ? ` (x${rowCaught})` : ""}` : "???");
      this.rows[i].setColor(rowSeen ? "#ffffff" : "#666666");
    });
  }

  destroy(): void {
    this.dim.destroy();
    this.panel.destroy();
    this.title.destroy();
    this.counter.destroy();
    for (const s of this.icons) s.destroy();
    for (const t of this.rows) t.destroy();
    // keys are shared instances from kb.addKey (same keycode → same object);
    // destroying them would wipe other panels' listeners. Scene shutdown
    // already tears every Key down via KeyboardPlugin.removeAllKeys(true).
  }
}
