import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { GameState } from "../gameState";
import { retroStyle } from "../pixelart";
import { Sfx } from "../audio";

interface ShopItem {
  label: string;
  price: number;
  key?: "sword" | "shield" | "ironSword" | "ironShield" | "amulet";
  buy(): string;
}

const SHOP_ITEMS: ShopItem[] = [
  {
    label: "POTION      10G",
    price: 10,
    buy: () => {
      GameState.inventory.potion += 1;
      return "Potion acquired!";
    },
  },
  {
    label: "MPOTION     15G",
    price: 15,
    buy: () => {
      GameState.inventory.mPotion += 1;
      return "MPotion acquired!";
    },
  },
  {
    label: "CANDY       20G",
    price: 20,
    buy: () => {
      GameState.inventory.candy += 1;
      return "Candy acquired!";
    },
  },
  {
    label: "HI-POTION   30G",
    price: 30,
    buy: () => {
      GameState.inventory.hiPotion += 1;
      return "Hi-Potion acquired!";
    },
  },
  {
    label: "ETHER       25G",
    price: 25,
    buy: () => {
      GameState.inventory.ether += 1;
      return "Ether acquired!";
    },
  },
  {
    label: "ELIXIR     100G",
    price: 100,
    buy: () => {
      GameState.inventory.elixir += 1;
      return "Elixir acquired!";
    },
  },
  {
    label: "BOMB        50G",
    price: 50,
    buy: () => {
      GameState.inventory.bomb += 1;
      return "Bomb acquired!";
    },
  },
  {
    label: "SWORD       80G",
    price: 80,
    key: "sword",
    buy: () => {
      GameState.inventory.sword += 1;
      return "Sword acquired!";
    },
  },
  {
    label: "SHIELD      80G",
    price: 80,
    key: "shield",
    buy: () => {
      GameState.inventory.shield += 1;
      return "Shield acquired!";
    },
  },
  {
    label: "IRON SWORD 180G",
    price: 180,
    key: "ironSword",
    buy: () => {
      GameState.inventory.ironSword += 1;
      return "Iron Sword acquired!";
    },
  },
  {
    label: "IRON SHIELD 180G",
    price: 180,
    key: "ironShield",
    buy: () => {
      GameState.inventory.ironShield += 1;
      return "Iron Shield acquired!";
    },
  },
  {
    label: "AMULET     120G",
    price: 120,
    key: "amulet",
    buy: () => {
      GameState.inventory.amulet += 1;
      return "Amulet acquired!";
    },
  },
];

const SHOP_COLS = 2;
const SHOP_ROW_GAP = 20;

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
  private keyLeft: Phaser.Input.Keyboard.Key;
  private keyRight: Phaser.Input.Keyboard.Key;
  private keyH: Phaser.Input.Keyboard.Key;
  private keyJ: Phaser.Input.Keyboard.Key;
  private keyK: Phaser.Input.Keyboard.Key;
  private keyL: Phaser.Input.Keyboard.Key;
  private keyZ: Phaser.Input.Keyboard.Key;
  private keyEsc: Phaser.Input.Keyboard.Key;

  private upQueued = false;
  private downQueued = false;
  private leftQueued = false;
  private rightQueued = false;
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
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, 460, 200, 0x0b0b2b, 0.95)
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

    let col = 0;
    let row = 0;
    for (const item of SHOP_ITEMS) {
      const t = scene.add
        .text(GAME_WIDTH / 2 - 200 + col * 220, GAME_HEIGHT / 2 - 52 + row * SHOP_ROW_GAP, item.label, retroStyle(6, "#ffffff"))
        .setOrigin(0, 0.5)
        .setScrollFactor(0)
        .setDepth(152)
        .setVisible(false);
      this.items.push(t);
      col++;
      if (col >= SHOP_COLS) {
        col = 0;
        row++;
      }
    }
    this.cursor = scene.add
      .text(GAME_WIDTH / 2 - 100, 0, ">", retroStyle(6, "#ffd166"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);

    this.goldText = scene.add
      .text(GAME_WIDTH / 2 + 150, GAME_HEIGHT / 2 - 84, "G 0", retroStyle(6, "#8ecbff"))
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
    this.keyLeft = kb.addKey(Phaser.Input.Keyboard.KeyCodes.LEFT);
    this.keyRight = kb.addKey(Phaser.Input.Keyboard.KeyCodes.RIGHT);
    this.keyH = kb.addKey(Phaser.Input.Keyboard.KeyCodes.H);
    this.keyJ = kb.addKey(Phaser.Input.Keyboard.KeyCodes.J);
    this.keyK = kb.addKey(Phaser.Input.Keyboard.KeyCodes.K);
    this.keyL = kb.addKey(Phaser.Input.Keyboard.KeyCodes.L);
    this.keyZ = kb.addKey(Phaser.Input.Keyboard.KeyCodes.Z);
    this.keyEsc = kb.addKey(Phaser.Input.Keyboard.KeyCodes.ESC);

    const DOWN = Phaser.Input.Keyboard.Events.DOWN;
    const queue = (flag: "upQueued" | "downQueued" | "leftQueued" | "rightQueued") => () => {
      this[flag] = true;
    };
    this.keyUp.on(DOWN, queue("upQueued"));
    this.keyK.on(DOWN, queue("upQueued"));
    this.keyDown.on(DOWN, queue("downQueued"));
    this.keyJ.on(DOWN, queue("downQueued"));
    this.keyLeft.on(DOWN, queue("leftQueued"));
    this.keyH.on(DOWN, queue("leftQueued"));
    this.keyRight.on(DOWN, queue("rightQueued"));
    this.keyL.on(DOWN, queue("rightQueued"));
    this.keyZ.on(DOWN, () => {
      this.zQueued = true;
    });
    this.keyEsc.on(DOWN, () => {
      this.escQueued = true;
    });
  }

  open(): void {
    this.active = true;
    this.index = 0;
    this.upQueued = false;
    this.downQueued = false;
    this.leftQueued = false;
    this.rightQueued = false;
    this.zQueued = false;
    this.escQueued = false;
    this.dim.setVisible(true);
    this.panel.setVisible(true);
    this.title.setVisible(true);
    this.goldText.setVisible(true);
    this.msg.setVisible(true);
    for (const t of this.items) t.setVisible(true);
    this.cursor.setVisible(true);
    this.refresh();
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
    const prev = this.index;
    if (this.upQueued) {
      this.upQueued = false;
      this.index = (this.index + SHOP_ITEMS.length - SHOP_COLS) % SHOP_ITEMS.length;
    }
    if (this.downQueued) {
      this.downQueued = false;
      this.index = (this.index + SHOP_COLS) % SHOP_ITEMS.length;
    }
    if (this.leftQueued) {
      this.leftQueued = false;
      this.index ^= 1;
    }
    if (this.rightQueued) {
      this.rightQueued = false;
      this.index ^= 1;
    }
    if (this.index !== prev) {
      Sfx.move();
      this.renderCursor();
    }
    if (this.zQueued) {
      this.zQueued = false;
      this.buy();
    }
  }

  private buy(): void {
    const item = SHOP_ITEMS[this.index];
    if (item.key && GameState.inventory[item.key] > 0) {
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
      const owned = item.key ? GameState.inventory[item.key] > 0 : false;
      this.items[i].setText(owned ? item.label.replace(/\d+G\s*$/, "SOLD") : item.label);
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
    this.msg.setText("");
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
    // keys are shared instances from kb.addKey (same keycode → same object);
    // destroying them would wipe other panels' listeners. Scene shutdown
    // already tears every Key down via KeyboardPlugin.removeAllKeys(true).
  }
}
