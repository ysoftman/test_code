import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { GameState } from "../gameState";
import { retroStyle } from "../pixelart";
import { Sfx } from "../audio";

interface ShopItem {
  label: string;
  price: number;
  owned?: boolean;
  buy(): string;
}

const SHOP_ITEMS: ShopItem[] = [
  {
    label: "POTION   10G",
    price: 10,
    buy: () => {
      GameState.inventory.potion += 1;
      return "Potion acquired!";
    },
  },
  {
    label: "MPOTION  15G",
    price: 15,
    buy: () => {
      GameState.inventory.mPotion += 1;
      return "MPotion acquired!";
    },
  },
  {
    label: "CANDY    20G",
    price: 20,
    buy: () => {
      GameState.inventory.candy += 1;
      return "Candy acquired!";
    },
  },
  {
    label: "SWORD    80G",
    price: 80,
    owned: true,
    buy: () => {
      GameState.sword = true;
      return "ATK +2!";
    },
  },
  {
    label: "SHIELD   80G",
    price: 80,
    owned: true,
    buy: () => {
      GameState.shield = true;
      return "DEF +2!";
    },
  },
];

export class ShopUI {
  private scene: Phaser.Scene;
  private active = false;
  private index = 0;

  private dim: Phaser.GameObjects.Rectangle;
  private panel: Phaser.GameObjects.Rectangle;
  private title: Phaser.GameObjects.Text;
  private items: Phaser.GameObjects.Text[] = [];
  private cursor: Phaser.GameObjects.Text;
  private goldText: Phaser.GameObjects.Text;
  private msg: Phaser.GameObjects.Text;
  private msgTimer?: Phaser.Time.TimerEvent;

  private keyUp: Phaser.Input.Keyboard.Key;
  private keyDown: Phaser.Input.Keyboard.Key;
  private keyH: Phaser.Input.Keyboard.Key;
  private keyJ: Phaser.Input.Keyboard.Key;
  private keyK: Phaser.Input.Keyboard.Key;
  private keyL: Phaser.Input.Keyboard.Key;
  private keyZ: Phaser.Input.Keyboard.Key;
  private keyEsc: Phaser.Input.Keyboard.Key;

