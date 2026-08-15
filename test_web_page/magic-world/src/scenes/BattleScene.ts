import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { GameState, expToNext, onSaved } from "../gameState";
import { retroStyle, showToast } from "../pixelart";
import { Sfx, BATTLE_THEME } from "../audio";
import { ENEMIES, EnemyDef } from "../monsters";

const MP_COST = 3;
const CRIT_CHANCE = 0.1;
const CRIT_MULT = 2;

type MenuAction = "fight" | "magic" | "run" | "potion" | "mPotion" | "candy" | "hiPotion" | "ether" | "elixir" | "bomb";

interface ItemSlot {
  label: string;
  key: keyof typeof GameState.inventory;
  action: MenuAction;
}

const ITEM_SLOTS: ItemSlot[] = [
  { label: "POTION", key: "potion", action: "potion" },
  { label: "MPOTION", key: "mPotion", action: "mPotion" },
  { label: "CANDY", key: "candy", action: "candy" },
  { label: "HI-POTION", key: "hiPotion", action: "hiPotion" },
  { label: "ETHER", key: "ether", action: "ether" },
  { label: "ELIXIR", key: "elixir", action: "elixir" },
  { label: "BOMB", key: "bomb", action: "bomb" },
];

const ITEMS_PER_ROW = 4;
const ITEM_COL_X = 24;
const ITEM_COL_WIDTH = 140;
const ITEM_TEXT_OFFSET = 16;

export class BattleScene extends Phaser.Scene {
  private enemy!: EnemyDef & { curHp: number };
  private enemySprite!: Phaser.GameObjects.Sprite;
  private playerSprite!: Phaser.GameObjects.Sprite;
  private weaponOverlay!: Phaser.GameObjects.Sprite;
  private shieldOverlay!: Phaser.GameObjects.Sprite;
  private msgText!: Phaser.GameObjects.Text;

  private menuItems: ("fight" | "magic" | "item" | "run")[] = ["fight", "magic", "item", "run"];
  private menuTexts: Phaser.GameObjects.Text[] = [];

  private inItems = false;
  private itemIndex = 0;
  private itemTexts: Phaser.GameObjects.Text[] = [];
  private itemCursor!: Phaser.GameObjects.Text;
  private hintText!: Phaser.GameObjects.Text;

  private playerHpBar!: Phaser.GameObjects.Rectangle;
  private enemyHpBar!: Phaser.GameObjects.Rectangle;
  private playerHpText!: Phaser.GameObjects.Text;
  private playerMpText!: Phaser.GameObjects.Text;
  private enemyHpText!: Phaser.GameObjects.Text;

  private running = false;
  private waitingAction: { resolve: (a: MenuAction) => void } | null = null;
  private origin: "World" | "Dungeon" = "World";

  private hitBurst!: Phaser.GameObjects.Particles.ParticleEmitter;
  private glowBurst!: Phaser.GameObjects.Particles.ParticleEmitter;
  private healBurst!: Phaser.GameObjects.Particles.ParticleEmitter;
  private levelBurst!: Phaser.GameObjects.Particles.ParticleEmitter;
  private coinBurst!: Phaser.GameObjects.Particles.ParticleEmitter;

  constructor() {
    super("Battle");
  }

  init(data: { enemy: string; from?: "World" | "Dungeon" }): void {
    const def = ENEMIES[data?.enemy ?? ""] ?? ENEMIES.slime;
    this.enemy = { ...def, curHp: def.hp };
    this.origin = data?.from === "Dungeon" ? "Dungeon" : "World";
    if (!GameState.seenMonsters.includes(def.name)) GameState.seenMonsters.push(def.name);
  }

