export interface EnemyDef {
  name: string;
  texture: string;
  hp: number;
  atk: number;
  def: number;
  exp: number;
  gold: number;
  boss?: boolean; // story boss (KING SLIME, MOSS GOLEM): quest flag, uncatchable, boss dialogue
  giant?: boolean; // just a bigger sprite + boss fanfare, no quest/story hooks
  rare?: boolean; // rare world jackpot (GOLDEN SLIME): tinted, big payout, not required for collection
  tint?: number; // sprite tint applied in the world and in battle (e.g. gold for GOLDEN SLIME)
}

export const ENEMIES: Record<string, EnemyDef> = {
  slime: { name: "SLIME", texture: "slime", hp: 16, atk: 5, def: 0, exp: 8, gold: 5 },
  goldSlime: {
    name: "GOLDEN SLIME",
    texture: "slime",
    tint: 0xffd700,
    hp: 28,
    atk: 6,
    def: 1,
    exp: 40,
    gold: 60,
    rare: true, // rare world jackpot: big payout, not required for collection
  },
  goblin: { name: "GOBLIN", texture: "goblin", hp: 22, atk: 7, def: 1, exp: 14, gold: 9 },
  bat: { name: "BAT", texture: "bat", hp: 18, atk: 6, def: 0, exp: 12, gold: 8 },
  wolf: { name: "WOLF", texture: "wolf", hp: 30, atk: 9, def: 1, exp: 25, gold: 15 },
  king: {
    name: "KING SLIME",
    texture: "king",
    hp: 60,
    atk: 9,
    def: 2,
    exp: 80,
    gold: 120,
    boss: true,
  },
  troll: {
    name: "TROLL KING",
    texture: "troll",
    hp: 90,
    atk: 13,
    def: 3,
    exp: 150,
    gold: 200,
    giant: true,
  },
  wasp: { name: "WASP", texture: "wasp", hp: 28, atk: 9, def: 1, exp: 22, gold: 14 },
  spider: { name: "SPIDER", texture: "spider", hp: 40, atk: 11, def: 2, exp: 34, gold: 22 },
  orc: { name: "ORC", texture: "orc", hp: 52, atk: 13, def: 3, exp: 50, gold: 34 },
  mossGolem: {
    name: "MOSS GOLEM",
    texture: "mossGolem",
    hp: 140,
    atk: 15,
    def: 5,
    exp: 220,
    gold: 300,
    boss: true, // FOREST story boss: same flag/uncatchable path as KING SLIME
  },
};

// Bosses can't be caught (throwCandy refuses them), and rare monsters are a
// bonus jackpot — not required — so bestiary completion is measured against
// this list, not every entry in ENEMIES.
export const CATCHABLE = Object.values(ENEMIES).filter((e) => !e.boss && !e.rare);

export function allSpeciesCaught(caught: string[]): boolean {
  return CATCHABLE.every((e) => caught.includes(e.name));
}
