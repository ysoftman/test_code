import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { GameState, isNight, clock, dayCount, onSaved } from "../gameState";
import { retroStyle, showToast } from "../pixelart";
import { Sfx, DUNGEON_THEME } from "../audio";
import {
  buildDungeon,
  DUNGEON_W,
  DUNGEON_H,
  DUNGEON_ENTRY,
  DUNGEON_ZONES,
  TREASURE_POS,
  TILE,
  SOLID,
  T_WATER_A,
  T_WATER_B,
} from "../levels";

type LastMove = "down" | "up" | "right" | "left";

const ENCOUNTER_COOLDOWN = 600;
const EXIT_SAFE_RADIUS_X = TILE * 2;
const EXIT_SAFE_RADIUS_Y = TILE * 2.5;

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
  kind: "slime" | "goblin" | "king";
}

const IDLE_TEXTURE: Record<LastMove, string> = {
  down: "hero-idle-down",
  up: "hero-idle-up",
  right: "hero-idle-right",
  left: "hero-idle-left",
};

export class DungeonScene extends Phaser.Scene {
  private player!: Phaser.Physics.Arcade.Sprite;
  private playerShadow!: Phaser.GameObjects.Ellipse;
  private weaponOverlay!: Phaser.GameObjects.Sprite;
  private shieldOverlay!: Phaser.GameObjects.Sprite;
  private layer!: Phaser.Tilemaps.TilemapLayer;
  private dust!: Phaser.GameObjects.Particles.ParticleEmitter;
  private roamerGroup!: Phaser.Physics.Arcade.Group;
  private roamers: Roamer[] = [];
  private encounterCooldown = 0;
  private exitingDungeon = false;
  private sQueued = false;
  private lastMove: LastMove = "down";

  private keyLeft!: Phaser.Input.Keyboard.Key;
  private keyRight!: Phaser.Input.Keyboard.Key;
  private keyUp!: Phaser.Input.Keyboard.Key;
  private keyDown!: Phaser.Input.Keyboard.Key;
  private keyH!: Phaser.Input.Keyboard.Key;
  private keyJ!: Phaser.Input.Keyboard.Key;
  private keyK!: Phaser.Input.Keyboard.Key;
  private keyL!: Phaser.Input.Keyboard.Key;
  private keyS!: Phaser.Input.Keyboard.Key;
  private keyM!: Phaser.Input.Keyboard.Key;
  private mQueued = false;
  private qQueued = false;

  private statusText!: Phaser.GameObjects.Text;
  private statusPanel!: Phaser.GameObjects.Rectangle;
  private statusLast = "";

  constructor() {
    super("Dungeon");
  }