  create(): void {
    Sfx.playBgm(BATTLE_THEME);
    this.menuTexts = [];
    this.itemTexts = [];
    this.inItems = false;
    this.itemIndex = 0;
    this.waitingAction = null;

    const unsubSaved = onSaved(() => showToast(this, "SAVED"));
    this.events.once(Phaser.Scenes.Events.SHUTDOWN, unsubSaved);

    this.add.image(GAME_WIDTH / 2, GAME_HEIGHT / 2, "battle-bg");

    this.enemySprite = this.add
      .sprite(GAME_WIDTH - 160, 140, this.enemy.texture)
      .setScale(this.enemy.boss || this.enemy.giant ? 3 : 2);
    this.playerSprite = this.add.sprite(160, 184, "hero-down-0").setScale(2);
    this.playerSprite.setFlipX(true);
    this.weaponOverlay = this.add
      .sprite(174, 184, GameState.equipped.weapon === "ironSword" ? "equip-iron-sword" : "equip-sword")
      .setScale(2);
    this.shieldOverlay = this.add
      .sprite(146, 184, GameState.equipped.armor === "ironShield" ? "equip-iron-shield" : "equip-shield")
      .setScale(2);
    this.weaponOverlay.setVisible(!!GameState.equipped.weapon);
    this.shieldOverlay.setVisible(!!GameState.equipped.armor);

    this.window(16, 12, 232, 88);
    this.window(GAME_WIDTH - 248, 12, 232, 88);

    this.add
      .text(32, 20, GameState.player.name, retroStyle(7, "#ffd166"))
      .setOrigin(0, 0);
    this.playerHpText = this.add
      .text(32, 44, "HP " + GameState.player.hp + "/" + GameState.effMaxHp(), retroStyle(6, "#ffffff"))
      .setOrigin(0, 0);
    this.playerMpText = this.add
      .text(32, 68, "MP " + GameState.player.mp + "/" + GameState.player.maxMp, retroStyle(6, "#8ecbff"))
      .setOrigin(0, 0);

    this.playerHpBar = this.add.rectangle(32, 62, 88, 8, 0x22c55e).setOrigin(0, 0.5);

    this.add
      .text(GAME_WIDTH - 232, 20, this.enemy.name, retroStyle(7, "#ff5555"))
      .setOrigin(0, 0);
    this.enemyHpText = this.add
      .text(GAME_WIDTH - 232, 44, "HP " + this.enemy.curHp + "/" + this.enemy.hp, retroStyle(6, "#ffffff"))
      .setOrigin(0, 0);
    this.enemyHpBar = this.add
      .rectangle(GAME_WIDTH - 232, 62, 88, 8, 0xef4444)
      .setOrigin(0, 0.5);

    this.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT - 30, GAME_WIDTH - 32, 56, 0x0b0b2b, 0.92)
      .setStrokeStyle(1, 0xffffff);
    this.msgText = this.add
      .text(32, GAME_HEIGHT - 52, "", retroStyle(8, "#f5f5f5"))
      .setWordWrapWidth(GAME_WIDTH - 64);

    const menuY = GAME_HEIGHT - 92;
    const labels: Record<string, string> = {
      fight: "A:FIGHT",
      magic: "F:MAGIC",
      item: "I:ITEM",
      run: "ESC:RUN",
    };
    let x = 64;
    for (const item of this.menuItems) {
      const t = this.add
        .text(x, menuY, labels[item], retroStyle(8, "#ffffff"))
        .setOrigin(0.5);
      this.menuTexts.push(t);
      x += 128;
    }
    this.hideMenu();

    this.hintText = this.add
      .text(GAME_WIDTH / 2, GAME_HEIGHT - 72, "", retroStyle(4, "#9f9fd0"))
      .setOrigin(0.5)
      .setDepth(30);

    const itemY = GAME_HEIGHT - 116;
    for (let i = 0; i < ITEM_SLOTS.length; i++) {
      const slot = ITEM_SLOTS[i];
      const colX = ITEM_COL_X + (i % ITEMS_PER_ROW) * ITEM_COL_WIDTH;
      const t = this.add
        .text(
          colX + ITEM_TEXT_OFFSET,
          itemY + Math.floor(i / ITEMS_PER_ROW) * 20,
          `${slot.label} x${GameState.inventory[slot.key]}`,
          retroStyle(6, "#ffffff")
        )
        .setOrigin(0, 0.5)
        .setVisible(false);
      this.itemTexts.push(t);
    }
    this.itemCursor = this.add
      .text(0, itemY, ">", retroStyle(6, "#ffd166"))
      .setOrigin(0, 0.5)
      .setVisible(false);

