import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { makeTexture, makeTilesetTexture } from "../pixelart";

const GRASS_PALETTE = { g: 0x1f5c42, G: 0x16432f, L: 0x2a6b4d };
const GRASS_TILE = [
  "gggggggggggggggg",
  "gggggggggggggggg",
  "gGgggggggggGgggg",
  "gggggggggggggggg",
  "gggggLgggggggggg",
  "gggggggggggggggg",
  "gGgggggggggggGgg",
  "gggggggggggggggg",
  "gggggggggLgggggg",
  "gggggGgggggggggg",
  "gggggggggggggggg",
  "gggggggggLgggggg",
  "gggggggggggggggg",
  "gGgggggggggggggg",
  "gggggggggggggLgg",
  "gggggggggggggggg",
];

const WATER_PALETTE = { W: 0x0133a9, B: 0x01207f };
const WATER_A = [
  "WWWWWWWWWWWWWWWW",
  "WWWWWWWWWWWWWWWW",
  "WWBBWWWWWWWWBBWW",
  "WWWWWWWWWWWWWWWW",
  "WWWWWWBBWWWWWWWW",
  "WWWWWWWWWWWWWWWW",
  "BBWWWWWWWWWWWWWW",
  "WWWWWWWWWWWWWWWW",
  "WWWWWWBBWWWWBBWW",
  "WWWWWWWWWWWWWWWW",
  "WWBBWWWWWWWWWWWW",
  "WWWWWWWWWWWWWWWW",
  "WWWWWWWWWWWWWWWW",
  "WWBBWWWWWWWWBBWW",
  "WWWWWWWWWWWWWWWW",
  "WWWWWWWWWWWWWWWW",
];
const WATER_B = [
  "WWWWWWWWWWWWWWWW",
  "WWBBWWWWWWBBWWWW",
  "WWWWWWWWWWWWWWWW",
  "WWWWWWBBWWWWWWWW",
  "WWWWWWWWWWWWWWWW",
  "BBWWWWWWWWWWWWWW",
  "WWWWWWWWWWWWWWWW",
  "WWWWWWBBWWWWBBWW",
  "WWWWWWWWWWWWWWWW",
  "WWBBWWWWWWWWWWWW",
  "WWWWWWWWWWWWWWWW",
  "WWWWWWWWWWWWWWWW",
  "WWBBWWWWWWWWBBWW",
  "WWWWWWWWWWWWWWWW",
  "WWWWWWWWWWWWWWWW",
  "WWBBWWWWWWWWWWWW",
];

const TREE_PALETTE = { b: 0x0a331f, d: 0x0d4528, L: 0x155e38, t: 0x3d2c18 };
const TREE_TILE = [
  "bbbbbbbbbbbbbbbb",
  "bbbbbbbbbbbbbbbb",
  "bbbbLddddddLbbbb",
  "bbbddddddddddbbb",
  "bbddddddddddddbb",
  "bbddddddddddddbb",
  "bddddddddddddddb",
  "bddddddddddddddb",
  "bddddddddddddddb",
  "bbddddddddddddbb",
  "bbbbddddddddbbbb",
  "bbbbbbttttbbbbbb",
  "bbbbbbttttbbbbbb",
  "bbbbbbttttbbbbbb",
  "bbbbbttttttbbbbb",
  "bbbbbbbbbbbbbbbb",
];

const PATH_PALETTE = { p: 0x735f43, P: 0x5e4c33 };
const PATH_TILE = [
  "pppppppppppppppp",
  "pppppppppppppppp",
  "pppPPppppppPPppp",
  "pppppppppppppppp",
  "pppppppPPppppppp",
  "pppppppppppppppp",
  "pPPppppppppppppp",
  "pppppppppppppppp",
  "pppppppppPPppppp",
  "pppppppppppppppp",
  "pppPPppppppPPppp",
  "pppppppppppppppp",
  "pppppppppppppppp",
  "pppppPPppppppppp",
  "pppppppppppppppp",
  "pppppppppppppppp",
];

