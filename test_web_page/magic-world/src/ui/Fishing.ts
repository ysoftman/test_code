import Phaser from "phaser";
import { Sfx } from "../audio";
import { GAME_HEIGHT, GAME_WIDTH } from "../config";
import { GameState } from "../gameState";
import { retroStyle } from "../pixelart";

const PANEL_W = 380;
const PANEL_H = 300;
const PANEL_TOP = GAME_HEIGHT / 2 - PANEL_H / 2;
const WATER_Y = GAME_HEIGHT / 2 + 30;
const CAST_MIN = 1000;
const CAST_MAX = 2600;
const BITE_WINDOW = 700;
const RESULT_HOLD = 1400;

interface FishDef {
  name: string;
  min: number;
  max: number;
  chance: number;
}

const FISH_TABLE: FishDef[] = [
  { name: "MINNOW", min: 5, max: 10, chance: 0.45 },
  { name: "PERCH", min: 12, max: 20, chance: 0.3 },
  { name: "TROUT", min: 25, max: 40, chance: 0.17 },
  { name: "GOLDEN FISH", min: 80, max: 120, chance: 0.08 },
];

type FishState = "cast" | "bite" | "result";

export class FishingUI {
  private scene: Phaser.Scene;
  private active = false;
  private dirty = false;
  private state: FishState = "cast";
  private castAt = 0;
  private biteUntil = 0;
  private resultUntil = 0;

  private dim: Phaser.GameObjects.Rectangle;
  private panel: Phaser.GameObjects.Rectangle;
  private title: Phaser.GameObjects.Text;
  private water: Phaser.GameObjects.Ellipse;
  private bobber: Phaser.GameObjects.Container;
  private biteMark: Phaser.GameObjects.Text;
  private status: Phaser.GameObjects.Text;
  private count: Phaser.GameObjects.Text;
  private hint: Phaser.GameObjects.Text;
  private bobTween?: Phaser.Tweens.Tween;

  private zQueued = false;
  private escQueued = false;