  create(): void {
    Sfx.playBgm(DUNGEON_THEME);
    this.roamers = [];
    this.encounterCooldown = GameState.encountersLocked() ? ENCOUNTER_COOLDOWN : 0;
    this.lastMove = "down";
    this.exitingDungeon = false;

    // Registered before the SHUTDOWN handler below that calls GameState.save()
    // — SHUTDOWN listeners fire in registration order, so this unsubscribes
    // before that save happens and no toast gets created on a scene that's
    // already tearing down. Keep this the first SHUTDOWN listener.
    const unsubSaved = onSaved(() => showToast(this, "SAVED"));
    this.events.once(Phaser.Scenes.Events.SHUTDOWN, unsubSaved);

    const level = buildDungeon();
    const map = this.make.tilemap({
      data: level,
      tileWidth: TILE,
      tileHeight: TILE,
    });
    const tileset = map.addTilesetImage("tiles16", "tiles16", TILE, TILE);
    this.layer = map.createLayer(0, tileset!, 0, 0)!;
    this.layer.setCollision(Array.from(SOLID));
    this.layer.setTint(0x8899bb);

    this.physics.world.setBounds(0, 0, DUNGEON_W * TILE, DUNGEON_H * TILE);

    this.add
      .text(DUNGEON_W * TILE / 2, 20, "THE CAVE", retroStyle(8, "#ffd166"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(95);

    this.add
      .image(DUNGEON_ENTRY.x, DUNGEON_ENTRY.y, "cave")
      .setDepth(9);

    this.player = this.physics.add.sprite(
      DUNGEON_ENTRY.x,
      DUNGEON_ENTRY.y + TILE * 2,
      "hero-idle-down"
    );
    this.player.setCollideWorldBounds(true);
    this.player.setDepth(10);
    this.player.body?.setSize(20, 16).setOffset(6, 16);
    this.physics.add.collider(this.player, this.layer);

    this.playerShadow = this.add
      .ellipse(this.player.x, this.player.y + 14, 20, 8, 0x000000, 0.4)
      .setDepth(5);

    this.weaponOverlay = this.add
      .sprite(this.player.x, this.player.y, "equip-sword")
      .setDepth(11)
      .setVisible(false);
    this.shieldOverlay = this.add
      .sprite(this.player.x, this.player.y, "equip-shield")
      .setDepth(11)
      .setVisible(false);

    const walkFrames = (dir: string): Phaser.Types.Animations.AnimationFrame[] =>
      [0, 1, 2, 3].map((i) => ({ key: `hero-${dir}-${i}` }));

    if (!this.anims.exists("walk-down")) {
      this.anims.create({
        key: "walk-down",
        frames: walkFrames("down"),
        frameRate: 10,
        repeat: -1,
      });
    }
    if (!this.anims.exists("walk-up")) {
      this.anims.create({
        key: "walk-up",
        frames: walkFrames("up"),
        frameRate: 10,
        repeat: -1,
      });
    }
    if (!this.anims.exists("walk-right")) {
      this.anims.create({
        key: "walk-right",
        frames: walkFrames("right"),
        frameRate: 10,
        repeat: -1,
      });
    }
    if (!this.anims.exists("walk-left")) {
      this.anims.create({
        key: "walk-left",
        frames: walkFrames("left"),
        frameRate: 10,
        repeat: -1,
      });
    }

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

    this.spawnTreasures();

    this.physics.add.overlap(this.player, this.roamerGroup, (_p, roamer) => {
      if (this.encounterCooldown > 0) return;
      const r = this.roamers.find((r) => r.sprite === roamer);
      // BattleScene.runBattle() already plays the boss fanfare for the boss
      // enemy; playing it here too would sound it twice.
      this.startBattle(r?.kind ?? "slime");
    });

    const exit = this.add.zone(DUNGEON_ENTRY.x, DUNGEON_ENTRY.y, TILE * 2, TILE * 2);
    this.physics.add.existing(exit);
    this.physics.add.overlap(this.player, exit, () => {
      if (!this.exitingDungeon) this.exitDungeon();
    });

    this.time.addEvent({
      delay: 400,
      loop: true,
      callback: () => this.animateWater(),
    });

    this.cameras.main.startFollow(this.player, true, 0.08, 0.08);
    this.cameras.main.setBounds(0, 0, DUNGEON_W * TILE, DUNGEON_H * TILE);

    const kb = this.input.keyboard!;
    this.keyLeft = kb.addKey(Phaser.Input.Keyboard.KeyCodes.LEFT);
    this.keyRight = kb.addKey(Phaser.Input.Keyboard.KeyCodes.RIGHT);
    this.keyUp = kb.addKey(Phaser.Input.Keyboard.KeyCodes.UP);
    this.keyDown = kb.addKey(Phaser.Input.Keyboard.KeyCodes.DOWN);
    this.keyH = kb.addKey(Phaser.Input.Keyboard.KeyCodes.H);
    this.keyJ = kb.addKey(Phaser.Input.Keyboard.KeyCodes.J);
    this.keyK = kb.addKey(Phaser.Input.Keyboard.KeyCodes.K);
    this.keyL = kb.addKey(Phaser.Input.Keyboard.KeyCodes.L);
    this.keyS = kb.addKey(Phaser.Input.Keyboard.KeyCodes.S);
    this.keyS.on(Phaser.Input.Keyboard.Events.DOWN, () => {
      this.sQueued = true;
    });
    this.keyM = kb.addKey(Phaser.Input.Keyboard.KeyCodes.M);
    this.keyM.on(Phaser.Input.Keyboard.Events.DOWN, () => {
      this.mQueued = true;
    });
    kb.addKey(Phaser.Input.Keyboard.KeyCodes.Q).on(
      Phaser.Input.Keyboard.Events.DOWN,
      (_k: Phaser.Input.Keyboard.Key, e: KeyboardEvent) => {
        if (!e.repeat) this.qQueued = true;
      }
    );

    this.add
      .text(
        GAME_WIDTH - 8,
        GAME_HEIGHT - 6,
        "HJKL:MOVE  S:HUD  M:MUTE  Q:QUIT  FIND THE KING!",
        retroStyle(6, "#9f9fd0")
      )
      .setOrigin(1, 1)
      .setScrollFactor(0)
      .setDepth(100);

    const dark = this.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH, GAME_HEIGHT, 0x0a0a2a, 0.35)
      .setScrollFactor(0)
      .setDepth(90);

    const statusDummy = ["HERO", "LV 1", "HP 30/30", "MP 10/10", "DAY 1 00:00"].join("\n");
    this.statusText = this.add
      .text(16, 0, statusDummy, retroStyle(6, "#ffffff"))
      .setOrigin(0, 0)
      .setScrollFactor(0)
      .setDepth(101)
      .setVisible(GameState.hudVisible);
    const statusH = this.statusText.height + 24;
    this.statusText.setY(GAME_HEIGHT - 8 - statusH + 12);
    this.statusPanel = this.add
      .rectangle(8, GAME_HEIGHT - 8, 180, statusH, 0x0b0b2b, 0.88)
      .setOrigin(0, 1)
      .setStrokeStyle(1, 0xffffff)
      .setScrollFactor(0)
      .setDepth(100)
      .setVisible(GameState.hudVisible);

    this.events.once(Phaser.Scenes.Events.SHUTDOWN, () => {
      GameState.save();
      dark.destroy();
    });
  }

  update(_time: number, delta: number): void {
    GameState.minutes += delta / 1000;
    this.updateStatus();

    if (this.sQueued) {
      this.sQueued = false;
      this.toggleStatus();
    }

    if (this.mQueued) {
      this.mQueued = false;
      const muted = Sfx.toggleMuted();
      showToast(this, muted ? "SOUND: OFF" : "SOUND: ON");
    }

    if (this.qQueued) {
      this.qQueued = false;
      // the SHUTDOWN handler saves, so this is save-and-quit
      this.scene.start("Title");
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
    this.updateEquipOverlays();
    this.updateRoamers(delta);
    this.checkEncounter(delta);
  }

  private updateEquipOverlays(): void {
    this.weaponOverlay.setVisible(!!GameState.equipped.weapon);
    this.shieldOverlay.setVisible(!!GameState.equipped.armor);
    this.weaponOverlay.setTexture(
      GameState.equipped.weapon === "ironSword" ? "equip-iron-sword" : "equip-sword"
    );
    this.shieldOverlay.setTexture(
      GameState.equipped.armor === "ironShield" ? "equip-iron-shield" : "equip-shield"
    );
    const flip = this.lastMove === "left";
    this.weaponOverlay.setFlipX(flip);
    this.shieldOverlay.setFlipX(flip);
    this.weaponOverlay.setPosition(this.player.x + 7, this.player.y + 2);
    this.shieldOverlay.setPosition(this.player.x - 7, this.player.y + 4);
  }

  private toggleStatus(): void {
    const visible = !this.statusPanel.visible;
    this.statusPanel.setVisible(visible);
    this.statusText.setVisible(visible);
    GameState.hudVisible = visible;
    GameState.saveSettings();
  }

  private updateStatus(): void {
    const p = GameState.player;
    const text = [
      p.name,
      `LV ${p.level}`,
      `HP ${p.hp}/${GameState.effMaxHp()}`,
      `MP ${p.mp}/${p.maxMp}`,
      `DAY ${dayCount()} ${clock()}`,
    ].join("\n");
    if (text !== this.statusLast) {
      this.statusLast = text;
      this.statusText.setText(text);
    }
  }

  private exitDungeon(): void {
    if (this.exitingDungeon) return;
    this.exitingDungeon = true;
    Sfx.night();
    this.player.setVelocity(0, 0);
    this.cameras.main.fadeOut(200, 0, 0, 0);
    this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
      this.scene.start("World", { fromDungeon: true });
    });
  }