    this.hitBurst = this.add.particles(0, 0, "spark", {
      speed: { min: 40, max: 120 },
      lifespan: 300,
      scale: { start: 1, end: 0 },
      alpha: { start: 1, end: 0 },
      emitting: false,
    });
    this.glowBurst = this.add.particles(0, 0, "glow", {
      speed: { min: 60, max: 160 },
      lifespan: 400,
      scale: { start: 1, end: 0 },
      alpha: { start: 1, end: 0 },
      emitting: false,
    });
    this.healBurst = this.add.particles(0, 0, "glow", {
      speed: { min: 40, max: 100 },
      lifespan: 500,
      scale: { start: 1, end: 0 },
      alpha: { start: 1, end: 0 },
      tint: 0x4ade80,
      emitting: false,
    });
    this.levelBurst = this.add.particles(0, 0, "spark", {
      speed: 200,
      lifespan: 500,
      scale: { start: 1, end: 0 },
      alpha: { start: 1, end: 0 },
      emitting: false,
    });
    this.coinBurst = this.add.particles(0, 0, "coin", {
      speed: { min: 60, max: 140 },
      lifespan: 600,
      scale: { start: 1, end: 0 },
      alpha: { start: 1, end: 0 },
      emitting: false,
    });

    this.input.keyboard!.on("keydown", this.onKey, this);
    this.input.keyboard!.on("keydown-M", () => {
      const muted = Sfx.toggleMuted();
      showToast(this, muted ? "SOUND: OFF" : "SOUND: ON");
    });