  constructor(scene: Phaser.Scene) {
    this.scene = scene;

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
      .text(GAME_WIDTH / 2, PANEL_TOP + 34, "FISHING", retroStyle(8, "#38bdf8"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);
    this.water = scene.add
      .ellipse(GAME_WIDTH / 2, WATER_Y, 280, 34, 0x1e40af, 0.8)
      .setStrokeStyle(2, 0x60a5fa)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);
    this.bobber = scene.add.container(GAME_WIDTH / 2, WATER_Y, [
      scene.add.ellipse(0, 0, 12, 10, 0xef4444, 1),
      scene.add.ellipse(0, -4, 12, 5, 0xfef3c7, 1),
    ]);
    this.bobber.setScrollFactor(0).setDepth(153).setVisible(false);
    this.biteMark = scene.add
      .text(GAME_WIDTH / 2 + 24, WATER_Y - 30, "!", retroStyle(10, "#ffd166"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(153)
      .setVisible(false);
    this.status = scene.add
      .text(GAME_WIDTH / 2, PANEL_TOP + 140, "", retroStyle(6, "#f5f5f5"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);
    this.count = scene.add
      .text(GAME_WIDTH / 2, PANEL_TOP + 190, "", retroStyle(5, "#8ecbff"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);
    this.hint = scene.add
      .text(GAME_WIDTH / 2, PANEL_TOP + PANEL_H - 26, "Z: REEL  ESC: QUIT", retroStyle(5, "#9f9fd0"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);

    const kb = scene.input.keyboard!;
    kb.addKey(Phaser.Input.Keyboard.KeyCodes.Z).on(Phaser.Input.Keyboard.Events.DOWN, () => {
      this.zQueued = true;
    });
    kb.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE).on(Phaser.Input.Keyboard.Events.DOWN, () => {
      this.zQueued = true;
    });
    kb.addKey(Phaser.Input.Keyboard.KeyCodes.ESC).on(Phaser.Input.Keyboard.Events.DOWN, () => {
      this.escQueued = true;
    });
  }

  open(): void {
    this.active = true;
    this.dirty = false;
    this.zQueued = false;
    this.escQueued = false;
    this.dim.setVisible(true);
    this.panel.setVisible(true);
    this.title.setVisible(true);
    this.water.setVisible(true);
    this.bobber.setVisible(true);
    this.biteMark.setVisible(false);
    this.status.setVisible(true);
    this.count.setVisible(true);
    this.hint.setVisible(true);
    this.count.setText(`FISH CAUGHT: ${GameState.fishCaught}`);
    this.bobTween?.remove();
    this.bobTween = this.scene.tweens.add({
      targets: this.bobber,
      y: WATER_Y - 6,
      duration: 600,
      yoyo: true,
      repeat: -1,
      ease: "sine.inout",
    });
    this.startCast();
  }

  isActive(): boolean {
    return this.active;
  }

  update(): void {
    if (!this.active) return;
    if (this.escQueued) {
      this.escQueued = false;
      this.close();
      return;
    }
    const now = this.scene.time.now;
    if (this.state === "cast") {
      if (now >= this.castAt) {
        this.state = "bite";
        this.biteUntil = now + BITE_WINDOW;
        this.biteMark.setVisible(true);
        this.status.setText("!! BITE !!");
        this.bobber.setY(WATER_Y + 12);
        // a press made while casting must not carry into the window — only a
        // press inside the 700ms bite window should count as a catch
        this.zQueued = false;
        Sfx.hit();
      }
    } else if (this.state === "bite") {
      if (this.zQueued) {
        this.zQueued = false;
        this.catchFish();
      } else if (now >= this.biteUntil) {
        this.state = "result";
        this.resultUntil = now + RESULT_HOLD;
        this.biteMark.setVisible(false);
        this.bobber.setY(WATER_Y);
        this.status.setText("IT GOT AWAY...");
        Sfx.error();
      }
    } else if (this.state === "result" && now >= this.resultUntil) {
      this.startCast();
    }
  }

  private startCast(): void {
    this.state = "cast";
    this.castAt = this.scene.time.now + Phaser.Math.Between(CAST_MIN, CAST_MAX);
    this.biteMark.setVisible(false);
    this.bobber.setY(WATER_Y);
    this.status.setText("CASTING...");
    // a Z press while casting must not carry into the bite window — only a
    // press inside the window (700ms) should count as a catch
    this.zQueued = false;
    Sfx.move();
  }

  private catchFish(): void {
    this.state = "result";
    this.resultUntil = this.scene.time.now + RESULT_HOLD;
    this.biteMark.setVisible(false);
    this.bobber.setY(WATER_Y);
    let r = Math.random();
    let fish: FishDef = FISH_TABLE[FISH_TABLE.length - 1];
    for (const f of FISH_TABLE) {
      if (r < f.chance) {
        fish = f;
        break;
      }
      r -= f.chance;
    }
    const gold = Phaser.Math.Between(fish.min, fish.max);
    GameState.gainGold(gold);
    GameState.fishCaught += 1;
    this.dirty = true;
    this.count.setText(`FISH CAUGHT: ${GameState.fishCaught}`);
    if (fish.name === "GOLDEN FISH") {
      GameState.inventory.potion += 1;
      this.status.setText(`CAUGHT: GOLDEN FISH! +${gold}G +POTION`);
      Sfx.victory();
    } else {
      this.status.setText(`CAUGHT: ${fish.name}  +${gold}G`);
      Sfx.pickup();
    }
  }

  private close(): void {
    this.active = false;
    this.bobTween?.remove();
    this.dim.setVisible(false);
    this.panel.setVisible(false);
    this.title.setVisible(false);
    this.water.setVisible(false);
    this.bobber.setVisible(false);
    this.biteMark.setVisible(false);
    this.status.setVisible(false);
    this.count.setVisible(false);
    this.hint.setVisible(false);
    if (this.dirty) GameState.save();
  }

  destroy(): void {
    this.bobTween?.remove();
    this.dim.destroy();
    this.panel.destroy();
    this.title.destroy();
    this.water.destroy();
    this.bobber.destroy();
    this.biteMark.destroy();
    this.status.destroy();
    this.count.destroy();
    this.hint.destroy();
  }
}