const TALL_PALETTE = { g: 0x185137, d: 0x113f2a, h: 0x2a6b4d };
const TALL_TILE = [
  "gggggggggggggggg",
  "gdhgggggdhgggggg",
  "gggggggggggggdhg",
  "gdgggggggggggggg",
  "gggggdhggggggggg",
  "gggggggggggdhggg",
  "gdgggggggggggggg",
  "gggggdhggggggggg",
  "gggggggggggggdhg",
  "gdhggggggggggggg",
  "gggggggggdhggggg",
  "gggggggggggggggg",
  "ggdhgggggggggggg",
  "gggggggggggggdhg",
  "gdhggggggggggggg",
  "gggggggggggggggg",
];

const HOUSE_TILE_PALETTE = { s: 0x3d3650, d: 0x322c42 };
const HOUSE_TILE = [
  "ssssssssssssssss",
  "ssssssssssssssss",
  "ssdssssssssdssss",
  "ssssssssssssssss",
  "ssssssdsssssssss",
  "ssssssssssssssss",
  "ssdssssssssssdss",
  "ssssssssssssssss",
  "sssssssssdssssss",
  "sssssdssssssssss",
  "ssssssssssssssss",
  "sssssssssdssssss",
  "ssssssssssssssss",
  "ssdsssssssssssss",
  "sssssssssssssdss",
  "ssssssssssssssss",
];

const HERO_PALETTE = {
  h: 0x6b4226,
  s: 0xf8c896,
  e: 0x141414,
  t: 0x3b6ef0,
  b: 0x8a5a2b,
  p: 0x2f3a56,
  o: 0x4a2f1a,
};

const HERO_HEAD = [
  "................",
  "................",
  ".....hhhhhh.....",
  "....hhhhhhhh....",
  "...hhhhhhhhhh...",
  "...hssssssssh...",
  "...hseesseesh...",
  "...hssssssssh...",
  "....hhhhhhhh....",
];
const HERO_TORSO = [
  ".....tttttt.....",
  "....tttttttt....",
  "...ttbbbbbbtt...",
];

const HERO_UP_HEAD = [
  "................",
  "................",
  ".....hhhhhh.....",
  "....hhhhhhhh....",
  "...hhhhhhhhhh...",
  "...hhhhhhhhhh...",
  "...hhhhhhhhhh...",
  "...hhhhhhhhhh...",
  "....hhhhhhhh....",
];

const HERO_SIDE_HEAD = [
  "................",
  "................",
  ".....hhhhhh.....",
  "....hhhhhhhh....",
  "...hhhhhhhhhh...",
  "...hssssssssss..",
  "...hsssssseess..",
  "...hssssssssss..",
  "....hhhhhhhh....",
];

const HERO_LEGS_STRIDE_A = [
  "..s..pp..pp..s..",
  "...spp....pps...",
  "....ooo..ooo....",
  "................",
];
const HERO_LEGS_PASS_A = [
  "..s..pppppp..s..",
  "...spppppppps...",
  "....oooooooo....",
  "................",
];
const HERO_LEGS_STRIDE_B = [
  "..s..pp..pp..s..",
  "....ppp..ppp....",
  "....ooo..ooo....",
  "................",
];
const HERO_LEGS_PASS_B = [
  "....pppppppp....",
  "...spppppppps...",
  "....oooooooo....",
  "................",
];
const HERO_LEGS_IDLE = [
  "..s..pppppp..s..",
  "..s..pppppp..s..",
  "..oo.oooooo.oo..",
  "................",
];

const NPC_PALETTE = {
  h: 0xf59e0b,
  s: 0xf8c896,
  e: 0x141414,
  b: 0xe5e7eb,
  r: 0x7c3aed,
  R: 0x6d28d9,
};
const NPC_TILE = [
  "................",
  ".....hhhhhh.....",
  "....hhhhhhhh....",
  "...hhhhhhhhhh...",
  "...hssssssssh...",
  "...hseesseesh...",
  "...hbbbbbbbbh...",
  "....rrrrrrrr....",
  "...rrrrrrrrrr...",
  "...rrrrrrrrrr...",
  "...rrbbbbbbbrr..",
  "...rrrrrrrrrr...",
  "....rrrrrrrr....",
  "....rrrr..rr....",
  "................",
  "................",
];