  private checkEncounter(delta: number): void {
    if (this.encounterCooldown > 0) {
      this.encounterCooldown -= delta;
      return;
    }
    const nearExit =
      Math.abs(this.player.x - DUNGEON_ENTRY.x) < EXIT_SAFE_RADIUS_X &&
      Math.abs(this.player.y - DUNGEON_ENTRY.y) < EXIT_SAFE_RADIUS_Y;
    if (nearExit) return;
    const rate = (isNight() ? 0.1 : 0.06) * (delta / 1000);
    if (Math.random() < rate) {
      this.startBattle();
    }
  }

  private spawnMonsters(): void {
    this.roamerGroup = this.physics.add.group();
    for (const zone of DUNGEON_ZONES) {
      const isBoss = zone.count === 1;
      for (let i = 0; i < zone.count; i++) {
        const x = zone.cx + (Math.random() - 0.5) * zone.w * 0.6;
        const y = zone.cy + (Math.random() - 0.5) * zone.h * 0.6;
        const kind: Roamer["kind"] = isBoss
          ? "king"
          : Math.random() < 0.4
            ? "slime"
            : "goblin";
        const sprite = this.roamerGroup.create(
          x,
          y,
          kind === "king" ? "king" : kind
        ) as Phaser.Physics.Arcade.Sprite;
        sprite.setDepth(10);
        sprite.body?.setSize(20, 12).setOffset(6, 16);
        if (kind === "king") {
          sprite.setScale(1.5);
        }
        this.roamers.push({
          sprite,
          minX: zone.cx - zone.w / 2 + 4,
          maxX: zone.cx + zone.w / 2 - 4,
          minY: zone.cy - zone.h / 2 + 4,
          maxY: zone.cy + zone.h / 2 - 4,
          targetX: x,
          targetY: y,
          wait: 300 + Math.random() * 800,
          speed: (isBoss ? 20 : 28) + Math.random() * 20,
          kind,
        });
        this.tweens.add({
          targets: sprite,
          scaleX: kind === "king" ? 1.68 : 1.12,
          scaleY: kind === "king" ? 1.32 : 0.88,
          duration: 280,
          yoyo: true,
          repeat: -1,
          ease: "Sine.easeInOut",
        });
      }
    }
  }

