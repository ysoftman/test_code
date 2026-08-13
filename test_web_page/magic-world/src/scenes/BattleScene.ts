import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { GameState, expToNext } from "../gameState";
import { retroStyle } from "../pixelart";
import { Sfx } from "../audio";

interface EnemyDef {
  name: string;
  texture: string;
  hp: number;
  atk: number;
  def: number;
  exp: number;
  gold: number;
  boss?: boolean;
}

const ENEMIES: Record<string, EnemyDef> = {
  slime: { name: "SLIME", texture: "slime", hp: 16, atk: 5, def: 0, exp: 8, gold: 5 },
  goblin: { name: "GOBLIN", texture: "goblin", hp: 22, atk: 7, def: 1, exp: 14, gold: 9 },
  king: {
    name: "KING SLIME",
    texture: "slime",
    hp: 60,
    atk: 9,
    def: 2,
    exp: 80,
    gold: 120,
    boss: true,
  },
};

const MP_COST = 3;

type MenuAction = "fight" | "magic" | "run" | "potion" | "mPotion" | "candy";

interface ItemSlot {
  label: string;
  key: keyof typeof GameState.inventory;
  action: MenuAction;
}

const ITEM_SLOTS: ItemSlot[] = [
  { label: "POTION", key: "potion", action: "potion" },
  { label: "MPOTION", key: "mPotion", action: "mPotion" },
  { label: "CANDY", key: "candy", action: "candy" },
];

export class BattleScene extends Phaser.Scene {
  private enemy!: EnemyDef & { curHp: number };
  private enemySprite!: Phaser.GameObjects.Sprite;
  private playerSprite!: Phaser.GameObjects.Sprite;
  private msgText!: Phaser.GameObjects.Text;

  private menuIndex = 0;
  private menuItems: ("fight" | "magic" | "item" | "run")[] = ["fight", "magic", "item", "run"];
  private menuTexts: Phaser.GameObjects.Text[] = [];
  private cursor!: Phaser.GameObjects.Text;

  private inItems = false;
  private itemIndex = 0;
  private itemTexts: Phaser.GameObjects.Text[] = [];
  private itemCursor!: Phaser.GameObjects.Text;

  private playerHpBar!: Phaser.GameObjects.Rectangle;
  private enemyHpBar!: Phaser.GameObjects.Rectangle;
  private playerHpText!: Phaser.GameObjects.Text;
  private playerMpText!: Phaser.GameObjects.Text;
  private enemyHpText!: Phaser.GameObjects.Text;

  private running = false;
  private waitingAction: { resolve: (a: MenuAction) => void } | null = null;

  private keyLeft!: Phaser.Input.Keyboard.Key;
  private keyRight!: Phaser.Input.Keyboard.Key;
  private keyH!: Phaser.Input.Keyboard.Key;
  private keyL!: Phaser.Input.Keyboard.Key;
  private keyZ!: Phaser.Input.Keyboard.Key;
  private keyEsc!: Phaser.Input.Keyboard.Key;

  constructor() {
    super("Battle");
  }

  init(data: { enemy: string }): void {
    const def = ENEMIES[data.enemy] ?? ENEMIES.slime;
    this.enemy = { ...def, curHp: def.hp };
  }

