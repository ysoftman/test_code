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

const EQUIP_SWORD_PALETTE = { w: 0xd1d5db, d: 0x64748b, g: 0xf59e0b, b: 0x6b4226 };
const EQUIP_SWORD_TILE = [
  "................",
  "................",
  "................",
  ".....wwww.......",
  ".....wwww.......",
  ".....wwww.......",
  ".....wwww.......",
  ".....wwww.......",
  ".....wwww.......",
  ".....wwww.......",
  ".....wwww.......",
  ".....wwww.......",
  ".....gggg.......",
  ".....bbbb.......",
  ".....bb.........",
  "................",
];

const EQUIP_SHIELD_PALETTE = { s: 0x94a3b8, S: 0x64748b, d: 0x475569 };
const EQUIP_SHIELD_TILE = [
  "................",
  "................",
  "................",
  "................",
  "....ssssssss....",
  "...ssssssssss...",
  "...sSSSSSSSSs...",
  "...sSSddddSSs...",
  "...sSSddddSSs...",
  "...sSSSSSSSSs...",
  "...ssssssssss...",
  "....ssssssss....",
  "................",
  "................",
  "................",
  "................",
];

const EQUIP_IRON_SWORD_PALETTE = { w: 0xe2e8f0, d: 0x334155, g: 0x60a5fa, b: 0x1e3a8a };
const EQUIP_IRON_SHIELD_PALETTE = { s: 0x60a5fa, S: 0x3b82f6, d: 0x1e3a8a };

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
const KING_SLIME_PALETTE = { g: 0xff7a7a, G: 0xb91c1c, m: 0x7f1d1d };
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
const TROLL_PALETTE = {
  s: 0x4d5d4d,
  S: 0x2f3a2f,
  e: 0xffd166,
  h: 0x1f2e1f,
  r: 0x7c2d12,
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

const SPARK_PALETTE = { y: 0xffdd44 };
const SPARK_TILE = [
  "..y.....",
  "..y.....",
  "..y.....",
  "yyyyyyyy",
  "..y.....",
  "..y.....",
  "..y.....",
  "........",
];

const GLOW_PALETTE = { g: 0x8ecbff, w: 0xffffff };
const GLOW_TILE = [
  "................",
  "......gggg......",
  "....ggwwwwgg....",
  "...ggwwwwwwgg...",
  "..ggwwwwwwwwgg..",
  "..gwwwwwwwwwwg..",
  ".gwwwwwwwwwwwwg.",
  ".gwwwwwwwwwwwwg.",
  ".gwwwwwwwwwwwwg.",
  ".gwwwwwwwwwwwwg.",
  "..gwwwwwwwwwwg..",
  "..ggwwwwwwwwgg..",
  "...ggwwwwwwgg...",
  "....ggwwwwgg....",
  "......gggg......",
  "................",
];

const COIN_PALETTE = { y: 0x8a5a2b, Y: 0xffd166, W: 0xfff3c4 };
const COIN_TILE = [
  "................",
  ".....yyyyyy.....",
  "...yyyYYYYyyy...",
  "..yyYYYYYYYYyy..",
  ".yyYYYYYYYYYYyy.",
  ".yYYYYYYYYYYYYy.",
  "yYYYWWYYYYWWYYYy",
  "yYYYWYYYYYYWYYYy",
  "yYYYYYYYYYYYYYYy",
  "yYYYYYYYYYYYYYYy",
  ".yYYYYYYYYYYYYy.",
  ".yyYYYYYYYYYYyy.",
  "..yyYYYYYYYYyy..",
  "...yyyYYYYyyy...",
  ".....yyyyyy.....",
  "................",
];

const FIREFLY_PALETTE = { w: 0xe9ff66 };
const FIREFLY_TILE = [
  "........",
  "........",
  "..ww....",
  ".wwww...",
  "..ww....",
  "........",
  "........",
  "........",
];

const CHEST_PALETTE = { b: 0x4a2f1a, w: 0x8a5a2b, L: 0xd1a455, l: 0x3d2c18, Y: 0xffd166 };
const CHEST_TILE = [
  "................",
  "................",
  "...bbbbbbbbbb...",
  "..bwwwwwwwwwwb..",
  ".bwwwwwwwwwwwwb.",
  ".bwLLLLLLLLLLwb.",
  ".bwLllllllllLwb.",
  ".bwLllllllllLwb.",
  ".bwLllllllllLwb.",
  ".bwLllllllllLwb.",
  ".bwLLLLLLLLLLwb.",
  ".bwwwwwwwwwwwwb.",
  "..bbbbbbbbbbbb..",
  "...bb......bb...",
  "................",
  "................",
];
const CHEST_OPEN_TILE = [
  "................",
  "..bbbbbbbbbbbb..",
  ".bbwwwwwwwwwwbb.",
  "................",
  "................",
  "...bwwwwwwwwwb..",
  "..bwYYYYYYYYYwb.",
  ".bwYYYYYYYYYYYwb",
  ".bwYYYYYYYYYYYwb",
  ".bwYYYYYYYYYYYwb",
  ".bwYYYYYYYYYYYwb",
  ".bwwwwwwwwwwwwb.",
  "..bbbbbbbbbbbb..",
  "...bb......bb...",
  "................",
  "................",
];

function makeCave(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x2a2a3a, 1);
  g.fillRect(0, 0, 128, 128);
  g.fillStyle(0x3d3650, 1);
  g.fillRect(0, 0, 128, 12);
  g.fillRect(0, 0, 12, 128);
  g.fillRect(116, 0, 12, 128);
  g.fillStyle(0x141418, 1);
  g.fillTriangle(16, 12, 64, 80, 112, 12);
  g.fillRect(20, 12, 88, 80);
  g.fillStyle(0x0b0b0e, 1);
  g.fillRect(20, 60, 88, 68);
  g.generateTexture("cave", 128, 128);
  g.destroy();
}

