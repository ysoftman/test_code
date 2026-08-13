import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { GameState, expToNext, isNight, timeLabel, clock, dayCount } from "../gameState";
import { retroStyle } from "../pixelart";
import { DialogueBox } from "../ui/DialogueBox";
import { ShopUI } from "../ui/Shop";
import { Sfx } from "../audio";
import {
  buildLevel,
  MAP_W,
  MAP_H,
  TILE,
  PLAYER_SPAWN,
  NPC_POS,
  SHOP_POS,
  HOUSE_POS,
  CAVE_POS,
  MONSTER_ZONES,
  SOLID,
  T_WATER_A,
  T_WATER_B,
  TALL_GRASS,
} from "../levels";

const ENCOUNTER_RATE = 0.18;
const ENCOUNTER_COOLDOWN = 600;

type LastMove = "down" | "up" | "right" | "left";

interface Roamer {
  sprite: Phaser.Physics.Arcade.Sprite;
  minX: number;
  maxX: number;
  minY: number;
  maxY: number;
  targetX: number;
  targetY: number;
  wait: number;
  speed: number;
}

const IDLE_TEXTURE: Record<LastMove, string> = {
  down: "hero-idle-down",
  up: "hero-idle-up",
  right: "hero-idle-right",
  left: "hero-idle-left",
};

export class WorldScene extends Phaser.Scene {
  private player!: Phaser.Physics.Arcade.Sprite;
  private playerShadow!: Phaser.GameObjects.Ellipse;
  private layer!: Phaser.Tilemaps.TilemapLayer;
  private dialogue!: DialogueBox;
  private shop!: ShopUI;
  private dust!: Phaser.GameObjects.Particles.ParticleEmitter;
  private roamerGroup!: Phaser.Physics.Arcade.Group;
  private roamers: Roamer[] = [];
  private encounterCooldown = 0;
  private lastMove: LastMove = "down";
  private nightOverlay!: Phaser.GameObjects.Rectangle;
  private moon!: Phaser.GameObjects.Image;
  private stars!: Phaser.GameObjects.Image;
  private homeLabel!: Phaser.GameObjects.Text;
  private homeBubble!: Phaser.GameObjects.Container;
  private bubbleVisible = false;
  private resting = false;
  private zQueued = false;
  private bQueued = false;

  private keyLeft!: Phaser.Input.Keyboard.Key;
  private keyRight!: Phaser.Input.Keyboard.Key;
  private keyUp!: Phaser.Input.Keyboard.Key;
  private keyDown!: Phaser.Input.Keyboard.Key;
  private keyH!: Phaser.Input.Keyboard.Key;
  private keyJ!: Phaser.Input.Keyboard.Key;
  private keyK!: Phaser.Input.Keyboard.Key;
  private keyL!: Phaser.Input.Keyboard.Key;
  private keyZ!: Phaser.Input.Keyboard.Key;
  private keySpace!: Phaser.Input.Keyboard.Key;
  private keyB!: Phaser.Input.Keyboard.Key;
  private keyS!: Phaser.Input.Keyboard.Key;

  private statusText!: Phaser.GameObjects.Text;
  private statusPanel!: Phaser.GameObjects.Rectangle;
  private expBar!: Phaser.GameObjects.Rectangle;
  private statusLast = "";

  constructor() {
    super("World");
  }

