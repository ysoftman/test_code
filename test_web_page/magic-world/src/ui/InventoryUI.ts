import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { GameState, EquipmentKey } from "../gameState";
import { retroStyle } from "../pixelart";
import { Sfx } from "../audio";

type ConsumableKey = "potion" | "mPotion" | "candy" | "hiPotion" | "ether" | "elixir" | "bomb";

interface BaseItem {
  label: string;
  key: ConsumableKey | EquipmentKey;
}
interface UseItem extends BaseItem {
  kind: "use";
  use(): string;
}
interface EquipItem extends BaseItem {
  kind: "equip";
}
type InventoryItem = UseItem | EquipItem;

const INVENTORY_COLS = 2;
const INVENTORY_ROW_GAP = 40;

const INVENTORY_ITEMS: InventoryItem[] = [
  {
    label: "POTION",
    key: "potion",
    kind: "use",
    use: () => {
      const healed = Math.min(GameState.effMaxHp() - GameState.player.hp, 25);
      GameState.player.hp += healed;
      return healed > 0 ? `HP +${healed}!` : "HP is already full!";
    },
  },
  {
    label: "BOMB",
    key: "bomb",
    kind: "use",
    use: () => "Bomb is for battle!",
  },
  {
    label: "MPOTION",
    key: "mPotion",
    kind: "use",
    use: () => {
      const restored = Math.min(GameState.player.maxMp - GameState.player.mp, 8);
      GameState.player.mp += restored;
      return restored > 0 ? `MP +${restored}!` : "MP is already full!";
    },
  },
  {
    label: "SWORD",
    key: "sword",
    kind: "equip",
  },
  {
    label: "CANDY",
    key: "candy",
    kind: "use",
    use: () => "Candy is for battle!",
  },
  {
    label: "SHIELD",
    key: "shield",
    kind: "equip",
  },
  {
    label: "HI-POTION",
    key: "hiPotion",
    kind: "use",
    use: () => {
      const healed = Math.min(GameState.effMaxHp() - GameState.player.hp, 50);
      GameState.player.hp += healed;
      return healed > 0 ? `HP +${healed}!` : "HP is already full!";
    },
  },
  {
    label: "IRON SWORD",
    key: "ironSword",
    kind: "equip",
  },
  {
    label: "ETHER",
    key: "ether",
    kind: "use",
    use: () => {
      const restored = Math.min(GameState.player.maxMp - GameState.player.mp, 12);
      GameState.player.mp += restored;
      return restored > 0 ? `MP +${restored}!` : "MP is already full!";
    },
  },
  {
    label: "IRON SHIELD",
    key: "ironShield",
    kind: "equip",
  },
  {
    label: "ELIXIR",
    key: "elixir",
    kind: "use",
    use: () => {
      GameState.player.hp = GameState.effMaxHp();
      GameState.player.mp = GameState.player.maxMp;
      return "HP and MP fully restored!";
    },
  },
  {
    label: "AMULET",
    key: "amulet",
    kind: "equip",
  },
  {
    label: "MYTHRIL SWORD",
    key: "mythrilSword",
    kind: "equip",
  },
  {
    label: "MYTHRIL SHIELD",
    key: "mythrilShield",
    kind: "equip",
  },
];

export class InventoryUI {
  private scene: Phaser.Scene;
  private active = false;
  private index = 0;

  private dim: Phaser.GameObjects.Rectangle;
  private panel: Phaser.GameObjects.Rectangle;
  private title: Phaser.GameObjects.Text;
  private items: Phaser.GameObjects.Text[] = [];
  private cursor: Phaser.GameObjects.Text;
  private statusText: Phaser.GameObjects.Text;
  private msg: Phaser.GameObjects.Text;
  private msgTimer?: Phaser.Time.TimerEvent;

