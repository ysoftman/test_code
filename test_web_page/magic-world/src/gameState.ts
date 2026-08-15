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
  hiPotion: number;
  ether: number;
  elixir: number;
  bomb: number;
  sword: number;
  shield: number;
  ironSword: number;
  ironShield: number;
  amulet: number;
}

export type EquipSlot = "weapon" | "armor" | "accessory";
export type EquipmentKey = "sword" | "shield" | "ironSword" | "ironShield" | "amulet";

export const EQUIP_SLOT: Record<EquipmentKey, EquipSlot> = {
  sword: "weapon",
  ironSword: "weapon",
  shield: "armor",
  ironShield: "armor",
  amulet: "accessory",
};

export interface QuestState {
  slimes: number;
  slimeReward: boolean;
  bossDefeated: boolean;
  finalReward: boolean;
}

const SAVE_KEY = "magic-world-save";
const SETTINGS_KEY = "magic-world-settings";

const saveListeners: Array<() => void> = [];

// Lets scenes show a "SAVED" toast without GameState.save() needing any
// reference to a Phaser scene. Returns an unsubscribe function.
export function onSaved(callback: () => void): () => void {
  saveListeners.push(callback);
  return () => {
    const i = saveListeners.indexOf(callback);
    if (i >= 0) saveListeners.splice(i, 1);
  };
}

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

export function nightFactor(): number {
  const h = hour() + minute() / 60;
  if (h >= 6.0 && h < 19.5) return 0;
  if (h >= 20.0 || h < 5.5) return 1;
  if (h < 6.0) return 1 - (h - 5.5) / 0.5;
  return (h - 19.5) / 0.5;
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
  inventory: {
    potion: 2,
    mPotion: 1,
    candy: 0,
    hiPotion: 0,
    ether: 0,
    elixir: 0,
    bomb: 0,
    sword: 0,
    shield: 0,
    ironSword: 0,
    ironShield: 0,
    amulet: 0,
  } as InventoryState,
  equipped: { weapon: null, armor: null, accessory: null } as Record<EquipSlot, EquipmentKey | null>,
  caught: [] as string[],
  seenMonsters: [] as string[],
  openedTreasures: [] as string[],
  quest: { slimes: 0, slimeReward: false, bossDefeated: false, finalReward: false } as QuestState,
  minutes: 360,
  pos: undefined as { x: number; y: number } | undefined,
  encounterLockUntil: 0,
  hudVisible: true,
  soundMuted: false,

  lockEncounters(ms: number): void {
    this.encounterLockUntil = Date.now() + ms;
  },
  encountersLocked(): boolean {
    return Date.now() < this.encounterLockUntil;
  },

  effMaxHp(): number {
    return this.player.maxHp + (this.equipped.accessory === "amulet" ? 10 : 0);
  },
  effAtk(): number {
    return (
      this.player.atk +
      (this.equipped.weapon === "sword" ? 2 : 0) +
      (this.equipped.weapon === "ironSword" ? 4 : 0)
    );
  },
  effDef(): number {
    return (
      this.player.def +
      (this.equipped.armor === "shield" ? 2 : 0) +
      (this.equipped.armor === "ironShield" ? 4 : 0)
    );
  },
  isEquipped(key: EquipmentKey): boolean {
    return this.equipped[EQUIP_SLOT[key]] === key;
  },
  equipToggle(key: EquipmentKey): string {
    const slot = EQUIP_SLOT[key];
    if (this.isEquipped(key)) {
      this.unequip(slot);
      return "Unequipped!";
    }
    const before = this.effMaxHp();
    this.setEquipped(slot, key);
    // preserve the HP the amulet's +maxHp bonus grants, without letting
    // repeated equip/unequip toggles net-heal (the bonus isn't tracked
    // separately from maxHp, so clamping alone would keep adding it back)
    this.player.hp = Math.min(this.effMaxHp(), this.player.hp + (this.effMaxHp() - before));
    return "Equipped!";
  },
  setEquipped(slot: EquipSlot, key: EquipmentKey): void {
    this.equipped[slot] = key;
  },
  unequip(slot: EquipSlot): void {
    const key = this.equipped[slot];
    if (!key) return;
    const before = this.effMaxHp();
    this.equipped[slot] = null;
    this.player.hp = Math.max(1, Math.min(this.effMaxHp(), this.player.hp + (this.effMaxHp() - before)));
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
    this.inventory = {
      potion: 2,
      mPotion: 1,
      candy: 0,
      hiPotion: 0,
      ether: 0,
      elixir: 0,
      bomb: 0,
      sword: 0,
      shield: 0,
      ironSword: 0,
      ironShield: 0,
      amulet: 0,
    };
    this.equipped = { weapon: null, armor: null, accessory: null };
    this.caught = [];
    this.seenMonsters = [];
    this.openedTreasures = [];
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
        equipped: this.equipped,
        caught: this.caught,
        seenMonsters: this.seenMonsters,
        openedTreasures: this.openedTreasures,
        quest: this.quest,
        minutes: this.minutes,
        pos: this.pos,
        encounterLockUntil: this.encounterLockUntil,
      })
    );
    saveListeners.forEach((cb) => cb());
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
      // migrate old boolean equipment flags -> inventory counts + equipped
      if (data.sword && this.inventory.sword === 0) this.inventory.sword = 1;
      if (data.shield && this.inventory.shield === 0) this.inventory.shield = 1;
      this.equipped = data.equipped ?? {
        weapon: data.sword ? "sword" : null,
        armor: data.shield ? "shield" : null,
        accessory: null,
      };
      this.caught = data.caught ?? [];
      this.seenMonsters = data.seenMonsters ?? [];
      this.openedTreasures = data.openedTreasures ?? [];
      Object.assign(this.quest, data.quest);
      this.minutes = data.minutes ?? 360;
      this.pos = data.pos;
      this.encounterLockUntil = data.encounterLockUntil ?? 0;
    } catch {
      this.clearSave();
    }
  },

  // Display/audio preferences: kept in their own key, separate from the game
  // save, so they survive "new game" / delete-save and don't trigger the
  // "SAVED" toast that GameState.save() fires on every real progress save.
  loadSettings(): void {
    try {
      const raw = localStorage.getItem(SETTINGS_KEY);
      if (!raw) return;
      const s = JSON.parse(raw);
      this.hudVisible = s.hudVisible ?? true;
      this.soundMuted = s.soundMuted ?? false;
    } catch {
      /* keep defaults */
    }
  },
  saveSettings(): void {
    localStorage.setItem(
      SETTINGS_KEY,
      JSON.stringify({ hudVisible: this.hudVisible, soundMuted: this.soundMuted })
    );
  },

  clearSave(): void {
    localStorage.removeItem(SAVE_KEY);
  },
};