  create(): void {
    this.menuIndex = 0;
    this.menuTexts = [];
    this.itemTexts = [];
    this.inItems = false;
    this.itemIndex = 0;
    this.waitingAction = null;

    this.add.image(GAME_WIDTH / 2, GAME_HEIGHT / 2, "battle-bg");

    this.enemySprite = this.add
      .sprite(GAME_WIDTH - 160, 140, this.enemy.texture)
      .setScale(this.enemy.boss ? 3 : 2);
    this.playerSprite = this.add.sprite(160, 184, "hero-down-0").setScale(2);
    this.playerSprite.setFlipX(true);

    this.window(16, 12, 232, 88);
    this.window(GAME_WIDTH - 248, 12, 232, 88);

    this.add
      .text(32, 20, GameState.player.name, retroStyle(7, "#ffd166"))
      .setOrigin(0, 0);
    this.playerHpText = this.add
      .text(32, 44, "HP " + GameState.player.hp + "/" + GameState.player.maxHp, retroStyle(6, "#ffffff"))
      .setOrigin(0, 0);
    this.playerMpText = this.add
      .text(32, 68, "MP " + GameState.player.mp + "/" + GameState.player.maxMp, retroStyle(6, "#8ecbff"))
      .setOrigin(0, 0);

    this.playerHpBar = this.add.rectangle(140, 52, 88, 8, 0x22c55e).setOrigin(0, 0.5);

    this.add
      .text(GAME_WIDTH - 232, 20, this.enemy.name, retroStyle(7, "#ff5555"))
      .setOrigin(0, 0);
    this.enemyHpText = this.add
      .text(GAME_WIDTH - 232, 44, "HP " + this.enemy.curHp + "/" + this.enemy.hp, retroStyle(6, "#ffffff"))
      .setOrigin(0, 0);
    this.enemyHpBar = this.add
      .rectangle(GAME_WIDTH - 140, 52, 88, 8, 0xef4444)
      .setOrigin(0, 0.5);

    this.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT - 30, GAME_WIDTH - 32, 56, 0x0b0b2b, 0.92)
      .setStrokeStyle(1, 0xffffff);
    this.msgText = this.add
      .text(32, GAME_HEIGHT - 52, "", retroStyle(8, "#f5f5f5"))
      .setWordWrapWidth(GAME_WIDTH - 64);

    const menuY = GAME_HEIGHT - 92;
    const labels: Record<string, string> = {
      fight: "FIGHT",
      magic: "MAGIC",
      item: "ITEM",
      run: "RUN",
    };
    let x = 64;
    for (const item of this.menuItems) {
      const t = this.add
        .text(x, menuY, labels[item], retroStyle(8, "#ffffff"))
        .setOrigin(0.5);
      this.menuTexts.push(t);
      x += 128;
    }
    this.cursor = this.add.text(0, menuY, ">", retroStyle(8, "#ffd166")).setOrigin(0.5);
    this.hideMenu();

    const itemY = GAME_HEIGHT - 116;
    let ix = 96;
    for (const slot of ITEM_SLOTS) {
      const t = this.add
        .text(ix, itemY, `${slot.label} x${GameState.inventory[slot.key]}`, retroStyle(6, "#ffffff"))
        .setOrigin(0.5)
        .setVisible(false);
      this.itemTexts.push(t);
      ix += 150;
    }
    this.itemCursor = this.add
      .text(0, itemY, ">", retroStyle(6, "#ffd166"))
      .setOrigin(0.5)
      .setVisible(false);

    const kb = this.input.keyboard!;
    this.keyLeft = kb.addKey(Phaser.Input.Keyboard.KeyCodes.LEFT);
    this.keyRight = kb.addKey(Phaser.Input.Keyboard.KeyCodes.RIGHT);
    this.keyH = kb.addKey(Phaser.Input.Keyboard.KeyCodes.H);
    this.keyL = kb.addKey(Phaser.Input.Keyboard.KeyCodes.L);
    this.keyZ = kb.addKey(Phaser.Input.Keyboard.KeyCodes.Z);
    this.keyEsc = kb.addKey(Phaser.Input.Keyboard.KeyCodes.ESC);

