import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { GameState } from "../gameState";
import { retroStyle } from "../pixelart";

interface EnemyDef {
  name: string;
  texture: string;
  hp: number;
  atk: number;
  def: number;
  exp: number;
  gold: number;
}

const ENEMIES: Record<string, EnemyDef> = {
  slime: { name: "SLIME", texture: "slime", hp: 16, atk: 5, def: 0, exp: 8, gold: 5 },
  goblin: { name: "GOBLIN", texture: "goblin", hp: 22, atk: 7, def: 1, exp: 14, gold: 9 },
};

const MP_COST = 3;

type MenuAction = "fight" | "magic" | "run";

export class BattleScene extends Phaser.Scene {
  private enemy!: EnemyDef & { curHp: number };
  private enemySprite!: Phaser.GameObjects.Sprite;
  private playerSprite!: Phaser.GameObjects.Sprite;
  private msgText!: Phaser.GameObjects.Text;

  private menuIndex = 0;
  private menuItems: MenuAction[] = ["fight", "magic", "run"];
  private menuTexts: Phaser.GameObjects.Text[] = [];
  private cursor!: Phaser.GameObjects.Text;

  private playerHpBar!: Phaser.GameObjects.Rectangle;
  private enemyHpBar!: Phaser.GameObjects.Rectangle;
  private playerHpText!: Phaser.GameObjects.Text;
  private playerMpText!: Phaser.GameObjects.Text;
  private enemyHpText!: Phaser.GameObjects.Text;

  private running = false;
  private waitingAction: { resolve: (a: MenuAction) => void } | null = null;

  private keyLeft!: Phaser.Input.Keyboard.Key;
  private keyRight!: Phaser.Input.Keyboard.Key;
  private keyZ!: Phaser.Input.Keyboard.Key;

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
    this.waitingAction = null;

    this.add.image(GAME_WIDTH / 2, GAME_HEIGHT / 2, "battle-bg");

    this.enemySprite = this.add
      .sprite(GAME_WIDTH - 80, 70, this.enemy.texture)
      .setScale(2);
    this.playerSprite = this.add.sprite(80, 92, "hero-down-0").setScale(2);
    this.playerSprite.setFlipX(true);

    this.window(8, 6, 116, 44);
    this.window(GAME_WIDTH - 124, 6, 116, 44);

    this.add
      .text(16, 10, GameState.player.name, retroStyle(7, "#ffd166"))
      .setOrigin(0, 0);
    this.playerHpText = this.add
      .text(16, 22, "HP " + GameState.player.hp + "/" + GameState.player.maxHp, retroStyle(6, "#ffffff"))
      .setOrigin(0, 0);
    this.playerMpText = this.add
      .text(16, 34, "MP " + GameState.player.mp + "/" + GameState.player.maxMp, retroStyle(6, "#8ecbff"))
      .setOrigin(0, 0);

    this.playerHpBar = this.add.rectangle(70, 26, 44, 4, 0x22c55e).setOrigin(0, 0.5);

    this.add
      .text(GAME_WIDTH - 116, 10, this.enemy.name, retroStyle(7, "#ff5555"))
      .setOrigin(0, 0);
    this.enemyHpText = this.add
      .text(GAME_WIDTH - 116, 22, "HP " + this.enemy.curHp + "/" + this.enemy.hp, retroStyle(6, "#ffffff"))
      .setOrigin(0, 0);
    this.enemyHpBar = this.add
      .rectangle(GAME_WIDTH - 70, 26, 44, 4, 0xef4444)
      .setOrigin(0, 0.5);