const SLIME_PALETTE = { g: 0x4ade80, G: 0x1c5c38, m: 0x14532d };
const SLIME_TILE = [
  "................",
  "................",
  "................",
  ".....gggggg.....",
  "....gggggggg....",
  "...gggggggggg...",
  "..gggggggggggg..",
  "..gggggggggggg..",
  "..gggGggggGggg..",
  "..gggggggggggg..",
  "..ggmgggggmggg..",
  "...gggggggggg...",
  "....gggggggg....",
  ".....gggggg.....",
  "................",
  "................",
];

const GOBLIN_PALETTE = {
  s: 0x86efac,
  S: 0x5bb97e,
  e: 0xff5555,
  h: 0x4ade80,
  r: 0x8b5a2b,
};
const GOBLIN_TILE = [
  "................",
  "................",
  ".....hh..hh.....",
  "....hsssssssh...",
  "...hssssssssh...",
  "...hsSseesSsh...",
  "...hssssssssh...",
  "....hssssssh....",
  "....ssssssss....",
  "...ssssssssss...",
  "...ssrrrrrrss...",
  "...ssrrrrrrss...",
  "....ssssssss....",
  "....ss....ss....",
  "................",
  "................",
];

function makeCave(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x2a2a3a, 1);
  g.fillRect(0, 0, 64, 64);
  g.fillStyle(0x3d3650, 1);
  g.fillRect(0, 0, 64, 6);
  g.fillRect(0, 0, 6, 64);
  g.fillRect(58, 0, 6, 64);
  g.fillStyle(0x141418, 1);
  g.fillTriangle(8, 6, 32, 40, 56, 6);
  g.fillRect(10, 6, 44, 40);
  g.fillStyle(0x0b0b0e, 1);
  g.fillRect(10, 30, 44, 34);
  g.generateTexture("cave", 64, 64);
  g.destroy();
}

function makeSign(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x4a2f1a, 1);
  g.fillRect(12, 18, 8, 14);
  g.fillStyle(0x8a5a2b, 1);
  g.fillRect(2, 2, 28, 16);
  g.fillStyle(0x6d4a1f, 1);
  g.fillRect(2, 2, 28, 2);
  g.fillStyle(0x2a1f2e, 1);
  g.fillRect(14, 6, 4, 8);
  g.fillRect(14, 16, 4, 2);
  g.generateTexture("sign", 32, 32);
  g.destroy();
}

function makeHouse(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x8a2b3a, 1);
  g.fillRect(0, 12, 64, 16);
  g.fillStyle(0x6d2130, 1);
  g.fillRect(0, 12, 64, 4);
  g.fillStyle(0x453a52, 1);
  g.fillRect(2, 28, 60, 36);
  g.fillStyle(0x382e44, 1);
  g.fillRect(2, 28, 60, 4);
  g.fillStyle(0x2a1f2e, 1);
  g.fillRect(24, 40, 16, 24);
  g.fillStyle(0x171019, 1);
  g.fillRect(30, 50, 4, 14);
  g.fillStyle(0xffd672, 1);
  g.fillRect(8, 30, 12, 12);
  g.fillStyle(0xffd672, 0.3);
  g.fillRect(6, 28, 16, 16);
  g.fillStyle(0xffd672, 1);
  g.fillRect(44, 30, 12, 12);
  g.fillStyle(0xffd672, 0.3);
  g.fillRect(42, 28, 16, 16);
  g.generateTexture("house", 64, 64);
  g.destroy();
}

function makeMoon(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0xe8eaf8, 0.25);
  g.fillCircle(48, 48, 34);
  g.fillStyle(0xe8eaf8, 0.5);
  g.fillCircle(48, 48, 26);
  g.fillStyle(0xf6f6ff, 1);
  g.fillCircle(48, 48, 18);
  g.fillStyle(0xffffff, 1);
  g.fillCircle(48, 48, 12);
  g.generateTexture("moon", 96, 96);
  g.destroy();
}