    this.running = true;
    this.runBattle();
  }

  // keydown events, not JustDown polling: Key.onUp resets _justDown, so a
  // press whose down/up land in the same frame queue is silently dropped
  private onKey(e: KeyboardEvent): void {
    if (e.repeat || !this.waitingAction) return;

    if (this.inItems) {
      if (e.code === "ArrowLeft" || e.code === "KeyH") {
        this.itemIndex = (this.itemIndex + ITEM_SLOTS.length - 1) % ITEM_SLOTS.length;
        Sfx.move();
        this.renderItems();
        return;
      }
      if (e.code === "ArrowRight" || e.code === "KeyL") {
        this.itemIndex = (this.itemIndex + 1) % ITEM_SLOTS.length;
        Sfx.move();
        this.renderItems();
        return;
      }
      if (e.code === "Escape") {
        this.inItems = false;
        this.hideItems();
        this.renderMenu();
        return;
      }
      if (e.code === "KeyZ") {
        const slot = ITEM_SLOTS[this.itemIndex];
        if (GameState.inventory[slot.key] <= 0) {
          Sfx.error();
          return;
        }
        this.inItems = false;
        this.hideItems();
        this.resolveAction(slot.action);
      }
      return;
    }

    if (e.code === "Escape") {
      this.resolveAction("run");
      return;
    }
    if (e.code === "KeyA") {
      this.resolveAction("fight");
      return;
    }
    if (e.code === "KeyF") {
      this.resolveAction("magic");
      return;
    }
    if (e.code === "KeyI") {
      this.hideMenu();
      this.renderItems();
      this.inItems = true;
    }
  }

  private resolveAction(action: MenuAction): void {
    const waiter = this.waitingAction!;
    this.waitingAction = null;
    this.hideMenu();
    waiter.resolve(action);
  }

  private window(x: number, y: number, w: number, h: number): void {
    this.add
      .rectangle(x, y, w, h, 0x0b0b2b, 0.85)
      .setOrigin(0, 0)
      .setStrokeStyle(1, 0xffffff);
  }

  private hideMenu(): void {
    for (const t of this.menuTexts) t.setVisible(false);
  }

  private renderMenu(): void {
    for (const t of this.menuTexts) t.setVisible(true);
    this.hintText.setText(""); // the menu buttons above already show the hotkeys
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
    this.itemCursor.setX(target.x - ITEM_TEXT_OFFSET);
    this.itemCursor.setY(target.y);
    this.hintText.setText("H/L:NAV  Z:OK  ESC:BACK");
  }

  private async runBattle(): Promise<void> {
    if (this.enemy.boss || this.enemy.giant) Sfx.boss();
    await this.say(`${this.enemy.name} blocks your way!`);

    while (this.running) {
      if (GameState.player.hp <= 0) return this.defeat();

      let action = await this.playerTurn();
      while (action === "magic" && GameState.player.mp < MP_COST) {
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
        case "hiPotion":
          await this.useHiPotion();
          break;
        case "ether":
          await this.useEther();
          break;
        case "elixir":
          await this.useElixir();
          break;
        case "bomb":
          await this.throwBomb();
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
    const { dmg, crit } = this.calcDamage(GameState.effAtk(), this.enemy.def);
    if (crit) Sfx.critical();
    this.enemy.curHp = Math.max(0, this.enemy.curHp - dmg);
    this.enemySprite.setTintFill(0xffffff);
    this.hitBurst.setPosition(this.enemySprite.x, this.enemySprite.y);
    this.hitBurst.explode(crit ? 16 : 8);
    this.cameras.main.shake(crit ? 120 : 60, crit ? 0.012 : 0.004);
    this.flashDamage(this.enemySprite.x, this.enemySprite.y, dmg, crit);
    await this.say(crit ? `CRITICAL HIT! You strike for ${dmg}!` : `You strike for ${dmg}!`);
    this.enemySprite.clearTint();
    this.updateEnemyHp();
  }

  private async playerMagic(): Promise<void> {
    Sfx.magic();
    GameState.player.mp -= MP_COST;
    this.updatePlayerStats();
    const dmg = 10 + Math.floor(Math.random() * 5);
    await this.fireball();
    this.enemy.curHp = Math.max(0, this.enemy.curHp - dmg);
    this.enemySprite.setTintFill(0xffa500);
    this.flashDamage(this.enemySprite.x, this.enemySprite.y, dmg);
    await this.say(`FIRE! ${dmg} damage!`);
    this.enemySprite.clearTint();
    this.updateEnemyHp();
  }

  private async usePotion(): Promise<void> {
    if (GameState.player.hp >= GameState.effMaxHp()) {
      Sfx.error();
      await this.say("HP is already full!");
      return;
    }
    Sfx.buy();
    GameState.inventory.potion -= 1;
    const healed = Math.min(GameState.effMaxHp() - GameState.player.hp, 25);
    GameState.player.hp += healed;
    this.updatePlayerStats();
    this.healBurst.setPosition(this.playerSprite.x, this.playerSprite.y);
    this.healBurst.explode(10);
    this.flashHeal(this.playerSprite.x, this.playerSprite.y, healed);
    await this.say(`Potion heals ${healed} HP!`);
  }

  private async useMPotion(): Promise<void> {
    if (GameState.player.mp >= GameState.player.maxMp) {
      Sfx.error();
      await this.say("MP is already full!");
      return;
    }
    Sfx.buy();
    GameState.inventory.mPotion -= 1;
    const restored = Math.min(GameState.player.maxMp - GameState.player.mp, 8);
    GameState.player.mp += restored;
    this.updatePlayerStats();
    await this.say(`Magic restores ${restored} MP!`);
  }

  private async useHiPotion(): Promise<void> {
    if (GameState.player.hp >= GameState.effMaxHp()) {
      Sfx.error();
      await this.say("HP is already full!");
      return;
    }
    Sfx.buy();
    GameState.inventory.hiPotion -= 1;
    const healed = Math.min(GameState.effMaxHp() - GameState.player.hp, 50);
    GameState.player.hp += healed;
    this.updatePlayerStats();
    this.healBurst.setPosition(this.playerSprite.x, this.playerSprite.y);
    this.healBurst.explode(10);
    this.flashHeal(this.playerSprite.x, this.playerSprite.y, healed);
    await this.say(`Hi-Potion heals ${healed} HP!`);
  }

  private async useEther(): Promise<void> {
    if (GameState.player.mp >= GameState.player.maxMp) {
      Sfx.error();
      await this.say("MP is already full!");
      return;
    }
    Sfx.buy();
    GameState.inventory.ether -= 1;
    const restored = Math.min(GameState.player.maxMp - GameState.player.mp, 12);
    GameState.player.mp += restored;
    this.updatePlayerStats();
    await this.say(`Ether restores ${restored} MP!`);
  }

  private async useElixir(): Promise<void> {
    if (
      GameState.player.hp >= GameState.effMaxHp() &&
      GameState.player.mp >= GameState.player.maxMp
    ) {
      Sfx.error();
      await this.say("HP and MP are already full!");
      return;
    }
    Sfx.buy();
    GameState.inventory.elixir -= 1;
    const hpBefore = GameState.player.hp;
    GameState.player.hp = GameState.effMaxHp();
    GameState.player.mp = GameState.player.maxMp;
    this.updatePlayerStats();
    this.healBurst.setPosition(this.playerSprite.x, this.playerSprite.y);
    this.healBurst.explode(12);
    const healed = GameState.effMaxHp() - hpBefore;
    if (healed > 0) this.flashHeal(this.playerSprite.x, this.playerSprite.y, healed);
    await this.say("Elixir fully restores HP and MP!");
  }

  private async throwBomb(): Promise<void> {
    Sfx.hit();
    GameState.inventory.bomb -= 1;
    const dmg = 12;
    this.enemy.curHp = Math.max(0, this.enemy.curHp - dmg);
    this.enemySprite.setTintFill(0xffa500);
    this.flashDamage(this.enemySprite.x, this.enemySprite.y, dmg);
    await this.say(`BOOM! ${dmg} damage!`);
    this.enemySprite.clearTint();
    this.updateEnemyHp();
  }

  private async throwCandy(): Promise<void> {
    if (this.enemy.boss) {
      Sfx.error();
      await this.say("The KING SLIME is too strong!");
      return;
    }
    Sfx.capture();
    GameState.inventory.candy -= 1;
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
    await this.enemyLunge();
    const { dmg, crit } = this.calcDamage(this.enemy.atk, GameState.effDef());
    if (crit) Sfx.critical();
    GameState.player.hp = Math.max(0, GameState.player.hp - dmg);
    this.playerSprite.setTintFill(0xff6666);
    this.hitBurst.setPosition(this.playerSprite.x, this.playerSprite.y);
    this.hitBurst.explode(8);
    this.cameras.main.shake(80, 0.006);
    this.flashDamage(this.playerSprite.x, this.playerSprite.y, dmg, crit);
    await this.say(crit ? `CRITICAL! ${this.enemy.name} strikes for ${dmg}!` : `${this.enemy.name} attacks for ${dmg}!`);
    this.playerSprite.clearTint();
    this.updatePlayerStats();
  }

  private async enemyLunge(): Promise<void> {
    const startX = this.enemySprite.x;
    const targetX = this.playerSprite.x + 40;
    await this.tweenPromise(this.enemySprite, { x: targetX }, 140);
    await this.tweenPromise(this.enemySprite, { x: startX }, 160);
  }

  private async lunge(): Promise<void> {
    const startX = this.playerSprite.x;
    const targetX = this.enemySprite.x - 40;
    const hasWeapon = !!GameState.equipped.weapon;
    const syncOverlays = () => {
      this.weaponOverlay.x = this.playerSprite.x + 14;
      this.shieldOverlay.x = this.playerSprite.x - 14;
    };
    this.playerSprite.x = startX;
    syncOverlays();
    if (hasWeapon) {
      // wind-up, then swing down through the lunge
      this.weaponOverlay.setAngle(-20);
      this.tweens.add({ targets: this.weaponOverlay, angle: 60, duration: 140, ease: "Sine.easeIn" });
    }
    await this.tweenPromise(this.playerSprite, { x: targetX }, 140, syncOverlays);
    syncOverlays();
    if (hasWeapon) {
      this.tweens.add({ targets: this.weaponOverlay, angle: 0, duration: 160, ease: "Sine.easeOut" });
    }
    await this.tweenPromise(this.playerSprite, { x: startX }, 160, syncOverlays);
    syncOverlays();
  }

  private async fireball(): Promise<void> {
    const fb = this.add
      .circle(this.playerSprite.x + 20, this.playerSprite.y - 10, 8, 0xffa500)
      .setDepth(20);
    this.tweens.add({
      targets: fb,
      alpha: { from: 1, to: 0.5 },
      duration: 90,
      repeat: -1,
      yoyo: true,
    });
    await this.tweenPromise(fb, { x: this.enemySprite.x, y: this.enemySprite.y }, 240);
    this.tweens.killTweensOf(fb); // the repeat:-1 pulse tween outlives destroy() otherwise
    fb.destroy();
    const boom = this.add
      .circle(this.enemySprite.x, this.enemySprite.y, 12, 0xff5500)
      .setDepth(20);
    this.glowBurst.setPosition(this.enemySprite.x, this.enemySprite.y);
    this.glowBurst.explode(12);
    this.cameras.main.shake(100, 0.008);
    this.tweens.add({
      targets: boom,
      scale: 3,
      alpha: 0,
      duration: 280,
      onComplete: () => boom.destroy(),
    });
  }

  private flashDamage(x: number, y: number, amount: number, crit = false): void {
    const t = this.add
      .text(x + 20, y - 40, crit ? `${amount}!` : String(amount), retroStyle(crit ? 14 : 10, crit ? "#ff5555" : "#ffdd44"))
      .setOrigin(0.5)
      .setStroke("#7c2d12", 2);
    this.tweens.add({
      targets: t,
      y: y - (crit ? 100 : 80),
      alpha: 0,
      duration: 800,
      onComplete: () => t.destroy(),
    });
  }

  private flashHeal(x: number, y: number, amount: number): void {
    const t = this.add
      .text(x + 20, y - 40, `+${amount}`, retroStyle(10, "#4ade80"))
      .setOrigin(0.5)
      .setStroke("#14532d", 2);
    this.tweens.add({
      targets: t,
      y: y - 80,
      alpha: 0,
      duration: 800,
      onComplete: () => t.destroy(),
    });
  }

  private calcDamage(atk: number, def: number): { dmg: number; crit: boolean } {
    const crit = Math.random() < CRIT_CHANCE;
    // clamp to the 1-damage floor before applying the crit multiplier, so a
    // crit against heavy defense still doubles instead of also flooring to 1
    const hit = Math.max(1, Math.floor(atk * (0.8 + Math.random() * 0.4)) - def);
    return { dmg: crit ? hit * CRIT_MULT : hit, crit };
  }

  private updateEnemyHp(): void {
    this.enemyHpText.setText(`HP ${this.enemy.curHp}/${this.enemy.hp}`);
    this.enemyHpBar.setScale(Math.max(0, this.enemy.curHp / this.enemy.hp), 1);
  }

  private updatePlayerStats(): void {
    this.playerHpText.setText(`HP ${GameState.player.hp}/${GameState.effMaxHp()}`);
    this.playerMpText.setText(`MP ${GameState.player.mp}/${GameState.player.maxMp}`);
    this.playerHpBar.setScale(Math.max(0, GameState.player.hp / GameState.effMaxHp()), 1);
  }

  private async victory(caught = false): Promise<void> {
    this.running = false;
    if (!caught) {
      GameState.gold += this.enemy.gold;
      GameState.battles += 1;
      if (this.enemy.name === "SLIME") GameState.quest.slimes += 1;
      if (this.enemy.boss) GameState.quest.bossDefeated = true;
      GameState.player.hp = Math.min(GameState.effMaxHp(), GameState.player.hp + 5);
      GameState.player.mp = Math.min(GameState.player.maxMp, GameState.player.mp + 2);
      Sfx.victory();
      this.tweenPromise(this.enemySprite, { scale: this.enemySprite.scale * 1.15, alpha: 0 }, 350);
      await this.say(`${this.enemy.name} is defeated!`);
      await this.say(`Gained ${this.enemy.gold} gold!`);
      if (this.enemy.boss) {
        GameState.inventory.hiPotion += 1;
        Sfx.pickup();
        await this.say("Found a HI-POTION!");
      } else {
        const roll = Math.random();
        if (roll < 0.3) {
          GameState.inventory.potion += 1;
          Sfx.pickup();
          await this.say("Found a POTION!");
        } else if (roll < 0.45) {
          GameState.inventory.candy += 1;
          Sfx.pickup();
          await this.say("Found some CANDY!");
        } else if (roll < 0.55) {
          GameState.inventory.mPotion += 1;
          Sfx.pickup();
          await this.say("Found an MPOTION!");
        } else if (roll < 0.63) {
          GameState.inventory.hiPotion += 1;
          Sfx.pickup();
          await this.say("Found a HI-POTION!");
        }
      }
      GameState.player.exp += this.enemy.exp;
      let msg = `EXP +${this.enemy.exp}`;
      while (GameState.player.exp >= expToNext(GameState.player.level)) {
        GameState.player.exp -= expToNext(GameState.player.level);
        GameState.player.level += 1;
        GameState.player.maxHp += 5;
        GameState.player.maxMp += 2;
        GameState.player.atk += 1;
        GameState.player.def += 1;
        GameState.player.hp = GameState.effMaxHp();
        GameState.player.mp = GameState.player.maxMp;
        Sfx.levelup();
        this.levelBurst.setPosition(this.playerSprite.x, this.playerSprite.y);
        this.levelBurst.explode(24);
        this.coinBurst.setPosition(this.playerSprite.x, this.playerSprite.y);
        this.coinBurst.explode(12);
        this.cameras.main.shake(200, 0.01);
        msg = `LEVEL UP! LV ${GameState.player.level}`;
      }
      await this.say(msg);
      if (this.enemy.boss) await this.say("The KING SLIME is no more!");
    }
    GameState.lockEncounters(4000);
    GameState.save();
    this.coinBurst.setPosition(this.enemySprite.x, this.enemySprite.y);
    this.coinBurst.explode(10);
    await this.say("Battle won!");
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
      this.scene.start(this.origin === "Dungeon" ? "Dungeon" : "World");
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
    this.hintText.setText("Z/A/F/ESC:CONTINUE");
    const done = () => {
      this.input.keyboard?.removeListener("keydown-Z", done);
      this.input.keyboard?.removeListener("keydown-A", done);
      this.input.keyboard?.removeListener("keydown-F", done);
      this.input.keyboard?.removeListener("keydown-ESC", done);
      this.input.keyboard?.removeListener("keydown-SPACE", done);
      this.input.off("pointerdown", done);
      resolve();
    };
    this.input.keyboard?.once("keydown-Z", done);
    this.input.keyboard?.once("keydown-A", done);
    this.input.keyboard?.once("keydown-F", done);
    this.input.keyboard?.once("keydown-ESC", done);
    this.input.keyboard?.once("keydown-SPACE", done);
    this.input.once("pointerdown", done);
  }

  private tweenPromise(
    target: Phaser.GameObjects.GameObject,
    props: object,
    duration: number,
    onUpdate?: () => void
  ): Promise<void> {
    return new Promise((resolve) => {
      this.tweens.add({
        targets: target,
        ...props,
        duration,
        onUpdate,
        onComplete: () => resolve(),
      });
    });
  }
}
