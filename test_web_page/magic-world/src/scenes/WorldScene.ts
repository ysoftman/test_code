import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { GameState, isNight, nightFactor, onSaved } from "../gameState";
import { retroStyle, showToast } from "../pixelart";
import { StatusHud, STATUS_HUD_TOAST_Y } from "../ui/StatusHud";
import { DialogueBox } from "../ui/DialogueBox";
import { ShopUI } from "../ui/Shop";
import { InventoryUI } from "../ui/InventoryUI";
import { BestiaryUI } from "../ui/BestiaryUI";
import { Minimap } from "../ui/Minimap";
import { Sfx, OVERWORLD_THEME } from "../audio";
import { CATCHABLE, allSpeciesCaught } from "../monsters";
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
  FOREST_POS,
  MONSTER_ZONES,
  escapeFromZones,
  SOLID,
  T_WATER_A,
  T_WATER_B,
  TALL_GRASS,
} from "../levels";

const ENCOUNTER_RATE = 0.18;
const ENCOUNTER_COOLDOWN = 600;
const TROLL_KING_SPAWN_CHANCE = 0.35;

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
  kind: "slime" | "troll" | "wolf";
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
  private weaponOverlay!: Phaser.GameObjects.Sprite;
  private shieldOverlay!: Phaser.GameObjects.Sprite;
  private layer!: Phaser.Tilemaps.TilemapLayer;
  private dialogue!: DialogueBox;
  private shop!: ShopUI;
  private inventory!: InventoryUI;
  private bestiary!: BestiaryUI;
  private dust!: Phaser.GameObjects.Particles.ParticleEmitter;
  private fireflies!: Phaser.GameObjects.Particles.ParticleEmitter;
  private roamerGroup!: Phaser.Physics.Arcade.Group;
  private roamers: Roamer[] = [];
  private encounterCooldown = 0;
  private lastMove: LastMove = "down";
  private nightOverlay!: Phaser.GameObjects.Rectangle;
  private homeLabel!: Phaser.GameObjects.Text;
  private homeBubble!: Phaser.GameObjects.Container;
  private bubbleVisible = false;
  private resting = false;
  private enteringDungeon = false;
  private enteringForest = false;
  // true while overlapping the forest zone; reset a full tile away so the
  // sealed-entrance dialogue doesn't restart every overlap frame
  private forestOverlapActive = false;
  private zQueued = false;
  private sQueued = false;
  private ctrlSQueued = false;
  private iQueued = false;
  private gCheatQueued = false;
  private mQueued = false;
  private tQueued = false;
  private bQueued = false;
  private qQueued = false;
  private quitConfirm = false;
  private yQueued = false;
  private nQueued = false;
  private escQueued = false;
  private quitConfirmText!: Phaser.GameObjects.Text;

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
  private keyS!: Phaser.Input.Keyboard.Key;
  private keyI!: Phaser.Input.Keyboard.Key;
  private keyG!: Phaser.Input.Keyboard.Key;
  private keyM!: Phaser.Input.Keyboard.Key;
  private keyT!: Phaser.Input.Keyboard.Key;
  private keyB!: Phaser.Input.Keyboard.Key;
  private keyY!: Phaser.Input.Keyboard.Key;
  private keyN!: Phaser.Input.Keyboard.Key;
  private keyEsc!: Phaser.Input.Keyboard.Key;

  private hud!: StatusHud;
  private minimap!: Minimap;
  private guardPos = { x: 0, y: 0 };

  constructor() {
    super("World");
  }

  create(data?: { fromDungeon?: boolean; fromBattle?: boolean; fromForest?: boolean }): void {
    Sfx.playBgm(OVERWORLD_THEME);
    this.roamers = [];
    this.encounterCooldown = GameState.encountersLocked() ? ENCOUNTER_COOLDOWN : 0;
    this.lastMove = "down";
    this.resting = false;
    this.enteringDungeon = false;
    this.enteringForest = false;
    this.forestOverlapActive = false;

    // Registered before the SHUTDOWN handler below that calls GameState.save()
    // — SHUTDOWN listeners fire in registration order, so this unsubscribes
    // before that save happens and no toast gets created on a scene that's
    // already tearing down. Keep this the first SHUTDOWN listener.
    const unsubSaved = onSaved(() => showToast(this, "SAVED", STATUS_HUD_TOAST_Y));
    this.events.once(Phaser.Scenes.Events.SHUTDOWN, unsubSaved);

    const level = buildLevel();
    const map = this.make.tilemap({
      data: level,
      tileWidth: TILE,
      tileHeight: TILE,
    });
    const tileset = map.addTilesetImage("tiles16", "tiles16", TILE, TILE);
    this.layer = map.createLayer(0, tileset!, 0, 0)! as Phaser.Tilemaps.TilemapLayer;
    this.layer.setCollision(Array.from(SOLID));

    this.physics.world.setBounds(0, 0, MAP_W * TILE, MAP_H * TILE);

    this.add
      .image(HOUSE_POS.x + TILE, HOUSE_POS.y + TILE, "house")
      .setOrigin(0.5, 0.5);
    this.homeLabel = this.add
      .text(HOUSE_POS.x + TILE, HOUSE_POS.y + TILE - 80, "HOME", retroStyle(5, "#9f9fd0"))
      .setOrigin(0.5)
      .setDepth(11);
    this.homeBubble = this.buildHomeBubble();
    this.homeBubble.setVisible(false);

    this.add
      .sprite(NPC_POS.x, NPC_POS.y, "npc").setDepth(10);
    this.add
      .ellipse(NPC_POS.x, NPC_POS.y + 28, 40, 16, 0x000000, 0.4)
      .setDepth(5);
    this.add
      .text(NPC_POS.x, NPC_POS.y - 48, "ELDER", retroStyle(5, "#9f9fd0"))
      .setOrigin(0.5)
      .setDepth(11);

    this.add.sprite(SHOP_POS.x, SHOP_POS.y, "npc").setDepth(10).setTint(0xffd166);
    this.add
      .ellipse(SHOP_POS.x, SHOP_POS.y + 28, 40, 16, 0x000000, 0.4)
      .setDepth(5);
    this.add
      .text(SHOP_POS.x, SHOP_POS.y - 48, "SHOP", retroStyle(5, "#ffd166"))
      .setOrigin(0.5)
      .setDepth(11);

    this.add.image(CAVE_POS.x, CAVE_POS.y, "cave").setDepth(9);
    this.add
      .text(CAVE_POS.x, CAVE_POS.y + 32, "CAVE", retroStyle(6, "#9f9fd0"))
      .setOrigin(0.5)
      .setDepth(11);

    // eastern woods entrance: the zone itself is created further down, this is
    // just its ground dressing — sign beside the opening, name above it
    const signX = Phaser.Math.Clamp(FOREST_POS.x + TILE, TILE, (MAP_W - 1) * TILE);
    this.add.image(signX, FOREST_POS.y, "sign").setDepth(9);
    this.add
      .text(FOREST_POS.x, FOREST_POS.y - 40, "FOREST", retroStyle(6, "#9f9fd0"))
      .setOrigin(0.5)
      .setDepth(11);

    // gatekeeper who lets nobody through until the KING SLIME falls; stands a
    // tile west of the entrance (clamped so a map-edge FOREST_POS keeps him
    // on the tileset)
    this.guardPos = {
      x: Phaser.Math.Clamp(FOREST_POS.x - TILE, TILE, (MAP_W - 1) * TILE),
      y: Phaser.Math.Clamp(FOREST_POS.y, TILE * 1.5, (MAP_H - 1) * TILE - TILE * 0.5),
    };
    this.add.sprite(this.guardPos.x, this.guardPos.y, "npc").setDepth(10).setTint(0x67e8f9);
    this.add
      .ellipse(this.guardPos.x, this.guardPos.y + 28, 40, 16, 0x000000, 0.4)
      .setDepth(5);
    this.add
      .text(this.guardPos.x, this.guardPos.y - 48, "GUARD", retroStyle(5, "#67e8f9"))
      .setOrigin(0.5)
      .setDepth(11);

    const respawn = GameState.pos ?? PLAYER_SPAWN;
    // Position-based fallback for old saves / any other path that lands here
    // without the explicit flag. The real signal is `data.fromDungeon`, set
    // by DungeonScene.exitDungeon() — inferring "near the cave" from raw
    // coordinates undercounts the actual overlap-trigger radius (player body
    // half-width extends it further than this box), so it can't be trusted
    // alone.
    const nearCave =
      Math.abs(respawn.x - CAVE_POS.x) <= TILE / 2 &&
      Math.abs(respawn.y - CAVE_POS.y) <= TILE / 2;
    const fromDungeon = !!data?.fromDungeon || nearCave;
    const fromForest = !!data?.fromForest;
    const spawn = fromDungeon
      ? { x: CAVE_POS.x, y: CAVE_POS.y + TILE * 2 }
      : fromForest
        ? { x: FOREST_POS.x, y: FOREST_POS.y + TILE * 2 }
        : respawn;
    // just walked out of the cave/forest: hold off re-triggering it in case
    // the player is still holding the walk-in key
    if (fromDungeon || fromForest)
      this.encounterCooldown = Math.max(this.encounterCooldown, ENCOUNTER_COOLDOWN);
    this.player = this.physics.add.sprite(
      spawn.x,
      spawn.y,
      "hero-idle-down"
    );
    this.player.setCollideWorldBounds(true);
    this.player.setDepth(10);
    this.player.body?.setSize(40, 32).setOffset(12, 32);
    this.physics.add.collider(this.player, this.layer);

    // A battle just ended on this spot, which is inside a monster zone —
    // step out to the nearest walkable tile outside it so the encounter
    // lock expiring here doesn't trigger another fight immediately.
    if (data?.fromBattle) this.escapeMonsterZone();

    this.playerShadow = this.add
      .ellipse(this.player.x, this.player.y + 28, 40, 16, 0x000000, 0.4)
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
      speed: { min: 16, max: 44 },
      lifespan: { min: 180, max: 320 },
      scale: { start: 1, end: 0 },
      alpha: { start: 0.45, end: 0 },
      frequency: 70,
      emitting: false,
    });
    this.dust.startFollow(this.player, 0, 28);

    this.fireflies = this.add.particles(0, 0, "firefly", {
      speed: { min: 12, max: 40 },
      lifespan: { min: 2500, max: 4500 },
      scale: { start: 1, end: 0.4 },
      alpha: { start: 0.7, end: 0 },
      frequency: 700,
      emitting: false,
    });
    this.fireflies.startFollow(this.player, 0, 0);

    this.spawnMonsters();

    this.physics.add.overlap(this.player, this.roamerGroup, (_p, roamer) => {
      if (this.encounterCooldown > 0) return;
      if (this.uiBlocking()) return;
      // the monster zones are cramped enough that a slime can overlap the
      // player at the same moment as the troll; always let the rare one win
      // the tie instead of whichever roamer the physics engine happened to
      // report first
      const troll = this.roamers.find((r) => r.kind === "troll");
      const r =
        troll && this.physics.overlap(this.player, troll.sprite)
          ? troll
          : this.roamers.find((r) => r.sprite === roamer);
      // BattleScene.runBattle() already plays the boss fanfare for boss/giant
      // enemies; playing it here too would sound it twice.
      this.startBattle(r?.kind ?? "slime");
    });

    const cave = this.add.zone(CAVE_POS.x, CAVE_POS.y, TILE, TILE).setDepth(1);
    this.physics.add.existing(cave);
    this.physics.add.overlap(this.player, cave, () => {
      if (this.enteringDungeon || this.encounterCooldown > 0) return;
      if (this.uiBlocking()) return;
      this.enterDungeon();
    });

    const forest = this.add.zone(FOREST_POS.x, FOREST_POS.y, TILE, TILE).setDepth(1);
    this.physics.add.existing(forest);
    this.physics.add.overlap(this.player, forest, () => {
      if (this.enteringForest || this.enteringDungeon || this.encounterCooldown > 0) return;
      if (this.uiBlocking()) return;
      // overlap fires every frame while the body stays in the zone, so only
      // act on the entry edge and reset on exit (see updateForestGate)
      if (this.forestOverlapActive) return;
      this.forestOverlapActive = true;
      if (!GameState.quest.bossDefeated) {
        this.dialogue.start(["The forest is sealed.", "Defeat the KING SLIME", "first!"], "GUARD");
        return;
      }
      this.enterForest();
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
    // ignore e.repeat on keys the title screen also uses (Z/SPACE/C): holding
    // one through the scene switch delivers repeat keydowns to the fresh Keys
    // here, instantly triggering talk/rest or the bestiary on entry
    this.keyZ = kb.addKey(Phaser.Input.Keyboard.KeyCodes.Z);
    this.keyZ.on(Phaser.Input.Keyboard.Events.DOWN, (_k: Phaser.Input.Keyboard.Key, e: KeyboardEvent) => {
      if (!e.repeat) this.zQueued = true;
    });
    this.keySpace = kb.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);
    this.keySpace.on(Phaser.Input.Keyboard.Events.DOWN, (_k: Phaser.Input.Keyboard.Key, e: KeyboardEvent) => {
      if (!e.repeat) this.zQueued = true;
    });
    this.keyS = kb.addKey(Phaser.Input.Keyboard.KeyCodes.S);
    this.keyS.on(Phaser.Input.Keyboard.Events.DOWN, (_k: Phaser.Input.Keyboard.Key, e: KeyboardEvent) => {
      if (e.ctrlKey) this.ctrlSQueued = true;
      else this.sQueued = true;
    });
    this.keyI = kb.addKey(Phaser.Input.Keyboard.KeyCodes.I);
    this.keyI.on(Phaser.Input.Keyboard.Events.DOWN, () => {
      this.iQueued = true;
    });
    this.keyG = kb.addKey(Phaser.Input.Keyboard.KeyCodes.G);
    this.keyG.on(Phaser.Input.Keyboard.Events.DOWN, () => {
      if (this.keyG.ctrlKey) this.gCheatQueued = true;
    });
    this.keyM = kb.addKey(Phaser.Input.Keyboard.KeyCodes.M);
    this.keyM.on(Phaser.Input.Keyboard.Events.DOWN, () => {
      this.mQueued = true;
    });
    this.keyT = kb.addKey(Phaser.Input.Keyboard.KeyCodes.T);
    this.keyT.on(Phaser.Input.Keyboard.Events.DOWN, (_k: Phaser.Input.Keyboard.Key, e: KeyboardEvent) => {
      if (!e.repeat) this.tQueued = true;
    });
    this.keyB = kb.addKey(Phaser.Input.Keyboard.KeyCodes.B);
    this.keyB.on(Phaser.Input.Keyboard.Events.DOWN, (_k: Phaser.Input.Keyboard.Key, e: KeyboardEvent) => {
      if (!e.repeat) this.bQueued = true;
    });
    kb.addKey(Phaser.Input.Keyboard.KeyCodes.Q).on(
      Phaser.Input.Keyboard.Events.DOWN,
      (_k: Phaser.Input.Keyboard.Key, e: KeyboardEvent) => {
        if (!e.repeat) this.qQueued = true;
      }
    );
    this.keyY = kb.addKey(Phaser.Input.Keyboard.KeyCodes.Y);
    this.keyY.on(Phaser.Input.Keyboard.Events.DOWN, (_k: Phaser.Input.Keyboard.Key, e: KeyboardEvent) => {
      if (!e.repeat) this.yQueued = true;
    });
    this.keyN = kb.addKey(Phaser.Input.Keyboard.KeyCodes.N);
    this.keyN.on(Phaser.Input.Keyboard.Events.DOWN, (_k: Phaser.Input.Keyboard.Key, e: KeyboardEvent) => {
      if (!e.repeat) this.nQueued = true;
    });
    this.keyEsc = kb.addKey(Phaser.Input.Keyboard.KeyCodes.ESC);
    this.keyEsc.on(Phaser.Input.Keyboard.Events.DOWN, (_k: Phaser.Input.Keyboard.Key, e: KeyboardEvent) => {
      if (this.quitConfirm && !e.repeat) this.escQueued = true;
    });

    this.dialogue = new DialogueBox(this, []);
    this.shop = new ShopUI(this);
    this.inventory = new InventoryUI(this);
    this.bestiary = new BestiaryUI(this);

    const hint = this.add
      .text(
        GAME_WIDTH - 8,
        GAME_HEIGHT - 6,
        "HJKL:MOVE Z:TALK/OK I:ITEMS ESC:SKIP\nS:HUD M:MUTE B:BESTIARY T:MAP Q:QUIT CTRL+S:SAVE",
        retroStyle(6, "#9f9fd0")
      )
      .setOrigin(1, 1)
      .setAlign("right")
      .setScrollFactor(0)
      .setDepth(100);

    // key landmarks in world px, drawn as colored dots over the tile map
    this.minimap = new Minimap(this, level, this.player, [
      { x: HOUSE_POS.x + TILE, y: HOUSE_POS.y + TILE, color: 0xffd166 },
      { x: SHOP_POS.x, y: SHOP_POS.y, color: 0xfde047 },
      { x: NPC_POS.x, y: NPC_POS.y, color: 0x8ecbff },
      { x: CAVE_POS.x, y: CAVE_POS.y, color: 0xff5555 },
      { x: FOREST_POS.x, y: FOREST_POS.y, color: 0x4ade80 },
    ]);

    this.nightOverlay = this.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH, GAME_HEIGHT, 0x1a1a4a, 1)
      .setScrollFactor(0)
      .setDepth(90)
      .setAlpha(0);

    this.hud = new StatusHud(this);

    this.quitConfirmText = this.add
      .text(GAME_WIDTH / 2, GAME_HEIGHT / 2, "", retroStyle(8, "#ff5555"))
      .setOrigin(0.5)
      .setScrollFactor(0)
      .setDepth(300)
      .setVisible(false);

    this.events.once(Phaser.Scenes.Events.SHUTDOWN, () => {
      GameState.pos = { x: this.player.x, y: this.player.y };
      GameState.save();
      this.dialogue.destroy();
      this.shop.destroy();
      this.inventory.destroy();
      this.bestiary.destroy();
      this.minimap.destroy();
      hint.destroy();
      this.quitConfirmText.destroy();
    });
  }

  private buildHomeBubble(): Phaser.GameObjects.Container {
    const lines = ["HOME", "Z: REST - FULL HP/MP", "SLEEP UNTIL MORNING"];
    const text = this.add
      .text(0, 0, lines.join("\n"), retroStyle(5, "#f5f5f5"))
      .setOrigin(0.5)
      .setAlign("center")
      .setLineSpacing(4);
    const pad = 20;
    const w = text.width + pad * 2;
    const h = text.height + pad * 2;
    const border = this.add.rectangle(0, 0, w + 8, h + 8, 0xffffff).setOrigin(0.5);
    const box = this.add.rectangle(0, 0, w, h, 0x0b0b2b).setOrigin(0.5);
    const tail = this.add
      .triangle(0, h / 2 + 4, -24, 0, 24, 0, 0, 28, 0x0b0b2b)
      .setStrokeStyle(2, 0xffffff)
      .setOrigin(0.5);
    return this.add
      .container(
        HOUSE_POS.x + TILE,
        HOUSE_POS.y + TILE - h / 2 - 32,
        [border, box, text, tail]
      )
      .setDepth(12);
  }

  private nearHouse(): boolean {
    const dx = this.player.x - (HOUSE_POS.x + TILE);
    const dy = this.player.y - (HOUSE_POS.y + 2 * TILE);
    return dx * dx + dy * dy <= 144 * 144;
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
    if (this.enteringDungeon) return;
    this.enteringDungeon = true;
    Sfx.night();
    this.player.setVelocity(0, 0);
    this.cameras.main.fadeOut(200, 0, 0, 0);
    this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
      this.scene.start("Dungeon");
    });
  }

  private enterForest(): void {
    if (this.enteringForest) return;
    this.enteringForest = true;
    Sfx.night();
    this.player.setVelocity(0, 0);
    this.cameras.main.fadeOut(200, 0, 0, 0);
    this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
      this.scene.start("Forest");
    });
  }

  // resets forestOverlapActive once the player is a full tile clear of the
  // entrance, so stepping back in re-triggers the forest zone
  private updateForestGate(): void {
    if (!this.forestOverlapActive) return;
    if (
      Math.abs(this.player.x - FOREST_POS.x) > TILE ||
      Math.abs(this.player.y - FOREST_POS.y) > TILE
    ) {
      this.forestOverlapActive = false;
    }
  }

  // true while a modal panel owns input — every place that checks this must
  // use this method instead of listing the panels itself, or a newly added
  // panel silently stops blocking (this happened once already: overlap
  // callbacks kept a stale copy of this check and missed BestiaryUI).
  private uiBlocking(): boolean {
    return (
      this.dialogue.isActive() ||
      this.shop.isActive() ||
      this.inventory.isActive() ||
      this.bestiary.isActive()
    );
  }

  update(_time: number, delta: number): void {
    GameState.minutes += delta / 1000;
    this.updateStatus();
    this.updateDayNight();
    this.updateHomeBubble();
    this.updateForestGate();
    this.minimap.update();

    if (this.gCheatQueued) {
      this.gCheatQueued = false;
      GameState.gainGold(100);
      GameState.save();
      this.flashNote("+100G (CHEAT)");
    }

    if (this.sQueued) {
      this.sQueued = false;
      this.toggleStatus();
    }

    if (this.ctrlSQueued) {
      this.ctrlSQueued = false;
      GameState.save();
    }

    if (this.mQueued) {
      this.mQueued = false;
      const muted = Sfx.toggleMuted();
      showToast(this, muted ? "SOUND: OFF" : "SOUND: ON", STATUS_HUD_TOAST_Y);
    }

    if (this.qQueued) {
      this.qQueued = false;
      if (!this.uiBlocking() && !this.enteringDungeon) {
        this.quitConfirm = true;
        this.quitConfirmText.setText("QUIT TO TITLE? Y/N").setVisible(true);
        Sfx.error();
      }
    }

    if (this.quitConfirm) {
      this.player.setVelocity(0, 0);
      this.player.anims.stop();
      this.dust.emitting = false;
      this.zQueued = this.ctrlSQueued = this.iQueued = this.gCheatQueued = this.mQueued = this.bQueued = this.tQueued = false;
      if (this.yQueued) {
        this.yQueued = false;
        this.quitConfirm = false;
        this.quitConfirmText.setVisible(false);
        // the SHUTDOWN handler saves pos + state, so this is save-and-quit
        this.scene.start("Title");
        return;
      }
      if (this.nQueued || this.escQueued) {
        this.nQueued = false;
        this.escQueued = false;
        this.quitConfirm = false;
        this.quitConfirmText.setVisible(false);
      }
      return;
    }

    if (this.tQueued) {
      this.tQueued = false;
      if (!this.uiBlocking()) this.minimap.toggle();
    }

    if (this.uiBlocking()) {
      this.zQueued = false;
      if (this.iQueued) {
        this.iQueued = false;
        if (this.inventory.isActive()) this.inventory.close();
      }
      if (this.bQueued) {
        this.bQueued = false;
        if (this.bestiary.isActive()) this.bestiary.close();
      }
      this.player.setVelocity(0, 0);
      this.player.anims.stop();
      this.dust.emitting = false;
      this.dialogue.update();
      this.shop.update();
      this.inventory.update();
      this.bestiary.update();
      this.updateRoamers(delta);
      return;
    }

    if (this.iQueued) {
      this.iQueued = false;
      this.inventory.open();
      return;
    }

    if (this.bQueued) {
      this.bQueued = false;
      this.bestiary.open();
      return;
    }

    if (this.zQueued) {
      this.zQueued = false;
      if (this.tryTalk()) return;
    }

    let vx = 0;
    let vy = 0;
    if (this.keyLeft.isDown || this.keyH.isDown) vx = -240;
    else if (this.keyRight.isDown || this.keyL.isDown) vx = 240;
    if (this.keyUp.isDown || this.keyK.isDown) vy = -240;
    else if (this.keyDown.isDown || this.keyJ.isDown) vy = 240;

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

    this.playerShadow.setPosition(this.player.x, this.player.y + 28);
    this.dust.emitting = moving;
    this.updateEquipOverlays();
    this.updateRoamers(delta);
    this.checkEncounter(delta);
  }

  private flashNote(text: string): void {
    const n = this.add
      .text(this.player.x, this.player.y - 52, text, retroStyle(6, "#ffd166"))
      .setOrigin(0.5)
      .setDepth(120);
    this.tweens.add({
      targets: n,
      y: n.y - 40,
      alpha: 0,
      duration: 900,
      onComplete: () => n.destroy(),
    });
  }

  private updateEquipOverlays(): void {
    this.weaponOverlay.setVisible(!!GameState.equipped.weapon);
    this.shieldOverlay.setVisible(!!GameState.equipped.armor);
    this.weaponOverlay.setTexture(GameState.weaponTexture());
    this.shieldOverlay.setTexture(GameState.armorTexture());
    const flip = this.lastMove === "left";
    this.weaponOverlay.setFlipX(flip);
    this.shieldOverlay.setFlipX(flip);
    this.weaponOverlay.setPosition(this.player.x + 14, this.player.y + 4);
    this.shieldOverlay.setPosition(this.player.x - 14, this.player.y + 8);
  }

  private toggleStatus(): void {
    const visible = !this.hud.isVisible();
    this.hud.setVisible(visible);
    GameState.hudVisible = visible;
    GameState.saveSettings();
  }

  private updateDayNight(): void {
    const factor = nightFactor();
    this.nightOverlay.setAlpha(factor * 0.45);
    this.fireflies.emitting = factor > 0.05;
    this.fireflies.setAlpha(factor);
  }

  private updateStatus(): void {
    this.hud.update();
  }

  private tryTalk(): boolean {
    const near = (x: number, y: number): boolean => {
      const dx = this.player.x - x;
      const dy = this.player.y - y;
      return dx * dx + dy * dy <= 120 * 120;
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
    if (near(this.guardPos.x, this.guardPos.y)) {
      const q = GameState.quest;
      this.dialogue.start(
        q.bossDefeated
          ? ["The path to the forest", "is open. Be wary of", "the MOSS GOLEM!"]
          : ["The forest is sealed.", "Defeat the KING SLIME", "first!"],
        "GUARD"
      );
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
      GameState.player.hp = GameState.effMaxHp();
      GameState.player.mp = GameState.player.maxMp;
      GameState.minutes = (Math.floor(GameState.minutes / 1440) + 1) * 1440 + 360;
      GameState.save();
      this.hud.forceRefresh();
      this.cameras.main.fadeIn(400, 0, 0, 0);
      this.resting = false;
      const note = this.add
        .text(GAME_WIDTH / 2, GAME_HEIGHT / 2, "RESTED! HP/MP FULL", retroStyle(8, "#ffd166"))
        .setOrigin(0.5)
        .setScrollFactor(0)
        .setDepth(120);
      this.tweens.add({
        targets: note,
        y: GAME_HEIGHT / 2 - 60,
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
      GameState.gainGold(30);
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
      GameState.gainGold(100);
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
    if (!q.forestBoss) {
      this.dialogue.start(
        [
          "The eastern woods hold",
          "a deeper threat now.",
          "The GUARD by the woods",
          "knows more.",
        ],
        "ELDER"
      );
      return;
    }
    if (!q.forestReward) {
      q.forestReward = true;
      GameState.gainGold(200);
      GameState.inventory.mythrilSword += 1;
      Sfx.buy();
      this.dialogue.start(
        [
          "The forest is at peace!",
          "Take this 200 gold and",
          "a MYTHRIL SWORD!",
        ],
        "ELDER"
      );
      return;
    }
    if (!q.bestiaryReward && allSpeciesCaught(GameState.caught)) {
      q.bestiaryReward = true;
      GameState.gainGold(500);
      GameState.inventory.elixir += 3;
      GameState.inventory.mythrilShield += 1;
      Sfx.buy();
      this.dialogue.start(
        [
          "You caught every beast",
          "in the realm! A feat no",
          "hero has matched.",
          "500 gold, 3 ELIXIRS and",
          "a MYTHRIL SHIELD!",
        ],
        "ELDER"
      );
      return;
    }
    if (!q.bestiaryReward) {
      const caught = CATCHABLE.filter((e) => GameState.caught.includes(e.name)).length;
      this.dialogue.start(
        [
          "The forest is at peace.",
          `You have caught ${caught} of`,
          `${CATCHABLE.length} beasts. Catch them`,
          "all and I will reward you!",
        ],
        "ELDER"
      );
      return;
    }
    this.dialogue.start(["The realm owes you", "everything, hero."], "ELDER");
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

  private escapeMonsterZone(): void {
    const spot = escapeFromZones(
      MONSTER_ZONES,
      this.player.x,
      this.player.y,
      (tx, ty) => {
        const tile = this.layer.getTileAt(tx, ty);
        return !!tile && !SOLID.has(tile.index);
      }
    );
    if (spot) this.player.setPosition(spot.x, spot.y);
  }

  private spawnMonsters(): void {
    this.roamerGroup = this.physics.add.group();
    for (const zone of MONSTER_ZONES) {
      const signX = zone.cx - zone.w / 2 - 32;
      this.add.image(signX, zone.cy, "sign").setDepth(9);
      const bang = this.add
        .text(signX, zone.cy - 64, "!", retroStyle(10, "#ffdd44"))
        .setOrigin(0.5)
        .setStroke("#7c2d12", 2)
        .setDepth(11);
      this.tweens.add({
        targets: bang,
        y: zone.cy - 84,
        duration: 420,
        yoyo: true,
        repeat: -1,
        ease: "Sine.easeInOut",
      });

      const kind: "slime" | "wolf" = zone.kind === "wolf" ? "wolf" : "slime";
      for (let i = 0; i < zone.count; i++) {
        const x = zone.cx + (Math.random() - 0.5) * zone.w * 0.6;
        const y = zone.cy + (Math.random() - 0.5) * zone.h * 0.6;
        const sprite = this.roamerGroup.create(
          x,
          y,
          kind
        ) as Phaser.Physics.Arcade.Sprite;
        sprite.setDepth(10);
        sprite.body?.setSize(40, 24).setOffset(12, 32);
        this.roamers.push({
          sprite,
          minX: zone.cx - zone.w / 2 + 8,
          maxX: zone.cx + zone.w / 2 - 8,
          minY: zone.cy - zone.h / 2 + 8,
          maxY: zone.cy + zone.h / 2 - 8,
          targetX: x,
          targetY: y,
          wait: 300 + Math.random() * 800,
          speed: 56 + Math.random() * 40,
          kind,
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

    if (Math.random() < TROLL_KING_SPAWN_CHANCE) {
      const zone = MONSTER_ZONES[Math.floor(Math.random() * MONSTER_ZONES.length)];
      const x = zone.cx + (Math.random() - 0.5) * zone.w * 0.6;
      const y = zone.cy + (Math.random() - 0.5) * zone.h * 0.6;
      const sprite = this.roamerGroup.create(x, y, "troll") as Phaser.Physics.Arcade.Sprite;
      sprite.setDepth(10).setScale(1.6);
      sprite.body?.setSize(40, 24).setOffset(12, 32);
      this.roamers.push({
        sprite,
        minX: zone.cx - zone.w / 2 + 8,
        maxX: zone.cx + zone.w / 2 - 8,
        minY: zone.cy - zone.h / 2 + 8,
        maxY: zone.cy + zone.h / 2 - 8,
        targetX: x,
        targetY: y,
        wait: 300 + Math.random() * 800,
        speed: 44 + Math.random() * 24,
        kind: "troll",
      });
      this.tweens.add({
        targets: sprite,
        scaleX: 1.72,
        scaleY: 1.48,
        duration: 280,
        yoyo: true,
        repeat: -1,
        ease: "Sine.easeInOut",
      });
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

  private startBattle(enemy?: "slime" | "goblin" | "troll" | "wolf"): void {
    if (this.encounterCooldown > 0) return; // already fading into a battle
    this.player.setVelocity(0, 0);
    this.encounterCooldown = ENCOUNTER_COOLDOWN;
    this.cameras.main.fadeOut(300, 0, 0, 0);
    this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
      const roll = Math.random();
      const kind = enemy ?? (roll < 0.4 ? "slime" : roll < 0.75 ? "goblin" : "wolf");
      this.scene.start("Battle", { enemy: kind, from: "World" });
    });
  }

  private animateWater(): void {
    this.layer.forEachTile((tile) => {
      if (tile.index === T_WATER_A) tile.index = T_WATER_B;
      else if (tile.index === T_WATER_B) tile.index = T_WATER_A;
    });
  }
}