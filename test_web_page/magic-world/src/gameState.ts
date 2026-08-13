export interface PlayerState {
  name: string;
  level: number;
  exp: number;
  hp: number;
  maxHp: number;
  mp: number;
  maxMp: number;
  atk: number;
  def: number;
}

export interface InventoryState {
  potion: number;
  mPotion: number;
  candy: number;
}

export interface QuestState {
  slimes: number;
  slimeReward: boolean;
  bossDefeated: boolean;
  finalReward: boolean;
}

const SAVE_KEY = "magic-world-save";

export const expToNext = (level: number): number => 10 + level * 10;

export function hour(): number {
  return Math.floor(GameState.minutes / 60) % 24;
}

export function minute(): number {
  return Math.floor(GameState.minutes) % 60;
}

export function clock(): string {
  return `${String(hour()).padStart(2, "0")}:${String(minute()).padStart(2, "0")}`;
}

export function dayCount(): number {
  return Math.floor(GameState.minutes / 1440) + 1;
}

export function isNight(): boolean {
  const h = hour();
  return h < 6 || h >= 20;
}

export function timeLabel(): string {
  return isNight() ? "NIGHT" : "DAY";
}

export const GameState = {
  player: {
    name: "HERO",
    level: 1,
    exp: 0,
    hp: 30,
    maxHp: 30,
    mp: 10,
    maxMp: 10,
    atk: 6,
    def: 2,
  } as PlayerState,
  gold: 0,
  battles: 0,
  inventory: { potion: 2, mPotion: 1, candy: 0 } as InventoryState,
  sword: false,
  shield: false,
  caught: [] as string[],
  quest: { slimes: 0, slimeReward: false, bossDefeated: false, finalReward: false } as QuestState,
  minutes: 360,
  pos: undefined as { x: number; y: number } | undefined,
  encounterLockUntil: 0,

  lockEncounters(ms: number): void {
    this.encounterLockUntil = Date.now() + ms;
  },
  encountersLocked(): boolean {
    return Date.now() < this.encounterLockUntil;
  },

  effAtk(): number {
    return this.player.atk + (this.sword ? 2 : 0);
  },
  effDef(): number {
    return this.player.def + (this.shield ? 2 : 0);
  },

  reset(): void {
    this.player = {
      name: "HERO",
      level: 1,
      exp: 0,
      hp: 30,
      maxHp: 30,
      mp: 10,
      maxMp: 10,
      atk: 6,
      def: 2,
    };
    this.gold = 0;
    this.battles = 0;
    this.inventory = { potion: 2, mPotion: 1, candy: 0 };
    this.sword = false;
    this.shield = false;
    this.caught = [];
    this.quest = { slimes: 0, slimeReward: false, bossDefeated: false, finalReward: false };
    this.minutes = 360;
    this.pos = undefined;
    this.encounterLockUntil = 0;
  },

  hasSave(): boolean {
    return localStorage.getItem(SAVE_KEY) !== null;
  },

  save(): void {
    localStorage.setItem(
      SAVE_KEY,
      JSON.stringify({
        player: this.player,
        gold: this.gold,
        battles: this.battles,
        inventory: this.inventory,
        sword: this.sword,
        shield: this.shield,
        caught: this.caught,
        quest: this.quest,
        minutes: this.minutes,
        pos: this.pos,
      })
    );
  },

  load(): void {
    const raw = localStorage.getItem(SAVE_KEY);
    if (!raw) return;
    try {
      const data = JSON.parse(raw);
      Object.assign(this.player, data.player);
      this.gold = data.gold ?? 0;
      this.battles = data.battles ?? 0;
      Object.assign(this.inventory, data.inventory);
      this.sword = data.sword ?? false;
      this.shield = data.shield ?? false;
      this.caught = data.caught ?? [];
      Object.assign(this.quest, data.quest);
      this.minutes = data.minutes ?? 360;
      this.pos = data.pos;
    } catch {
      this.clearSave();
    }
  },

  clearSave(): void {
    localStorage.removeItem(SAVE_KEY);
  },
};