function makeSign(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x4a2f1a, 1);
  g.fillRect(24, 36, 16, 28);
  g.fillStyle(0x8a5a2b, 1);
  g.fillRect(4, 4, 56, 32);
  g.fillStyle(0x6d4a1f, 1);
  g.fillRect(4, 4, 56, 4);
  g.fillStyle(0x2a1f2e, 1);
  g.fillRect(28, 12, 8, 16);
  g.fillRect(28, 32, 8, 4);
  g.generateTexture("sign", 64, 64);
  g.destroy();
}

function makeHouse(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x8a2b3a, 1);
  g.fillRect(0, 24, 128, 32);
  g.fillStyle(0x6d2130, 1);
  g.fillRect(0, 24, 128, 8);
  g.fillStyle(0x453a52, 1);
  g.fillRect(4, 56, 120, 72);
  g.fillStyle(0x382e44, 1);
  g.fillRect(4, 56, 120, 8);
  g.fillStyle(0x2a1f2e, 1);
  g.fillRect(48, 80, 32, 48);
  g.fillStyle(0x171019, 1);
  g.fillRect(60, 100, 8, 28);
  g.fillStyle(0xffd672, 1);
  g.fillRect(16, 60, 24, 24);
  g.fillStyle(0xffd672, 0.3);
  g.fillRect(12, 56, 32, 32);
  g.fillStyle(0xffd672, 1);
  g.fillRect(88, 60, 24, 24);
  g.fillStyle(0xffd672, 0.3);
  g.fillRect(84, 56, 32, 32);
  g.generateTexture("house", 128, 128);
  g.destroy();
}

function makeMoon(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0xe8eaf8, 0.25);
  g.fillCircle(96, 96, 68);
  g.fillStyle(0xe8eaf8, 0.5);
  g.fillCircle(96, 96, 52);
  g.fillStyle(0xf6f6ff, 1);
  g.fillCircle(96, 96, 36);
  g.fillStyle(0xffffff, 1);
  g.fillCircle(96, 96, 24);
  g.generateTexture("moon", 192, 192);
  g.destroy();
}

function makeStars(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  for (let i = 0; i < 90; i++) {
    g.fillStyle(0xffffff, Math.random() * 0.8 + 0.2);
    g.fillRect(Math.floor(Math.random() * 1280), Math.floor(Math.random() * 320), 4, 4);
  }
  g.generateTexture("stars", 1280, 320);
  g.destroy();
}

function makeBattleBg(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x0133a9, 1);
  g.fillRect(0, 0, GAME_WIDTH, 240);
  g.fillStyle(0x0a38b8, 1);
  g.fillRect(0, 240, GAME_WIDTH, 160);
  g.fillStyle(0xe8eaf8, 0.18);
  g.fillCircle(240, 176, 160);
  g.fillStyle(0xf6f6ff, 0.4);
  g.fillCircle(240, 176, 72);
  g.fillStyle(0xffffff, 1);
  g.fillCircle(240, 176, 32);
  for (let i = 0; i < 30; i++) {
    g.fillStyle(0xffffff, Math.random() * 0.7 + 0.2);
    g.fillRect(Math.floor(Math.random() * GAME_WIDTH), Math.floor(Math.random() * 200), 4, 4);
  }
  g.fillStyle(0x261973, 1);
  g.fillTriangle(0, 440, 240, 240, 480, 440);
  g.fillTriangle(280, 440, 640, 160, 1000, 440);
  g.fillTriangle(800, 440, 1160, 260, 1280, 440);
  g.fillStyle(0x1a1240, 1);
  g.fillRect(0, 440, GAME_WIDTH, GAME_HEIGHT - 440);
  g.fillStyle(0x372a52, 1);
  g.fillRect(0, 440, GAME_WIDTH, 16);
  g.fillStyle(0x1f5c42, 1);
  g.fillRect(0, 456, GAME_WIDTH, 24);
  g.generateTexture("battle-bg", GAME_WIDTH, GAME_HEIGHT);
  g.destroy();
}