  constructor(scene: Phaser.Scene) {
    this.scene = scene;

    this.dim = scene.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH, GAME_HEIGHT, 0x000000, 0.5)
      .setScrollFactor(0)
      .setDepth(150)
      .setVisible(false);
    this.panel = scene.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, 300, 200, 0x0b0b2b, 0.95)
      .setScrollFactor(0)
      .setDepth(151)
      .setStrokeStyle(2, 0xffffff)
      .setVisible(false);
    this.title = scene.add
      .text(GAME_WIDTH / 2, GAME_HEIGHT / 2 - 84, "SHOP", retroStyle(8, "#ffd166"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);

    let y = GAME_HEIGHT / 2 - 52;
    for (const item of SHOP_ITEMS) {
      const t = scene.add
        .text(GAME_WIDTH / 2 - 80, y, item.label, retroStyle(6, "#ffffff"))
        .setOrigin(0, 0.5)
        .setScrollFactor(0)
        .setDepth(152)
        .setVisible(false);
      this.items.push(t);
      y += 22;
    }
    this.cursor = scene.add
      .text(GAME_WIDTH / 2 - 100, 0, ">", retroStyle(6, "#ffd166"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);

    this.goldText = scene.add
      .text(GAME_WIDTH / 2 + 80, GAME_HEIGHT / 2 - 84, "G 0", retroStyle(6, "#8ecbff"))
      .setOrigin(1, 0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);
    this.msg = scene.add
      .text(GAME_WIDTH / 2, GAME_HEIGHT / 2 + 64, "", retroStyle(6, "#f5f5f5"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);

    const kb = scene.input.keyboard!;
    this.keyUp = kb.addKey(Phaser.Input.Keyboard.KeyCodes.UP);
    this.keyDown = kb.addKey(Phaser.Input.Keyboard.KeyCodes.DOWN);
    this.keyH = kb.addKey(Phaser.Input.Keyboard.KeyCodes.H);
    this.keyJ = kb.addKey(Phaser.Input.Keyboard.KeyCodes.J);
    this.keyK = kb.addKey(Phaser.Input.Keyboard.KeyCodes.K);
    this.keyL = kb.addKey(Phaser.Input.Keyboard.KeyCodes.L);
    this.keyZ = kb.addKey(Phaser.Input.Keyboard.KeyCodes.Z);
    this.keyEsc = kb.addKey(Phaser.Input.Keyboard.KeyCodes.ESC);
  }

  open(): void {
    this.active = true;
    this.index = 0;
    this.dim.setVisible(true);
    this.panel.setVisible(true);
    this.title.setVisible(true);
    this.goldText.setVisible(true);
    this.msg.setVisible(true);
    this.refresh();
  }

  isActive(): boolean {
    return this.active;
  }

  update(): void {
    if (!this.active) return;
    if (Phaser.Input.Keyboard.JustDown(this.keyEsc)) {
      this.close();
      return;
    }
    const prev = this.index;
    if (
      Phaser.Input.Keyboard.JustDown(this.keyUp) ||
      Phaser.Input.Keyboard.JustDown(this.keyK)
    ) {
      this.index = (this.index + SHOP_ITEMS.length - 1) % SHOP_ITEMS.length;
    }
    if (
      Phaser.Input.Keyboard.JustDown(this.keyDown) ||
      Phaser.Input.Keyboard.JustDown(this.keyJ)
    ) {
      this.index = (this.index + 1) % SHOP_ITEMS.length;
    }
    if (this.index !== prev) {
      Sfx.move();
      this.renderCursor();
    }
    if (Phaser.Input.Keyboard.JustDown(this.keyZ)) {
      this.buy();
    }
  }

  private buy(): void {
    const item = SHOP_ITEMS[this.index];
    if (item.owned && (item.label.includes("SWORD") ? GameState.sword : GameState.shield)) {
      Sfx.error();
      this.showMsg("Already owned!");
      return;
    }
    if (GameState.gold < item.price) {
      Sfx.error();
      this.showMsg("Not enough gold!");
      return;
    }
    GameState.gold -= item.price;
    const result = item.buy();
    Sfx.buy();
    GameState.save();
    this.showMsg(result);
    this.refresh();
  }

  private showMsg(text: string): void {
    this.msgTimer?.remove();
    this.msg.setText(text);
    this.msgTimer = this.scene.time.addEvent({
      delay: 1200,
      callback: () => this.msg.setText(""),
    });
  }

  private refresh(): void {
    this.goldText.setText("G " + GameState.gold);
    for (let i = 0; i < SHOP_ITEMS.length; i++) {
      const item = SHOP_ITEMS[i];
      let owned = false;
      if (item.owned) owned = item.label.includes("SWORD") ? GameState.sword : GameState.shield;
      this.items[i].setText(item.label + (owned ? "  SOLD" : ""));
      this.items[i].setColor(owned ? "#666666" : "#ffffff");
    }
    this.renderCursor();
  }

  private renderCursor(): void {
    const target = this.items[this.index];
    this.cursor.setX(target.x - 12);
    this.cursor.setY(target.y);
  }

  private close(): void {
    this.active = false;
    this.dim.setVisible(false);
    this.panel.setVisible(false);
    this.title.setVisible(false);
    this.goldText.setVisible(false);
    this.msg.setVisible(false);
    this.msgTimer?.remove();
    for (const t of this.items) t.setVisible(false);
    this.cursor.setVisible(false);
  }

  destroy(): void {
    this.dim.destroy();
    this.panel.destroy();
    this.title.destroy();
    this.goldText.destroy();
    this.msg.destroy();
    this.msgTimer?.remove();
    for (const t of this.items) t.destroy();
    this.cursor.destroy();
    this.keyUp.destroy();
    this.keyDown.destroy();
    this.keyH.destroy();
    this.keyJ.destroy();
    this.keyK.destroy();
    this.keyL.destroy();
    this.keyZ.destroy();
    this.keyEsc.destroy();
  }
}