function makeStars(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  for (let i = 0; i < 90; i++) {
    g.fillStyle(0xffffff, Math.random() * 0.8 + 0.2);
    g.fillRect(Math.floor(Math.random() * 640), Math.floor(Math.random() * 160), 2, 2);
  }
  g.generateTexture("stars", 640, 160);
  g.destroy();
}

function makeBattleBg(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x0133a9, 1);
  g.fillRect(0, 0, GAME_WIDTH, 120);
  g.fillStyle(0x0a38b8, 1);
  g.fillRect(0, 120, GAME_WIDTH, 80);
  g.fillStyle(0xe8eaf8, 0.18);
  g.fillCircle(120, 88, 80);
  g.fillStyle(0xf6f6ff, 0.4);
  g.fillCircle(120, 88, 36);
  g.fillStyle(0xffffff, 1);
  g.fillCircle(120, 88, 16);
  for (let i = 0; i < 30; i++) {
    g.fillStyle(0xffffff, Math.random() * 0.7 + 0.2);
    g.fillRect(Math.floor(Math.random() * GAME_WIDTH), Math.floor(Math.random() * 100), 2, 2);
  }
  g.fillStyle(0x261973, 1);
  g.fillTriangle(0, 220, 120, 120, 240, 220);
  g.fillTriangle(140, 220, 320, 80, 500, 220);
  g.fillTriangle(400, 220, 580, 130, 640, 220);
  g.fillStyle(0x1a1240, 1);
  g.fillRect(0, 220, GAME_WIDTH, GAME_HEIGHT - 220);
  g.fillStyle(0x372a52, 1);
  g.fillRect(0, 220, GAME_WIDTH, 8);
  g.fillStyle(0x1f5c42, 1);
  g.fillRect(0, 228, GAME_WIDTH, 12);
  g.generateTexture("battle-bg", GAME_WIDTH, GAME_HEIGHT);
  g.destroy();
}

function makeTitleBg(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x0133a9, 1);
  g.fillRect(0, 0, GAME_WIDTH, GAME_HEIGHT);

  g.fillStyle(0xe8eaf8, 0.15);
  g.fillCircle(160, 92, 112);
  g.fillStyle(0xf6f6ff, 0.28);
  g.fillCircle(160, 92, 76);
  g.fillStyle(0xf6f6ff, 1);
  g.fillCircle(160, 92, 32);
  g.fillStyle(0xffffff, 1);
  g.fillCircle(160, 92, 22);
  g.fillStyle(0xd9ddf2, 1);
  g.fillCircle(150, 82, 6);
  g.fillCircle(170, 100, 4);
  g.fillCircle(156, 104, 3);

  for (let i = 0; i < 45; i++) {
    g.fillStyle(0xffffff, Math.random() * 0.8 + 0.2);
    g.fillRect(Math.floor(Math.random() * GAME_WIDTH), Math.floor(Math.random() * 200), 2, 2);
  }

  g.fillStyle(0x261973, 1);
  g.fillTriangle(-40, 240, 120, 120, 300, 240);
  g.fillTriangle(180, 240, 400, 140, 640, 240);
  g.fillStyle(0x17235a, 1);
  g.fillTriangle(40, 280, 220, 180, 380, 280);
  g.fillTriangle(300, 280, 500, 190, 680, 280);

  g.fillStyle(0x1a1240, 1);
  g.fillRect(280, 236, 52, 44);
  g.fillRect(344, 244, 68, 36);
  g.fillStyle(0x8a2b3a, 1);
  g.fillTriangle(276, 236, 306, 208, 336, 236);
  g.fillTriangle(340, 244, 378, 216, 416, 244);
  g.fillStyle(0xffd672, 1);
  g.fillRect(292, 248, 12, 14);
  g.fillRect(356, 256, 12, 14);
  g.fillRect(384, 252, 12, 14);

  g.fillStyle(0x1a1240, 1);
  g.fillRect(536, 192, 28, 48);
  g.fillStyle(0x8a2b3a, 1);
  g.fillTriangle(524, 192, 550, 164, 576, 192);
  g.fillStyle(0xffd672, 1);
  g.fillRect(542, 200, 8, 10);
  g.fillRect(542, 218, 8, 10);
  g.fillStyle(0xff8a3d, 1);
  g.fillCircle(550, 156, 8);
  g.fillStyle(0xffd672, 0.6);
  g.fillCircle(550, 156, 14);
  g.fillStyle(0xff5555, 0.4);
  g.fillCircle(550, 156, 20);

  g.fillStyle(0x0e5226, 1);
  g.fillCircle(40, 332, 32);
  g.fillCircle(96, 340, 40);
  g.fillCircle(160, 316, 26);
  g.fillCircle(240, 336, 36);
  g.fillCircle(480, 328, 30);
  g.fillCircle(600, 340, 44);
  g.fillStyle(0x0f6a2a, 1);
  g.fillCircle(108, 324, 18);
  g.fillCircle(252, 320, 14);
  g.fillCircle(612, 324, 18);
  g.fillStyle(0x081b12, 1);
  g.fillRect(0, 336, GAME_WIDTH, 24);
  g.generateTexture("title-bg", GAME_WIDTH, GAME_HEIGHT);
  g.destroy();
}