    this.running = true;
    this.runBattle();
  }

  update(_time: number, _delta: number): void {
    if (!this.waitingAction) return;

    if (this.inItems) {
      if (
        Phaser.Input.Keyboard.JustDown(this.keyLeft) ||
        Phaser.Input.Keyboard.JustDown(this.keyH)
      ) {
        this.itemIndex = (this.itemIndex + ITEM_SLOTS.length - 1) % ITEM_SLOTS.length;
        Sfx.move();
        this.renderItems();
        return;
      }
      if (
        Phaser.Input.Keyboard.JustDown(this.keyRight) ||
        Phaser.Input.Keyboard.JustDown(this.keyL)
      ) {
        this.itemIndex = (this.itemIndex + 1) % ITEM_SLOTS.length;
        Sfx.move();
        this.renderItems();
        return;
      }
      if (Phaser.Input.Keyboard.JustDown(this.keyEsc)) {
        this.inItems = false;
        this.hideItems();
        this.renderMenu();
        return;
      }
      if (Phaser.Input.Keyboard.JustDown(this.keyZ)) {
        const slot = ITEM_SLOTS[this.itemIndex];
        if (GameState.inventory[slot.key] <= 0) {
          Sfx.error();
          return;
        }
        this.inItems = false;
        this.hideItems();
        const waiter = this.waitingAction;
        this.waitingAction = null;
        this.hideMenu();
        waiter.resolve(slot.action);
      }
      return;
    }

    if (
      Phaser.Input.Keyboard.JustDown(this.keyLeft) ||
      Phaser.Input.Keyboard.JustDown(this.keyH)
    ) {
      this.menuIndex = (this.menuIndex + this.menuItems.length - 1) % this.menuItems.length;
      Sfx.move();
      this.renderMenu();
      return;
    }
    if (
      Phaser.Input.Keyboard.JustDown(this.keyRight) ||
      Phaser.Input.Keyboard.JustDown(this.keyL)
    ) {
      this.menuIndex = (this.menuIndex + 1) % this.menuItems.length;
      Sfx.move();
      this.renderMenu();
      return;
    }
    if (Phaser.Input.Keyboard.JustDown(this.keyZ)) {
      const item = this.menuItems[this.menuIndex];
      if (item === "item") {
        this.renderItems();
        this.inItems = true;
        return;
      }
      const waiter = this.waitingAction;
      this.waitingAction = null;
      this.hideMenu();
      waiter.resolve(item);
    }
  }

  private window(x: number, y: number, w: number, h: number): void {
    this.add
      .rectangle(x, y, w, h, 0x0b0b2b, 0.85)
      .setOrigin(0, 0)
      .setStrokeStyle(1, 0xffffff);
  }

  private hideMenu(): void {
    for (const t of this.menuTexts) t.setVisible(false);
    this.cursor.setVisible(false);
  }

  private renderMenu(): void {
    for (const t of this.menuTexts) t.setVisible(true);
    this.cursor.setVisible(true);
    const target = this.menuTexts[this.menuIndex];
    this.cursor.setX(target.x - 44);
    this.cursor.setY(target.y);
  }

  private hideItems(): void {
    for (const t of this.itemTexts) t.setVisible(false);
    this.itemCursor.setVisible(false);
  }

  private renderItems(): void {
    for (let i = 0; i < ITEM_SLOTS.length; i++) {
      this.itemTexts[i].setVisible(true);
      const count = GameState.inventory[ITEM_SLOTS[i].key];
      this.itemTexts[i].setText(`${ITEM_SLOTS[i].label} x${count}`);
      this.itemTexts[i].setColor(count > 0 ? "#ffffff" : "#666666");
    }
    this.itemCursor.setVisible(true);
    const target = this.itemTexts[this.itemIndex];
    this.itemCursor.setX(target.x - 44);
    this.itemCursor.setY(target.y);
  }

  private async runBattle(): Promise<void> {
    if (this.enemy.boss) Sfx.boss();
    await this.say(`${this.enemy.name} blocks your way!`);

    while (this.running) {
      if (GameState.player.hp <= 0) return this.defeat();

      let action = await this.playerTurn();
      if (action === "magic" && GameState.player.mp < MP_COST) {
        await this.say("Not enough MP!");
        action = await this.playerTurn();
      }

      switch (action) {
        case "run": {
          if (Math.random() < 0.5) {
            Sfx.run();
            await this.say("You escaped!");
            return this.end();
          }
          await this.say("Can't escape!");
          break;
        }
        case "fight":
          await this.playerAttack();
          break;
        case "magic":
          await this.playerMagic();
          break;
        case "potion":
          await this.usePotion();
          break;
        case "mPotion":
          await this.useMPotion();
          break;
        case "candy":
          await this.throwCandy();
          break;
      }

      if (!this.running) return;
      if (this.enemy.curHp <= 0) return this.victory();

      await this.enemyTurn();
    }
  }

  private playerTurn(): Promise<MenuAction> {
    this.renderMenu();
    return new Promise((resolve) => {
      this.waitingAction = { resolve };
    });
  }

  private async playerAttack(): Promise<void> {
    Sfx.attack();
    await this.lunge();
    const dmg = this.calcDamage(GameState.effAtk(), this.enemy.def);
    this.enemy.curHp = Math.max(0, this.enemy.curHp - dmg);
    this.enemySprite.setTintFill(0xffffff);
    this.flashDamage(this.enemySprite.x, this.enemySprite.y, dmg);
    await this.say(`You strike for ${dmg}!`);
    this.enemySprite.clearTint();
    this.updateEnemyHp();
  }

  private async playerMagic(): Promise<void> {
    Sfx.magic();
    GameState.player.mp -= MP_COST;
    this.updatePlayerStats();
    const dmg = 10 + Math.floor(Math.random() * 5);
    this.enemy.curHp = Math.max(0, this.enemy.curHp - dmg);
    this.enemySprite.setTintFill(0xffa500);
    this.flashDamage(this.enemySprite.x, this.enemySprite.y, dmg);
    await this.say(`FIRE! ${dmg} damage!`);
    this.enemySprite.clearTint();
    this.updateEnemyHp();
  }

  private async usePotion(): Promise<void> {
    Sfx.buy();
    GameState.inventory.potion -= 1;
    const healed = Math.min(GameState.player.maxHp - GameState.player.hp, 25);
    GameState.player.hp += healed;
    this.updatePlayerStats();
    await this.say(healed > 0 ? `Potion heals ${healed} HP!` : "Potion has no effect!");
  }

  private async useMPotion(): Promise<void> {
    Sfx.buy();
    GameState.inventory.mPotion -= 1;
    const restored = Math.min(GameState.player.maxMp - GameState.player.mp, 8);
    GameState.player.mp += restored;
    this.updatePlayerStats();
    await this.say(restored > 0 ? `Magic restores ${restored} MP!` : "MPotion has no effect!");
  }

  private async throwCandy(): Promise<void> {
    Sfx.capture();
    GameState.inventory.candy -= 1;
    if (this.enemy.boss) {
      await this.say("The KING SLIME is too strong!");
      return;
    }
    const ratio = this.enemy.curHp / this.enemy.hp;
    let chance = 0.15;
    if (ratio < 0.5) chance = 0.4 + (1 - ratio) * 0.3;
    if (Math.random() < chance) {
      GameState.caught.push(this.enemy.name);
      await this.say(`You caught ${this.enemy.name}!`);
      Sfx.victory();
      return this.victory(true);
    }
    await this.say("It broke free!");
  }

  private async enemyTurn(): Promise<void> {
    Sfx.hit();
    const dmg = this.calcDamage(this.enemy.atk, GameState.effDef());
    GameState.player.hp = Math.max(0, GameState.player.hp - dmg);
    this.playerSprite.setTintFill(0xff6666);
    this.flashDamage(this.playerSprite.x, this.playerSprite.y, dmg);
    await this.say(`${this.enemy.name} attacks for ${dmg}!`);
    this.playerSprite.clearTint();
    this.updatePlayerStats();
  }

  private async lunge(): Promise<void> {
    const startX = this.playerSprite.x;
    const targetX = this.enemySprite.x - 40;
    this.playerSprite.x = startX;
    await this.tweenPromise(this.playerSprite, { x: targetX }, 140);
    await this.tweenPromise(this.playerSprite, { x: startX }, 160);
  }

  private flashDamage(x: number, y: number, amount: number): void {
    const t = this.add
      .text(x + 20, y - 40, String(amount), retroStyle(10, "#ffdd44"))
      .setOrigin(0.5)
      .setStroke("#7c2d12", 2);
    this.tweens.add({
      targets: t,
      y: y - 80,
      alpha: 0,
      duration: 800,
      onComplete: () => t.destroy(),
    });
  }

  private calcDamage(atk: number, def: number): number {
    return Math.max(1, Math.floor(atk * (0.8 + Math.random() * 0.4)) - def);
  }

  private updateEnemyHp(): void {
    this.enemyHpText.setText(`HP ${this.enemy.curHp}/${this.enemy.hp}`);
    this.enemyHpBar.setScale(Math.max(0, this.enemy.curHp / this.enemy.hp), 1);
  }

  private updatePlayerStats(): void {
    this.playerHpText.setText(`HP ${GameState.player.hp}/${GameState.player.maxHp}`);
    this.playerMpText.setText(`MP ${GameState.player.mp}/${GameState.player.maxMp}`);
    this.playerHpBar.setScale(Math.max(0, GameState.player.hp / GameState.player.maxHp), 1);
  }

  private async victory(caught = false): Promise<void> {
    this.running = false;
    if (!caught) {
      GameState.gold += this.enemy.gold;
      GameState.battles += 1;
      if (this.enemy.name === "SLIME") GameState.quest.slimes += 1;
      if (this.enemy.boss) GameState.quest.bossDefeated = true;
      GameState.player.hp = Math.min(GameState.player.maxHp, GameState.player.hp + 5);
      GameState.player.mp = Math.min(GameState.player.maxMp, GameState.player.mp + 2);
      Sfx.victory();
      await this.say(`${this.enemy.name} is defeated!`);
      await this.say(`Gained ${this.enemy.gold} gold!`);
      GameState.player.exp += this.enemy.exp;
      let msg = `EXP +${this.enemy.exp}`;
      while (GameState.player.exp >= expToNext(GameState.player.level)) {
        GameState.player.exp -= expToNext(GameState.player.level);
        GameState.player.level += 1;
        GameState.player.maxHp += 5;
        GameState.player.maxMp += 2;
        GameState.player.atk += 1;
        GameState.player.def += 1;
        GameState.player.hp = GameState.player.maxHp;
        GameState.player.mp = GameState.player.maxMp;
        Sfx.levelup();
        msg = `LEVEL UP! LV ${GameState.player.level}`;
      }
      await this.say(msg);
      if (this.enemy.boss) await this.say("The KING SLIME is no more!");
    }
    GameState.save();
    await this.say("Press Z to continue.");
    this.end();
  }

  private async defeat(): Promise<void> {
    this.running = false;
    Sfx.gameover();
    await this.say("You have fallen...");
    await this.say("The world grows darker.");
    this.cameras.main.fadeOut(800, 0, 0, 0);
    this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
      GameState.reset();
      GameState.clearSave();
      this.scene.start("Title");
    });
  }

  private end(): void {
    this.running = false;
    GameState.lockEncounters(4000);
    this.cameras.main.fadeOut(400, 0, 0, 0);
    this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
      this.scene.start("World");
    });
  }

  private say(text: string): Promise<void> {
    return new Promise((resolve) => {
      this.msgText.setText("");
      let i = 0;
      const ev = this.time.addEvent({
        delay: 14,
        repeat: text.length,
        callback: () => {
          i++;
          this.msgText.setText(text.slice(0, i));
          if (i >= text.length) {
            ev.remove();
            this.awaitAdvance(resolve);
          }
        },
      });
    });
  }

  private awaitAdvance(resolve: () => void): void {
    const done = () => {
      this.input.keyboard?.removeListener("keydown-Z", done);
      this.input.keyboard?.removeListener("keydown-SPACE", done);
      this.input.off("pointerdown", done);
      resolve();
    };
    this.input.keyboard?.once("keydown-Z", done);
    this.input.keyboard?.once("keydown-SPACE", done);
    this.input.once("pointerdown", done);
  }

  private tweenPromise(
    target: Phaser.GameObjects.GameObject,
    props: object,
    duration: number
  ): Promise<void> {
    return new Promise((resolve) => {
      this.tweens.add({
        targets: target,
        ...props,
        duration,
        onComplete: () => resolve(),
      });
    });
  }
}
