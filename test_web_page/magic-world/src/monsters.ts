export interface EnemyDef {
  name: string;
  texture: string;
  hp: number;
  atk: number;
  def: number;
  exp: number;
  gold: number;
  boss?: boolean; // the KING SLIME story boss: quest flag, uncatchable, boss dialogue
  giant?: boolean; // just a bigger sprite + boss fanfare, no quest/story hooks
}

export const ENEMIES: Record<string, EnemyDef> = {
  slime: { name: "SLIME", texture: "slime", hp: 16, atk: 5, def: 0, exp: 8, gold: 5 },
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
};