export class BootScene extends Phaser.Scene {
  constructor() {
    super("Boot");
  }

  create(): void {
    this.buildTextures();
    this.scene.start("Title");
  }

  private buildTextures(): void {
    makeTilesetTexture(
      this,
      "tiles16",
      [
        { rows: GRASS_TILE, palette: GRASS_PALETTE },
        { rows: WATER_A, palette: WATER_PALETTE },
        { rows: WATER_B, palette: WATER_PALETTE },
        { rows: TREE_TILE, palette: TREE_PALETTE },
        { rows: PATH_TILE, palette: PATH_PALETTE },
        { rows: TALL_TILE, palette: TALL_PALETTE },
        { rows: HOUSE_TILE, palette: HOUSE_TILE_PALETTE },
      ],
      16
    );

    const flipRows = (rows: string[]): string[] =>
      rows.map((r) => [...r].reverse().join(""));

    const walkFrames = [
      HERO_LEGS_STRIDE_A,
      HERO_LEGS_PASS_A,
      HERO_LEGS_STRIDE_B,
      HERO_LEGS_PASS_B,
    ];
    for (let i = 0; i < walkFrames.length; i++) {
      const legs = walkFrames[i];
      makeTexture(this, `hero-down-${i}`, [...HERO_HEAD, ...HERO_TORSO, ...legs], HERO_PALETTE);
      makeTexture(this, `hero-up-${i}`, [...HERO_UP_HEAD, ...HERO_TORSO, ...legs], HERO_PALETTE);
      makeTexture(this, `hero-right-${i}`, [...HERO_SIDE_HEAD, ...HERO_TORSO, ...legs], HERO_PALETTE);
      makeTexture(
        this,
        `hero-left-${i}`,
        [...flipRows(HERO_SIDE_HEAD), ...HERO_TORSO, ...legs],
        HERO_PALETTE
      );
    }

    makeTexture(this, "hero-idle-down", [...HERO_HEAD, ...HERO_TORSO, ...HERO_LEGS_IDLE], HERO_PALETTE);
    makeTexture(this, "hero-idle-up", [...HERO_UP_HEAD, ...HERO_TORSO, ...HERO_LEGS_IDLE], HERO_PALETTE);
    makeTexture(
      this,
      "hero-idle-right",
      [...HERO_SIDE_HEAD, ...HERO_TORSO, ...HERO_LEGS_IDLE],
      HERO_PALETTE
    );
    makeTexture(
      this,
      "hero-idle-left",
      [...flipRows(HERO_SIDE_HEAD), ...HERO_TORSO, ...HERO_LEGS_IDLE],
      HERO_PALETTE
    );

    makeTexture(this, "npc", NPC_TILE, NPC_PALETTE);
    makeTexture(this, "slime", SLIME_TILE, SLIME_PALETTE);
    makeTexture(this, "goblin", GOBLIN_TILE, GOBLIN_PALETTE);

    makeTexture(this, "dust", ["dd", "dd"], { d: 0xcbbfa8 });

    makeHouse(this);
    makeSign(this);
    makeMoon(this);
    makeStars(this);
    makeCave(this);
    makeBattleBg(this);
    makeTitleBg(this);
  }
}