    this.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT - 15, GAME_WIDTH - 16, 28, 0x0b0b2b, 0.92)
      .setStrokeStyle(1, 0xffffff);
    this.msgText = this.add
      .text(16, GAME_HEIGHT - 26, "", retroStyle(8, "#f5f5f5"))
      .setWordWrapWidth(GAME_WIDTH - 32);

    const menuY = GAME_HEIGHT - 46;
    const labels: Record<MenuAction, string> = {
      fight: "FIGHT",
      magic: "MAGIC",
      run: "RUN",
    };
    let x = 40;
    for (const item of this.menuItems) {
      const t = this.add
        .text(x, menuY, labels[item], retroStyle(8, "#ffffff"))
        .setOrigin(0.5);
      this.menuTexts.push(t);
      x += 64;
    }
    this.cursor = this.add.text(0, menuY, ">", retroStyle(8, "#ffd166")).setOrigin(0.5);
    this.hideMenu();

    const kb = this.input.keyboard!;
    this.keyLeft = kb.addKey(Phaser.Input.Keyboard.KeyCodes.LEFT);
    this.keyRight = kb.addKey(Phaser.Input.Keyboard.KeyCodes.RIGHT);
    this.keyZ = kb.addKey(Phaser.Input.Keyboard.KeyCodes.Z);

    this.running = true;
    this.runBattle();
  }

  update(_time: number, _delta: number): void {
    if (this.waitingAction) {
      if (Phaser.Input.Keyboard.JustDown(this.keyLeft)) {
        this.menuIndex = (this.menuIndex + this.menuItems.length - 1) % this.menuItems.length;
        this.renderMenu();
      }
      if (Phaser.Input.Keyboard.JustDown(this.keyRight)) {
        this.menuIndex = (this.menuIndex + 1) % this.menuItems.length;
        this.renderMenu();
      }
      if (Phaser.Input.Keyboard.JustDown(this.keyZ)) {
        const action = this.menuItems[this.menuIndex];
        const waiter = this.waitingAction;
        this.waitingAction = null;
        this.hideMenu();
        waiter.resolve(action);
      }
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
    this.cursor.setX(target.x - 22);
    this.cursor.setY(target.y);
  }

  private showMenu(): void {
    this.renderMenu();
  }

  private async runBattle(): Promise<void> {
    await this.say(`${this.enemy.name} blocks your way!`);

    while (this.running) {
      if (GameState.player.hp <= 0) return this.defeat();

      let action = await this.playerTurn();
      if (action === "magic" && GameState.player.mp < MP_COST) {
        await this.say("Not enough MP!");
        action = await this.playerTurn();
      }

      if (action === "run") {
        if (Math.random() < 0.5) {
          await this.say("You escaped!");
          return this.end();
        }
        await this.say("Can't escape!");
      } else if (action === "fight") {
        await this.playerAttack();
      } else {
        await this.playerMagic();
      }

      if (!this.running) return;
      if (this.enemy.curHp <= 0) return this.victory();

      await this.enemyTurn();
    }
  }

  private playerTurn(): Promise<MenuAction> {
    this.showMenu();
    return new Promise((resolve) => {
      this.waitingAction = { resolve };
    });
  }

  private async playerAttack(): Promise<void> {
    await this.lunge();
    const dmg = this.calcDamage(GameState.player.atk, this.enemy.def);
    this.enemy.curHp = Math.max(0, this.enemy.curHp - dmg);
    this.enemySprite.setTintFill(0xffffff);
    this.flashDamage(this.enemySprite.x, this.enemySprite.y, dmg);
    await this.say(`You strike for ${dmg}!`);
    this.enemySprite.clearTint();
    this.updateEnemyHp();
  }

  private async playerMagic(): Promise<void> {
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

  private async enemyTurn(): Promise<void> {
    const dmg = this.calcDamage(this.enemy.atk, GameState.player.def);
    GameState.player.hp = Math.max(0, GameState.player.hp - dmg);
    this.playerSprite.setTintFill(0xff6666);
    this.flashDamage(this.playerSprite.x, this.playerSprite.y, dmg);
    await this.say(`${this.enemy.name} attacks for ${dmg}!`);
    this.playerSprite.clearTint();
    this.updatePlayerStats();
  }

  private async lunge(): Promise<void> {
    const startX = this.playerSprite.x;
    const targetX = this.enemySprite.x - 20;
    this.playerSprite.x = startX;
    await this.tweenPromise(this.playerSprite, { x: targetX }, 140);
    await this.tweenPromise(this.playerSprite, { x: startX }, 160);
  }

  private flashDamage(x: number, y: number, amount: number): void {
    const t = this.add
      .text(x + 10, y - 20, String(amount), retroStyle(10, "#ffdd44"))
      .setOrigin(0.5)
      .setStroke("#7c2d12", 2);
    this.tweens.add({
      targets: t,
      y: y - 40,
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

  private async victory(): Promise<void> {
    this.running = false;
    GameState.gold += this.enemy.gold;
    GameState.battles += 1;
    GameState.player.hp = Math.min(GameState.player.maxHp, GameState.player.hp + 5);
    GameState.player.mp = Math.min(GameState.player.maxMp, GameState.player.mp + 2);
    await this.say(`${this.enemy.name} is defeated!`);
    await this.say(`Gained ${this.enemy.gold} gold!`);
    await this.say("You recovered a little.");
    await this.say("Press Z to continue.");
    this.end();
  }

  private async defeat(): Promise<void> {
    this.running = false;
    await this.say("You have fallen...");
    await this.say("The world grows darker.");
    this.cameras.main.fadeOut(800, 0, 0, 0);
    this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
      GameState.reset();
      this.scene.start("Title");
    });
  }

  private end(): void {
    this.running = false;
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
