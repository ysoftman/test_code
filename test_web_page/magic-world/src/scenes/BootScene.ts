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

const TREE_PALETTE = { d: 0x0d4528, t: 0x3d2c18 };
const TREE_TILE = [
  "................",
  "................",
  ".....dddddd.....",
  "...dddddddddd...",
  "..dddddddddddd..",
  "..dddddddddddd..",
  ".dddddddddddddd.",
  ".dddddddddddddd.",
  ".dddddddddddddd.",
  "..dddddddddddd..",
  "....dddddddd....",
  "......tttt......",
  "......tttt......",
  "......tttt......",
  ".....tttttt.....",
  "................",
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
  "...hseessssssss.",
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

function makeSign(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x4a2f1a, 1);
  g.fillRect(6, 9, 4, 7);
  g.fillStyle(0x8a5a2b, 1);
  g.fillRect(1, 1, 14, 8);
  g.fillStyle(0x6d4a1f, 1);
  g.fillRect(1, 1, 14, 1);
  g.fillStyle(0x2a1f2e, 1);
  g.fillRect(7, 3, 2, 4);
  g.fillRect(7, 8, 2, 1);
  g.generateTexture("sign", 16, 16);
  g.destroy();
}

function makeHouse(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x8a2b3a, 1);
  g.fillRect(0, 6, 32, 8);
  g.fillStyle(0x6d2130, 1);
  g.fillRect(0, 6, 32, 2);
  g.fillStyle(0x453a52, 1);
  g.fillRect(1, 14, 30, 18);
  g.fillStyle(0x382e44, 1);
  g.fillRect(1, 14, 30, 2);
  g.fillStyle(0x2a1f2e, 1);
  g.fillRect(12, 20, 8, 12);
  g.fillStyle(0x171019, 1);
  g.fillRect(15, 25, 2, 7);
  g.fillStyle(0xffd672, 1);
  g.fillRect(4, 15, 6, 6);
  g.fillStyle(0xffd672, 0.3);
  g.fillRect(3, 14, 8, 8);
  g.fillStyle(0xffd672, 1);
  g.fillRect(22, 15, 6, 6);
  g.fillStyle(0xffd672, 0.3);
  g.fillRect(21, 14, 8, 8);
  g.generateTexture("house", 32, 32);
  g.destroy();
}

function makeMoon(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0xe8eaf8, 0.25);
  g.fillCircle(24, 24, 17);
  g.fillStyle(0xe8eaf8, 0.5);
  g.fillCircle(24, 24, 13);
  g.fillStyle(0xf6f6ff, 1);
  g.fillCircle(24, 24, 9);
  g.fillStyle(0xffffff, 1);
  g.fillCircle(24, 24, 6);
  g.generateTexture("moon", 48, 48);
  g.destroy();
}

function makeStars(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  for (let i = 0; i < 90; i++) {
    g.fillStyle(0xffffff, Math.random() * 0.8 + 0.2);
    g.fillRect(Math.floor(Math.random() * 320), Math.floor(Math.random() * 80), 1, 1);
  }
  g.generateTexture("stars", 320, 80);
  g.destroy();
}

function makeBattleBg(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x0133a9, 1);
  g.fillRect(0, 0, GAME_WIDTH, 60);
  g.fillStyle(0x0a38b8, 1);
  g.fillRect(0, 60, GAME_WIDTH, 40);
  g.fillStyle(0xe8eaf8, 0.18);
  g.fillCircle(60, 44, 40);
  g.fillStyle(0xf6f6ff, 0.4);
  g.fillCircle(60, 44, 18);
  g.fillStyle(0xffffff, 1);
  g.fillCircle(60, 44, 8);
  for (let i = 0; i < 30; i++) {
    g.fillStyle(0xffffff, Math.random() * 0.7 + 0.2);
    g.fillRect(Math.floor(Math.random() * GAME_WIDTH), Math.floor(Math.random() * 50), 1, 1);
  }
  g.fillStyle(0x261973, 1);
  g.fillTriangle(0, 110, 60, 60, 120, 110);
  g.fillTriangle(70, 110, 160, 40, 250, 110);
  g.fillTriangle(200, 110, 290, 65, 320, 110);
  g.fillStyle(0x1a1240, 1);
  g.fillRect(0, 110, GAME_WIDTH, GAME_HEIGHT - 110);
  g.fillStyle(0x372a52, 1);
  g.fillRect(0, 110, GAME_WIDTH, 4);
  g.fillStyle(0x1f5c42, 1);
  g.fillRect(0, 114, GAME_WIDTH, 6);
  g.generateTexture("battle-bg", GAME_WIDTH, GAME_HEIGHT);
  g.destroy();
}