  create(): void {
    this.roamers = [];
    this.encounterCooldown = GameState.encountersLocked() ? ENCOUNTER_COOLDOWN : 0;
    this.lastMove = "down";
    this.resting = false;

    const level = buildLevel();
    const map = this.make.tilemap({
      data: level,
      tileWidth: TILE,
      tileHeight: TILE,
    });
    const tileset = map.addTilesetImage("tiles16", "tiles16", TILE, TILE);
    this.layer = map.createLayer(0, tileset!, 0, 0)!;
    this.layer.setCollision(Array.from(SOLID));

    this.physics.world.setBounds(0, 0, MAP_W * TILE, MAP_H * TILE);

    this.moon = this.add
      .image(140, 72, "moon")
      .setScrollFactor(0)
      .setDepth(-50)
      .setVisible(isNight());
    this.stars = this.add
      .image(GAME_WIDTH / 2, 72, "stars")
      .setScrollFactor(0)
      .setDepth(-50)
      .setVisible(isNight());

    this.add
      .image(HOUSE_POS.x + TILE, HOUSE_POS.y + TILE, "house")
      .setOrigin(0.5, 0.5);
    this.homeLabel = this.add
      .text(HOUSE_POS.x + TILE, HOUSE_POS.y + TILE - 52, "HOME", retroStyle(5, "#9f9fd0"))
      .setOrigin(0.5)
      .setDepth(11);
    this.homeBubble = this.buildHomeBubble();
    this.homeBubble.setVisible(false);

    this.add
      .sprite(NPC_POS.x, NPC_POS.y, "npc").setDepth(10);
    this.add
      .ellipse(NPC_POS.x, NPC_POS.y + 14, 20, 8, 0x000000, 0.4)
      .setDepth(5);
    this.add
      .text(NPC_POS.x, NPC_POS.y - 34, "ELDER", retroStyle(5, "#9f9fd0"))
      .setOrigin(0.5)
      .setDepth(11);

    this.add.sprite(SHOP_POS.x, SHOP_POS.y, "npc").setDepth(10).setTint(0xffd166);
    this.add
      .ellipse(SHOP_POS.x, SHOP_POS.y + 14, 20, 8, 0x000000, 0.4)
      .setDepth(5);
    this.add
      .text(SHOP_POS.x, SHOP_POS.y - 34, "SHOP", retroStyle(5, "#ffd166"))
      .setOrigin(0.5)
      .setDepth(11);

    this.add.image(CAVE_POS.x, CAVE_POS.y, "cave").setDepth(9);
    this.add
      .text(CAVE_POS.x, CAVE_POS.y + 16, "CAVE", retroStyle(6, "#9f9fd0"))
      .setOrigin(0.5)
      .setDepth(11);

    this.player = this.physics.add.sprite(
      GameState.pos?.x ?? PLAYER_SPAWN.x,
      GameState.pos?.y ?? PLAYER_SPAWN.y,
      "hero-idle-down"
    );
    this.player.setCollideWorldBounds(true);
    this.player.setDepth(10);
    this.player.body?.setSize(20, 16).setOffset(6, 16);
    this.physics.add.collider(this.player, this.layer);

    this.playerShadow = this.add
      .ellipse(this.player.x, this.player.y + 14, 20, 8, 0x000000, 0.4)
      .setDepth(5);

    const walkFrames = (dir: string): Phaser.Types.Animations.AnimationFrame[] =>
      [0, 1, 2, 3].map((i) => ({ key: `hero-${dir}-${i}` }));

    this.anims.create({
      key: "walk-down",
      frames: walkFrames("down"),
      frameRate: 10,
      repeat: -1,
    });
    this.anims.create({
      key: "walk-up",
      frames: walkFrames("up"),
      frameRate: 10,
      repeat: -1,
    });
    this.anims.create({
      key: "walk-right",
      frames: walkFrames("right"),
      frameRate: 10,
      repeat: -1,
    });
    this.anims.create({
      key: "walk-left",
      frames: walkFrames("left"),
      frameRate: 10,
      repeat: -1,
    });

    this.dust = this.add.particles(0, 0, "dust", {
      speed: { min: 8, max: 22 },
      lifespan: { min: 180, max: 320 },
      scale: { start: 1, end: 0 },
      alpha: { start: 0.45, end: 0 },
      frequency: 70,
      emitting: false,
    });
    this.dust.startFollow(this.player, 0, 14);

    this.spawnMonsters();

    this.physics.add.overlap(this.player, this.roamerGroup, () => {
      if (this.encounterCooldown <= 0) this.startBattle("slime");
    });

    const cave = this.add.zone(CAVE_POS.x, CAVE_POS.y, TILE, TILE).setDepth(1);
    this.physics.add.existing(cave);
    this.physics.add.overlap(this.player, cave, () => {
      this.enterDungeon();
    });

    this.time.addEvent({
      delay: 400,
      loop: true,
      callback: () => this.animateWater(),
    });

    this.cameras.main.startFollow(this.player, true, 0.08, 0.08);
    this.cameras.main.setBounds(0, 0, MAP_W * TILE, MAP_H * TILE);

    const kb = this.input.keyboard!;
    this.keyLeft = kb.addKey(Phaser.Input.Keyboard.KeyCodes.LEFT);
    this.keyRight = kb.addKey(Phaser.Input.Keyboard.KeyCodes.RIGHT);
    this.keyUp = kb.addKey(Phaser.Input.Keyboard.KeyCodes.UP);
    this.keyDown = kb.addKey(Phaser.Input.Keyboard.KeyCodes.DOWN);
    this.keyH = kb.addKey(Phaser.Input.Keyboard.KeyCodes.H);
    this.keyJ = kb.addKey(Phaser.Input.Keyboard.KeyCodes.J);
    this.keyK = kb.addKey(Phaser.Input.Keyboard.KeyCodes.K);
    this.keyL = kb.addKey(Phaser.Input.Keyboard.KeyCodes.L);
    this.keyZ = kb.addKey(Phaser.Input.Keyboard.KeyCodes.Z);
    this.keyZ.on(Phaser.Input.Keyboard.Events.DOWN, () => {
      this.zQueued = true;
    });
    this.keySpace = kb.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);
    this.keySpace.on(Phaser.Input.Keyboard.Events.DOWN, () => {
      this.zQueued = true;
    });
    this.keyB = kb.addKey(Phaser.Input.Keyboard.KeyCodes.B);
    this.keyB.on(Phaser.Input.Keyboard.Events.DOWN, () => {
      this.bQueued = true;
    });
    this.keyS = kb.addKey(Phaser.Input.Keyboard.KeyCodes.S);