  private spawnTreasures(): void {
    for (const t of TREASURE_POS) {
      const opened = GameState.openedTreasures.includes(t.id);
      const chest = this.add.image(t.x, t.y, opened ? "chest-open" : "chest").setDepth(9);
      if (opened) continue;
      const zone = this.add.zone(t.x, t.y, TILE, TILE);
      this.physics.add.existing(zone);
      this.physics.add.overlap(this.player, zone, () => this.openTreasure(t.id, chest));
    }
  }

  private openTreasure(id: string, chest: Phaser.GameObjects.Image): void {
    if (GameState.openedTreasures.includes(id)) return;
    GameState.openedTreasures.push(id);
    chest.setTexture("chest-open");
    Sfx.chest();
    const gold = 15 + Math.floor(Math.random() * 16);
    GameState.gold += gold;
    let loot = "";
    const r = Math.random();
    if (r < 0.4) {
      GameState.inventory.potion += 1;
      loot = " POTION!";
    } else if (r < 0.6) {
      GameState.inventory.candy += 1;
      loot = " CANDY!";
    }
    if (loot) Sfx.pickup();
    const note = this.add
      .text(chest.x, chest.y - 26, `+${gold} GOLD${loot}`, retroStyle(6, "#ffd166"))
      .setOrigin(0.5)
      .setDepth(120);
    this.tweens.add({
      targets: note,
      y: note.y - 20,
      alpha: 0,
      duration: 900,
      onComplete: () => note.destroy(),
    });
    GameState.save();
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

  private startBattle(enemy?: "slime" | "goblin" | "king"): void {
    if (this.encounterCooldown > 0) return; // already fading into a battle
    this.player.setVelocity(0, 0);
    this.encounterCooldown = ENCOUNTER_COOLDOWN;
    this.cameras.main.fadeOut(300, 0, 0, 0);
    this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
      const kind = enemy ?? (Math.random() < 0.4 ? "slime" : "goblin");
      this.scene.start("Battle", { enemy: kind, from: "Dungeon" });
    });
  }

  private animateWater(): void {
    this.layer.forEachTile((tile) => {
      if (tile.index === T_WATER_A) tile.index = T_WATER_B;
      else if (tile.index === T_WATER_B) tile.index = T_WATER_A;
    });
  }
}