function makeTitleBg(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x0133a9, 1);
  g.fillRect(0, 0, GAME_WIDTH, GAME_HEIGHT);

  g.fillStyle(0xe8eaf8, 0.15);
  g.fillCircle(80, 46, 56);
  g.fillStyle(0xf6f6ff, 0.28);
  g.fillCircle(80, 46, 38);
  g.fillStyle(0xf6f6ff, 1);
  g.fillCircle(80, 46, 16);
  g.fillStyle(0xffffff, 1);
  g.fillCircle(80, 46, 11);
  g.fillStyle(0xd9ddf2, 1);
  g.fillCircle(75, 41, 3);
  g.fillCircle(85, 50, 2);
  g.fillCircle(78, 52, 1.5);

  for (let i = 0; i < 45; i++) {
    g.fillStyle(0xffffff, Math.random() * 0.8 + 0.2);
    g.fillRect(Math.floor(Math.random() * GAME_WIDTH), Math.floor(Math.random() * 100), 1, 1);
  }

  g.fillStyle(0x261973, 1);
  g.fillTriangle(-20, 120, 60, 60, 150, 120);
  g.fillTriangle(90, 120, 200, 70, 320, 120);
  g.fillStyle(0x17235a, 1);
  g.fillTriangle(20, 140, 110, 90, 190, 140);
  g.fillTriangle(150, 140, 250, 95, 340, 140);

  g.fillStyle(0x1a1240, 1);
  g.fillRect(140, 118, 26, 22);
  g.fillRect(172, 122, 34, 18);
  g.fillStyle(0x8a2b3a, 1);
  g.fillTriangle(138, 118, 153, 104, 168, 118);
  g.fillTriangle(170, 122, 189, 108, 208, 122);
  g.fillStyle(0xffd672, 1);
  g.fillRect(146, 124, 6, 7);
  g.fillRect(178, 128, 6, 7);
  g.fillRect(192, 126, 6, 7);

  g.fillStyle(0x1a1240, 1);
  g.fillRect(268, 96, 14, 24);
  g.fillStyle(0x8a2b3a, 1);
  g.fillTriangle(262, 96, 275, 82, 288, 96);
  g.fillStyle(0xffd672, 1);
  g.fillRect(271, 100, 4, 5);
  g.fillRect(271, 109, 4, 5);
  g.fillStyle(0xff8a3d, 1);
  g.fillCircle(275, 78, 4);
  g.fillStyle(0xffd672, 0.6);
  g.fillCircle(275, 78, 7);
  g.fillStyle(0xff5555, 0.4);
  g.fillCircle(275, 78, 10);

  g.fillStyle(0x0e5226, 1);
  g.fillCircle(20, 166, 16);
  g.fillCircle(48, 170, 20);
  g.fillCircle(80, 158, 13);
  g.fillCircle(120, 168, 18);
  g.fillCircle(240, 164, 15);
  g.fillCircle(300, 170, 22);
  g.fillStyle(0x0f6a2a, 1);
  g.fillCircle(54, 162, 9);
  g.fillCircle(126, 160, 7);
  g.fillCircle(306, 162, 9);
  g.fillStyle(0x081b12, 1);
  g.fillRect(0, 168, GAME_WIDTH, 12);
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
    makeBattleBg(this);
    makeTitleBg(this);
  }
}