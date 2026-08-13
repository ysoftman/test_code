import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { retroStyle } from "../pixelart";
import { DialogueBox } from "../ui/DialogueBox";
import {
  buildLevel,
  MAP_W,
  MAP_H,
  PLAYER_SPAWN,
  NPC_POS,
  HOUSE_POS,
  MONSTER_ZONES,
  SOLID,
  T_WATER_A,
  T_WATER_B,
  TALL_GRASS,
  TILE,
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
  private npc!: Phaser.GameObjects.Sprite;
  private layer!: Phaser.Tilemaps.TilemapLayer;
  private dialogue!: DialogueBox;
  private dust!: Phaser.GameObjects.Particles.ParticleEmitter;
  private roamerGroup!: Phaser.Physics.Arcade.Group;
  private roamers: Roamer[] = [];
  private encounterCooldown = 0;
  private lastMove: LastMove = "down";

  private keyLeft!: Phaser.Input.Keyboard.Key;
  private keyRight!: Phaser.Input.Keyboard.Key;
  private keyUp!: Phaser.Input.Keyboard.Key;
  private keyDown!: Phaser.Input.Keyboard.Key;
  private keyZ!: Phaser.Input.Keyboard.Key;
  private keySpace!: Phaser.Input.Keyboard.Key;
  private keyB!: Phaser.Input.Keyboard.Key;

  constructor() {
    super("World");
  }

  create(): void {
    this.roamers = [];
    this.encounterCooldown = 0;
    this.lastMove = "down";

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

    this.add
      .image(70, 36, "moon")
      .setScrollFactor(0)
      .setDepth(-50);
    this.add
      .image(GAME_WIDTH / 2, 36, "stars")
      .setScrollFactor(0)
      .setDepth(-50);

    this.add
      .image(HOUSE_POS.x + TILE, HOUSE_POS.y + TILE, "house")
      .setOrigin(0.5, 0.5);

    this.npc = this.add.sprite(NPC_POS.x, NPC_POS.y, "npc").setDepth(10);
    this.add
      .ellipse(NPC_POS.x, NPC_POS.y + 7, 10, 4, 0x000000, 0.4)
      .setDepth(5);

    this.player = this.physics.add.sprite(
      PLAYER_SPAWN.x,
      PLAYER_SPAWN.y,
      "hero-idle-down"
    );
    this.player.setCollideWorldBounds(true);
    this.player.setDepth(10);
    this.player.body?.setSize(10, 8).setOffset(3, 8);
    this.physics.add.collider(this.player, this.layer);

    this.playerShadow = this.add
      .ellipse(this.player.x, this.player.y + 7, 10, 4, 0x000000, 0.4)
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
    this.dust.startFollow(this.player, 0, 7);

    this.spawnMonsters();

    this.physics.add.overlap(this.player, this.roamerGroup, () => {
      if (this.encounterCooldown <= 0) this.startBattle("slime");
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
    this.keyZ = kb.addKey(Phaser.Input.Keyboard.KeyCodes.Z);
    this.keySpace = kb.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);
    this.keyB = kb.addKey(Phaser.Input.Keyboard.KeyCodes.B);

    this.dialogue = new DialogueBox(this, [
      "Welcome to MAGIC WORLD!",
      "I am Elder Willow.",
      "Slimes lurk in the tall grass.",
      "Press Z to fight them.",
      "Bring peace to our village!",
    ]);

    const hint = this.add
      .text(
        GAME_WIDTH / 2,
        GAME_HEIGHT - 6,
        "ARROWS:MOVE  Z:TALK/ATTACK",
        retroStyle(6, "#9f9fd0")
      )
      .setOrigin(0.5, 1)
      .setScrollFactor(0)
      .setDepth(100);

    this.events.once(Phaser.Scenes.Events.SHUTDOWN, () => {
      this.dialogue.destroy();
      hint.destroy();
    });
  }

  update(_time: number, delta: number): void {
    if (this.dialogue.isActive()) {
      this.player.setVelocity(0, 0);
      this.player.anims.stop();
      this.dust.emitting = false;
      this.dialogue.update();
      this.updateRoamers(delta);
      return;
    }

    if (Phaser.Input.Keyboard.JustDown(this.keyZ) || Phaser.Input.Keyboard.JustDown(this.keySpace)) {
      if (this.tryTalk()) return;
    }
    if (Phaser.Input.Keyboard.JustDown(this.keyB)) {
      this.startBattle();
      return;
    }

    let vx = 0;
    let vy = 0;
    if (this.keyLeft.isDown) vx = -60;
    else if (this.keyRight.isDown) vx = 60;
    if (this.keyUp.isDown) vy = -60;
    else if (this.keyDown.isDown) vy = 60;

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

    this.playerShadow.setPosition(this.player.x, this.player.y + 7);
    this.dust.emitting = moving;
    this.updateRoamers(delta);
    this.checkEncounter(delta);
  }

  private tryTalk(): boolean {
    const dx = this.player.x - this.npc.x;
    const dy = this.player.y - this.npc.y;
    if (dx * dx + dy * dy > 30 * 30) return false;
    this.dialogue.start();
    return true;
  }

  private checkEncounter(delta: number): void {
    if (this.encounterCooldown > 0) {
      this.encounterCooldown -= delta;
      return;
    }
    const tile = this.layer.getTileAtWorldXY(this.player.x, this.player.y);
    if (!tile || tile.index !== TALL_GRASS) return;
    if (Math.random() < ENCOUNTER_RATE) {
      this.startBattle();
    }
  }

  private spawnMonsters(): void {
    this.roamerGroup = this.physics.add.group();
    for (const zone of MONSTER_ZONES) {
      const signX = zone.cx - zone.w / 2 - 8;
      this.add.image(signX, zone.cy, "sign").setDepth(9);
      const bang = this.add
        .text(signX, zone.cy - 16, "!", retroStyle(10, "#ffdd44"))
        .setOrigin(0.5)
        .setStroke("#7c2d12", 2)
        .setDepth(11);
      this.tweens.add({
        targets: bang,
        y: zone.cy - 21,
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
        sprite.body?.setSize(10, 6).setOffset(3, 8);
        this.roamers.push({
          sprite,
          minX: zone.cx - zone.w / 2 + 2,
          maxX: zone.cx + zone.w / 2 - 2,
          minY: zone.cy - zone.h / 2 + 2,
          maxY: zone.cy + zone.h / 2 - 2,
          targetX: x,
          targetY: y,
          wait: 300 + Math.random() * 800,
          speed: 14 + Math.random() * 10,
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