function makeTitleBg(scene: Phaser.Scene): void {
  const g = scene.add.graphics();
  g.fillStyle(0x0133a9, 1);
  g.fillRect(0, 0, GAME_WIDTH, GAME_HEIGHT);

  g.fillStyle(0xe8eaf8, 0.15);
  g.fillCircle(320, 184, 224);
  g.fillStyle(0xf6f6ff, 0.28);
  g.fillCircle(320, 184, 152);
  g.fillStyle(0xf6f6ff, 1);
  g.fillCircle(320, 184, 64);
  g.fillStyle(0xffffff, 1);
  g.fillCircle(320, 184, 44);
  g.fillStyle(0xd9ddf2, 1);
  g.fillCircle(300, 164, 12);
  g.fillCircle(340, 200, 8);
  g.fillCircle(312, 208, 6);

  for (let i = 0; i < 45; i++) {
    g.fillStyle(0xffffff, Math.random() * 0.8 + 0.2);
    g.fillRect(Math.floor(Math.random() * GAME_WIDTH), Math.floor(Math.random() * 400), 4, 4);
  }

  g.fillStyle(0x261973, 1);
  g.fillTriangle(-80, 480, 240, 240, 600, 480);
  g.fillTriangle(360, 480, 800, 280, 1280, 480);
  g.fillStyle(0x17235a, 1);
  g.fillTriangle(80, 560, 440, 360, 760, 560);
  g.fillTriangle(600, 560, 1000, 380, 1360, 560);

  g.fillStyle(0x1a1240, 1);
  g.fillRect(560, 472, 104, 88);
  g.fillRect(688, 488, 136, 72);
  g.fillStyle(0x8a2b3a, 1);
  g.fillTriangle(552, 472, 612, 416, 672, 472);
  g.fillTriangle(680, 488, 756, 432, 832, 488);
  g.fillStyle(0xffd672, 1);
  g.fillRect(584, 496, 24, 28);
  g.fillRect(712, 512, 24, 28);
  g.fillRect(768, 504, 24, 28);

  g.fillStyle(0x1a1240, 1);
  g.fillRect(1072, 384, 56, 96);
  g.fillStyle(0x8a2b3a, 1);
  g.fillTriangle(1048, 384, 1100, 328, 1152, 384);
  g.fillStyle(0xffd672, 1);
  g.fillRect(1084, 400, 16, 20);
  g.fillRect(1084, 436, 16, 20);
  g.fillStyle(0xff8a3d, 1);
  g.fillCircle(1100, 312, 16);
  g.fillStyle(0xffd672, 0.6);
  g.fillCircle(1100, 312, 28);
  g.fillStyle(0xff5555, 0.4);
  g.fillCircle(1100, 312, 40);

  g.fillStyle(0x0e5226, 1);
  g.fillCircle(80, 664, 64);
  g.fillCircle(192, 680, 80);
  g.fillCircle(320, 632, 52);
  g.fillCircle(480, 672, 72);
  g.fillCircle(960, 656, 60);
  g.fillCircle(1200, 680, 88);
  g.fillStyle(0x0f6a2a, 1);
  g.fillCircle(216, 648, 36);
  g.fillCircle(504, 640, 28);
  g.fillCircle(1224, 648, 36);
  g.fillStyle(0x081b12, 1);
  g.fillRect(0, 672, GAME_WIDTH, 48);
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

    makeTexture(this, "equip-sword", EQUIP_SWORD_TILE, EQUIP_SWORD_PALETTE);
    makeTexture(this, "equip-shield", EQUIP_SHIELD_TILE, EQUIP_SHIELD_PALETTE);
    makeTexture(this, "equip-iron-sword", EQUIP_SWORD_TILE, EQUIP_IRON_SWORD_PALETTE);
    makeTexture(this, "equip-iron-shield", EQUIP_SHIELD_TILE, EQUIP_IRON_SHIELD_PALETTE);

    makeTexture(this, "npc", NPC_TILE, NPC_PALETTE);
    makeTexture(this, "slime", SLIME_TILE, SLIME_PALETTE);
    makeTexture(this, "king", SLIME_TILE, KING_SLIME_PALETTE);
    makeTexture(this, "goblin", GOBLIN_TILE, GOBLIN_PALETTE);
    makeTexture(this, "troll", GOBLIN_TILE, TROLL_PALETTE);

    makeTexture(this, "dust", ["dd", "dd"], { d: 0xcbbfa8 });
    makeTexture(this, "spark", SPARK_TILE, SPARK_PALETTE);
    makeTexture(this, "glow", GLOW_TILE, GLOW_PALETTE);
    makeTexture(this, "coin", COIN_TILE, COIN_PALETTE);
    makeTexture(this, "firefly", FIREFLY_TILE, FIREFLY_PALETTE);
    makeTexture(this, "chest", CHEST_TILE, CHEST_PALETTE);
    makeTexture(this, "chest-open", CHEST_OPEN_TILE, CHEST_PALETTE);

    makeHouse(this);
    makeSign(this);
    makeMoon(this);
    makeStars(this);
    makeCave(this);
    makeBattleBg(this);
    makeTitleBg(this);
  }
}