    this.dialogue = new DialogueBox(this, []);
    this.shop = new ShopUI(this);

    const hint = this.add
      .text(
        GAME_WIDTH - 8,
        GAME_HEIGHT - 6,
        "HJKL:MOVE  Z:TALK/REST  S:HUD  ESC:SKIP",
        retroStyle(6, "#9f9fd0")
      )
      .setOrigin(1, 1)
      .setScrollFactor(0)
      .setDepth(100);

    this.nightOverlay = this.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH, GAME_HEIGHT, 0x1a1a4a, 0)
      .setScrollFactor(0)
      .setDepth(90);

    const statusDummy = [
      "HERO",
      "LV 1",
      "HP 30/30",
      "MP 10/10",
      "G 0",
      "DAY 1",
      "00:00 DAY",
      "SLIMES 0/5",
    ].join("\n");
    this.statusText = this.add
      .text(16, 0, statusDummy, retroStyle(6, "#ffffff"))
      .setOrigin(0, 0)
      .setScrollFactor(0)
      .setDepth(101);
    const statusH = this.statusText.height + 24;
    this.statusText.setY(GAME_HEIGHT - 8 - statusH + 12);
    this.statusPanel = this.add
      .rectangle(8, GAME_HEIGHT - 8, 180, statusH, 0x0b0b2b, 0.88)
      .setOrigin(0, 1)
      .setStrokeStyle(1, 0xffffff)
      .setScrollFactor(0)
      .setDepth(100);
    this.expBar = this.add
      .rectangle(16, GAME_HEIGHT - 10, 164, 4, 0x22c55e)
      .setOrigin(0, 0.5)
      .setScrollFactor(0)
      .setDepth(101);

    this.events.once(Phaser.Scenes.Events.SHUTDOWN, () => {
      GameState.pos = { x: this.player.x, y: this.player.y };
      GameState.save();
      this.dialogue.destroy();
      this.shop.destroy();
      hint.destroy();
    });
  }

  private buildHomeBubble(): Phaser.GameObjects.Container {
    const lines = ["HOME", "Z: REST - FULL HP/MP", "SLEEP UNTIL MORNING"];
    const text = this.add
      .text(0, 0, lines.join("\n"), retroStyle(5, "#f5f5f5"))
      .setOrigin(0.5)
      .setAlign("center")
      .setLineSpacing(4);
    const pad = 10;
    const w = text.width + pad * 2;
    const h = text.height + pad * 2;
    const border = this.add.rectangle(0, 0, w + 4, h + 4, 0xffffff).setOrigin(0.5);
    const box = this.add.rectangle(0, 0, w, h, 0x0b0b2b).setOrigin(0.5);
    const tail = this.add
      .triangle(0, h / 2 + 2, -12, 0, 12, 0, 0, 14, 0x0b0b2b)
      .setStrokeStyle(2, 0xffffff)
      .setOrigin(0.5);
    return this.add
      .container(
        HOUSE_POS.x + TILE,
        HOUSE_POS.y + TILE - h / 2 - 16,
        [border, box, text, tail]
      )
      .setDepth(12);
  }

  private nearHouse(): boolean {
    const dx = this.player.x - (HOUSE_POS.x + TILE);
    const dy = this.player.y - (HOUSE_POS.y + 2 * TILE);
    return dx * dx + dy * dy <= 72 * 72;
  }

  private updateHomeBubble(): void {
    const near = this.nearHouse();
    if (near === this.bubbleVisible) return;
    this.bubbleVisible = near;
    this.homeBubble.setVisible(near);
    this.homeLabel.setVisible(!near);
    if (near) {
      this.tweens.killTweensOf(this.homeBubble);
      this.homeBubble.setAlpha(0);
      this.tweens.add({
        targets: this.homeBubble,
        alpha: 1,
        duration: 160,
      });
    }
  }

  private enterDungeon(): void {
    if (this.dialogue.isActive() || this.shop.isActive()) return;
    Sfx.night();
    this.player.setVelocity(0, 0);
    this.cameras.main.fadeOut(200, 0, 0, 0);
    this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
      this.scene.start("Dungeon");
    });
  }

  update(_time: number, delta: number): void {
    GameState.minutes += delta / 1000;
    this.updateStatus();
    this.updateDayNight();
    this.updateHomeBubble();

    if (Phaser.Input.Keyboard.JustDown(this.keyS)) {
      this.toggleStatus();
    }

    if (this.dialogue.isActive() || this.shop.isActive()) {
      this.zQueued = false;
      this.bQueued = false;
      this.player.setVelocity(0, 0);
      this.player.anims.stop();
      this.dust.emitting = false;
      this.dialogue.update();
      this.shop.update();
      this.updateRoamers(delta);
      return;
    }

    if (this.zQueued) {
      this.zQueued = false;
      if (this.tryTalk()) return;
    }
    if (this.bQueued) {
      this.bQueued = false;
      this.startBattle();
      return;
    }

    let vx = 0;
    let vy = 0;
    if (this.keyLeft.isDown || this.keyH.isDown) vx = -120;
    else if (this.keyRight.isDown || this.keyL.isDown) vx = 120;
    if (this.keyUp.isDown || this.keyK.isDown) vy = -120;
    else if (this.keyDown.isDown || this.keyJ.isDown) vy = 120;

    this.player.setVelocity(vx, vy);

    const moving = vx !== 0 || vy !== 0;
    if (moving) {
      if (Math.abs(vx) > Math.abs(vy)) {
        this.lastMove = vx < 0 ? "left" : "right";
        this.player.anims.play(this.lastMove === "left" ? "walk-left" : "walk-right", true);
      } else {
        this.lastMove = vy < 0 ? "up" : "down";
        this.player.anims.play(this.lastMove === "up" ? "walk-up" : "walk-down", true);
      }
    } else {
      this.player.setVelocity(0, 0);
      this.player.anims.stop();
      this.player.setTexture(IDLE_TEXTURE[this.lastMove]);
    }

    this.playerShadow.setPosition(this.player.x, this.player.y + 14);
    this.dust.emitting = moving;
    this.updateRoamers(delta);
    this.checkEncounter(delta);
  }

  private toggleStatus(): void {
    const visible = !this.statusPanel.visible;
    this.statusPanel.setVisible(visible);
    this.statusText.setVisible(visible);
    this.expBar.setVisible(visible);
  }

  private updateDayNight(): void {
    this.nightOverlay.setAlpha(isNight() ? 0.32 : 0);
    const night = isNight();
    this.moon.setVisible(night);
    this.stars.setVisible(night);
  }

  private updateStatus(): void {
    const p = GameState.player;
    const q = GameState.quest;
    const questLine = q.bossDefeated
      ? "QUEST DONE"
      : `SLIMES ${q.slimes}/5`;
    const text = [
      p.name,
      `LV ${p.level}`,
      `HP ${p.hp}/${p.maxHp}`,
      `MP ${p.mp}/${p.maxMp}`,
      `G ${GameState.gold}`,
      `DAY ${dayCount()}`,
      `${clock()} ${timeLabel()}`,
      questLine,
    ].join("\n");
    if (text !== this.statusLast) {
      this.statusLast = text;
      this.statusText.setText(text);
    }
    this.expBar.setScale(
      Math.max(0, p.exp / expToNext(p.level)),
      1
    );
  }

  private tryTalk(): boolean {
    const near = (x: number, y: number): boolean => {
      const dx = this.player.x - x;
      const dy = this.player.y - y;
      return dx * dx + dy * dy <= 60 * 60;
    };

    if (near(NPC_POS.x, NPC_POS.y)) {
      this.startElderDialogue();
      return true;
    }
    if (near(SHOP_POS.x, SHOP_POS.y)) {
      Sfx.buy();
      this.shop.open();
      return true;
    }
    if (near(HOUSE_POS.x + TILE, HOUSE_POS.y + 2 * TILE)) {
      this.rest();
      return true;
    }
    return false;
  }

  private rest(): void {
    if (this.resting) return;
    this.resting = true;
    this.player.setVelocity(0, 0);
    Sfx.night();
    this.cameras.main.fadeOut(400, 0, 0, 0);
    this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
      GameState.player.hp = GameState.player.maxHp;
      GameState.player.mp = GameState.player.maxMp;
      GameState.minutes = (Math.floor(GameState.minutes / 1440) + 1) * 1440 + 360;
      GameState.save();
      this.statusLast = "";
      this.cameras.main.fadeIn(400, 0, 0, 0);
      this.resting = false;
      const note = this.add
        .text(GAME_WIDTH / 2, GAME_HEIGHT / 2, "RESTED! HP/MP FULL", retroStyle(8, "#ffd166"))
        .setOrigin(0.5)
        .setScrollFactor(0)
        .setDepth(120);
      this.tweens.add({
        targets: note,
        y: GAME_HEIGHT / 2 - 30,
        alpha: 0,
        delay: 800,
        duration: 600,
        onComplete: () => note.destroy(),
      });
    });
  }

  private startElderDialogue(): void {
    const q = GameState.quest;
    if (!q.slimeReward && q.slimes >= 5) {
      q.slimeReward = true;
      GameState.gold += 30;
      Sfx.buy();
      this.dialogue.start(
        [
          "Well done, hero!",
          "You hunted 5 slimes.",
          "Take these 30 gold!",
        ],
        "ELDER"
      );
      return;
    }
    if (!q.bossDefeated) {
      this.dialogue.start(
        [
          "Welcome back!",
          "Slimes lurk in the grass.",
          "Hunt 5 slimes first.",
          "Then face the KING SLIME",
          "in the cave up north!",
        ],
        "ELDER"
      );
      return;
    }
    if (!q.finalReward) {
      q.finalReward = true;
      GameState.gold += 100;
      Sfx.buy();
      this.dialogue.start(
        [
          "You are our hero!",
          "The KING SLIME is gone.",
          "Take this 100 gold!",
        ],
        "ELDER"
      );
      return;
    }
    this.dialogue.start(["The village is at peace."], "ELDER");
  }

  private checkEncounter(delta: number): void {
    if (this.encounterCooldown > 0) {
      this.encounterCooldown -= delta;
      return;
    }
    const tile = this.layer.getTileAtWorldXY(this.player.x, this.player.y);
    if (!tile || tile.index !== TALL_GRASS) return;
    const rate = ENCOUNTER_RATE * (isNight() ? 1.8 : 1) * (delta / 1000);
    if (Math.random() < rate) {
      this.startBattle();
    }
  }

  private spawnMonsters(): void {
    this.roamerGroup = this.physics.add.group();
    for (const zone of MONSTER_ZONES) {
      const signX = zone.cx - zone.w / 2 - 16;
      this.add.image(signX, zone.cy, "sign").setDepth(9);
      const bang = this.add
        .text(signX, zone.cy - 32, "!", retroStyle(10, "#ffdd44"))
        .setOrigin(0.5)
        .setStroke("#7c2d12", 2)
        .setDepth(11);
      this.tweens.add({
        targets: bang,
        y: zone.cy - 42,
        duration: 420,
        yoyo: true,
        repeat: -1,
        ease: "Sine.easeInOut",
      });

      for (let i = 0; i < zone.count; i++) {
        const x = zone.cx + (Math.random() - 0.5) * zone.w * 0.6;
        const y = zone.cy + (Math.random() - 0.5) * zone.h * 0.6;
        const sprite = this.roamerGroup.create(
          x,
          y,
          "slime"
        ) as Phaser.Physics.Arcade.Sprite;
        sprite.setDepth(10);
        sprite.body?.setSize(20, 12).setOffset(6, 16);
        this.roamers.push({
          sprite,
          minX: zone.cx - zone.w / 2 + 4,
          maxX: zone.cx + zone.w / 2 - 4,
          minY: zone.cy - zone.h / 2 + 4,
          maxY: zone.cy + zone.h / 2 - 4,
          targetX: x,
          targetY: y,
          wait: 300 + Math.random() * 800,
          speed: 28 + Math.random() * 20,
        });
        this.tweens.add({
          targets: sprite,
          scaleX: 1.12,
          scaleY: 0.88,
          duration: 280,
          yoyo: true,
          repeat: -1,
          ease: "Sine.easeInOut",
        });
      }
    }
  }

  private updateRoamers(delta: number): void {
    for (const r of this.roamers) {
      const s = r.sprite;
      if (r.wait > 0) {
        r.wait -= delta;
        if (r.wait <= 0) this.pickRoamerTarget(r);
        continue;
      }
      const dx = r.targetX - s.x;
      const dy = r.targetY - s.y;
      const dist = Math.hypot(dx, dy);
      if (dist < 4) {
        s.setVelocity(0, 0);
        r.wait = 500 + Math.random() * 900;
      } else {
        s.setVelocity((dx / dist) * r.speed, (dy / dist) * r.speed);
      }
      s.x = Phaser.Math.Clamp(s.x, r.minX, r.maxX);
      s.y = Phaser.Math.Clamp(s.y, r.minY, r.maxY);
    }
  }

  private pickRoamerTarget(r: Roamer): void {
    r.targetX = r.minX + Math.random() * (r.maxX - r.minX);
    r.targetY = r.minY + Math.random() * (r.maxY - r.minY);
  }

  private startBattle(enemy?: "slime" | "goblin"): void {
    this.player.setVelocity(0, 0);
    this.encounterCooldown = ENCOUNTER_COOLDOWN;
    this.cameras.main.fadeOut(300, 0, 0, 0);
    this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
      const kind = enemy ?? (Math.random() < 0.5 ? "slime" : "goblin");
      this.scene.start("Battle", { enemy: kind });
    });
  }

  private animateWater(): void {
    this.layer.forEachTile((tile) => {
      if (tile.index === T_WATER_A) tile.index = T_WATER_B;
      else if (tile.index === T_WATER_B) tile.index = T_WATER_A;
    });
  }
}