  private keyUp: Phaser.Input.Keyboard.Key;
  private keyDown: Phaser.Input.Keyboard.Key;
  private keyLeft: Phaser.Input.Keyboard.Key;
  private keyRight: Phaser.Input.Keyboard.Key;
  private keyH: Phaser.Input.Keyboard.Key;
  private keyK: Phaser.Input.Keyboard.Key;
  private keyJ: Phaser.Input.Keyboard.Key;
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
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, 1000, 400, 0x0b0b2b, 0.95)
      .setScrollFactor(0)
      .setDepth(151)
      .setStrokeStyle(2, 0xffffff)
      .setVisible(false);
    this.title = scene.add
      .text(GAME_WIDTH / 2, GAME_HEIGHT / 2 - 136, "ITEMS", retroStyle(8, "#ffd166"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);

    let col = 0;
    let row = 0;
    for (const item of INVENTORY_ITEMS) {
      const t = scene.add
        .text(
          GAME_WIDTH / 2 - 440 + col * 480,
          GAME_HEIGHT / 2 - 72 + row * INVENTORY_ROW_GAP,
          `${item.label} x0`,
          retroStyle(6, "#ffffff")
        )
        .setOrigin(0, 0.5)
        .setScrollFactor(0)
        .setDepth(152)
        .setVisible(false);
      this.items.push(t);
      col++;
      if (col >= INVENTORY_COLS) {
        col = 0;
        row++;
      }
    }
    this.cursor = scene.add
      .text(GAME_WIDTH / 2 - 200, 0, ">", retroStyle(6, "#ffd166"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);

    this.statusText = scene.add
      .text(GAME_WIDTH / 2 + 300, GAME_HEIGHT / 2 - 168, "", retroStyle(5, "#8ecbff"))
      .setOrigin(1, 0.5)
      .setScrollFactor(0)
      .setDepth(152)
      .setVisible(false);
    this.msg = scene.add
      .text(GAME_WIDTH / 2, GAME_HEIGHT / 2 + 104, "", retroStyle(6, "#f5f5f5"))
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
    this.keyK = kb.addKey(Phaser.Input.Keyboard.KeyCodes.K);
    this.keyJ = kb.addKey(Phaser.Input.Keyboard.KeyCodes.J);
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
    this.statusText.setVisible(true);
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
      this.index = (this.index + INVENTORY_ITEMS.length - INVENTORY_COLS) % INVENTORY_ITEMS.length;
    }
    if (this.downQueued) {
      this.downQueued = false;
      this.index = (this.index + INVENTORY_COLS) % INVENTORY_ITEMS.length;
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
      this.useItem();
    }
  }

  private useItem(): void {
    const item = INVENTORY_ITEMS[this.index];
    if (GameState.inventory[item.key] <= 0) {
      Sfx.error();
      this.showMsg("Not owned!");
      return;
    }
    if (item.kind === "equip") {
      const result = GameState.equipToggle(item.key as EquipmentKey);
      Sfx.buy();
      GameState.save();
      this.showMsg(result);
      this.refresh();
      return;
    }
    switch (item.key) {
      case "candy":
        Sfx.error();
        this.showMsg("Candy is for battle!");
        return;
      case "bomb":
        Sfx.error();
        this.showMsg("Bomb is for battle!");
        return;
      case "potion":
      case "hiPotion":
        if (GameState.player.hp >= GameState.effMaxHp()) {
          Sfx.error();
          this.showMsg("HP is already full!");
          return;
        }
        break;
      case "mPotion":
      case "ether":
        if (GameState.player.mp >= GameState.player.maxMp) {
          Sfx.error();
          this.showMsg("MP is already full!");
          return;
        }
        break;
      case "elixir":
        if (
          GameState.player.hp >= GameState.effMaxHp() &&
          GameState.player.mp >= GameState.player.maxMp
        ) {
          Sfx.error();
          this.showMsg("HP and MP are already full!");
          return;
        }
        break;
    }
    GameState.inventory[item.key] -= 1;
    const result = item.use();
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
    const p = GameState.player;
    this.statusText.setText(`HP ${p.hp}/${GameState.effMaxHp()}\nMP ${p.mp}/${p.maxMp}`);
    for (let i = 0; i < INVENTORY_ITEMS.length; i++) {
      const item = INVENTORY_ITEMS[i];
      const count = GameState.inventory[item.key];
      if (item.kind === "equip") {
        const equipped = GameState.isEquipped(item.key as EquipmentKey);
        this.items[i].setText(`${item.label} x${count}` + (equipped ? " (E)" : ""));
        this.items[i].setColor(equipped ? "#ffd166" : count > 0 ? "#ffffff" : "#666666");
      } else {
        this.items[i].setText(`${item.label} x${count}`);
        this.items[i].setColor(count > 0 ? "#ffffff" : "#666666");
      }
    }
    this.renderCursor();
  }

  private renderCursor(): void {
    const target = this.items[this.index];
    this.cursor.setX(target.x - 24);
    this.cursor.setY(target.y);
  }

  close(): void {
    this.active = false;
    this.dim.setVisible(false);
    this.panel.setVisible(false);
    this.title.setVisible(false);
    this.statusText.setVisible(false);
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
    this.statusText.destroy();
    this.msg.destroy();
    this.msgTimer?.remove();
    for (const t of this.items) t.destroy();
    this.cursor.destroy();
    // keys are shared instances from kb.addKey (same keycode → same object);
    // destroying them would wipe other panels' listeners. Scene shutdown
    // already tears every Key down via KeyboardPlugin.removeAllKeys(true).
  }
}