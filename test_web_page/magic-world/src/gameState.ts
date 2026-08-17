import { MAX_GOLD, MAX_HP, MAX_LEVEL, MAX_MP } from "./config";

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
  mythrilSword: number;
  mythrilShield: number;
}

export type EquipSlot = "weapon" | "armor" | "accessory";
export type EquipmentKey =
  | "sword"
  | "shield"
  | "ironSword"
  | "ironShield"
  | "amulet"
  | "mythrilSword"
  | "mythrilShield";

export const EQUIP_SLOT: Record<EquipmentKey, EquipSlot> = {
  sword: "weapon",
  ironSword: "weapon",
  mythrilSword: "weapon",
  shield: "armor",
  ironShield: "armor",
  mythrilShield: "armor",
  amulet: "accessory",
};

// One table per equipment property, so adding a tier is one line each instead
// of a new branch in effAtk/effDef and in every scene's overlay code.
export const EQUIP_BONUS: Record<EquipmentKey, number> = {
  sword: 2,
  ironSword: 4,
  mythrilSword: 6,
  shield: 2,
  ironShield: 4,
  mythrilShield: 6,
  amulet: 0,
};

export const EQUIP_TEXTURE: Record<EquipmentKey, string> = {
  sword: "equip-sword",
  ironSword: "equip-iron-sword",
  mythrilSword: "equip-mythril-sword",
  shield: "equip-shield",
  ironShield: "equip-iron-shield",
  mythrilShield: "equip-mythril-shield",
  amulet: "equip-sword", // accessory: never drawn as an overlay
};

export interface QuestState {
  slimes: number;
  slimeReward: boolean;
  bossDefeated: boolean;
  finalReward: boolean;
  forestBoss: boolean;
  forestReward: boolean;
  bestiaryReward: boolean;
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
  streak: 0,
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
    mythrilSword: 0,
    mythrilShield: 0,
  } as InventoryState,
  equipped: { weapon: null, armor: null, accessory: null } as Record<EquipSlot, EquipmentKey | null>,
  caught: [] as string[],
  seenMonsters: [] as string[],
  openedTreasures: [] as string[],
  quest: {
    slimes: 0,
    slimeReward: false,
    bossDefeated: false,
    finalReward: false,
    forestBoss: false,
    forestReward: false,
    bestiaryReward: false,
  } as QuestState,
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
    return Math.min(MAX_HP, this.player.maxHp + (this.equipped.accessory === "amulet" ? 10 : 0));
  },
  gainGold(n: number): number {
    const added = Math.min(MAX_GOLD, this.gold + n) - this.gold;
    this.gold += added;
    return added;
  },
  effAtk(): number {
    return this.player.atk + (this.equipped.weapon ? EQUIP_BONUS[this.equipped.weapon] : 0);
  },
  effDef(): number {
    return this.player.def + (this.equipped.armor ? EQUIP_BONUS[this.equipped.armor] : 0);
  },
  weaponTexture(): string {
    return this.equipped.weapon ? EQUIP_TEXTURE[this.equipped.weapon] : "equip-sword";
  },
  armorTexture(): string {
    return this.equipped.armor ? EQUIP_TEXTURE[this.equipped.armor] : "equip-shield";
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
    this.streak = 0;
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
      mythrilSword: 0,
      mythrilShield: 0,
    };
    this.equipped = { weapon: null, armor: null, accessory: null };
    this.caught = [];
    this.seenMonsters = [];
    this.openedTreasures = [];
    this.quest = {
      slimes: 0,
      slimeReward: false,
      bossDefeated: false,
      finalReward: false,
      forestBoss: false,
      forestReward: false,
      bestiaryReward: false,
    };
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
        streak: this.streak,
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
      this.player.level = Math.min(MAX_LEVEL, this.player.level);
      this.player.maxHp = Math.min(MAX_HP, this.player.maxHp);
      this.player.maxMp = Math.min(MAX_MP, this.player.maxMp);
      this.gold = Math.min(MAX_GOLD, data.gold ?? 0);
      this.battles = data.battles ?? 0;
      this.streak = data.streak ?? 0;
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
