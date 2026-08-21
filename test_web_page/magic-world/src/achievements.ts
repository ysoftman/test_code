import { GameState } from "./gameState";
import { FOREST_TREASURE_POS, TREASURE_POS } from "./levels";
import { CATCHABLE } from "./monsters";

// Total chests across the dungeon (3) and the forest (4) — the number the
// treasure-hunter achievement keys off, so adding a chest to either map is a
// one-line update here instead of a drift-prone literal.
export const TOTAL_TREASURES = TREASURE_POS.length + FOREST_TREASURE_POS.length;

export interface AchievementDef {
  id: string;
  name: string;
  desc: string;
  check: () => boolean;
}

// Each check reads live GameState, so claimAchievements() can be called from
// anywhere after a state mutation (battle win, fish catch, chest open) and
// only the ids that newly became true are returned for the caller to toast.
export const ACHIEVEMENTS: AchievementDef[] = [
  {
    id: "first-blood",
    name: "FIRST BLOOD",
    desc: "Win your first battle",
    check: () => GameState.battles >= 1,
  },
  {
    id: "veteran",
    name: "VETERAN",
    desc: "Win 10 battles",
    check: () => GameState.battles >= 10,
  },
  {
    id: "hot-streak",
    name: "HOT STREAK",
    desc: "Win 3 battles in a row",
    check: () => GameState.streak >= 3,
  },
  {
    id: "unstoppable",
    name: "UNSTOPPABLE",
    desc: "Win 8 battles in a row",
    check: () => GameState.streak >= 8,
  },
  {
    id: "angler",
    name: "ANGLER",
    desc: "Catch your first fish",
    check: () => GameState.fishCaught >= 1,
  },
  {
    id: "fishmaster",
    name: "FISHMASTER",
    desc: "Catch 10 fish",
    check: () => GameState.fishCaught >= 10,
  },
  {
    id: "goldbag",
    name: "GOLDBAG",
    desc: "Hold 100 gold at once",
    check: () => GameState.gold >= 100,
  },
  {
    id: "treasure-hunter",
    name: "TREASURE HUNTER",
    desc: "Open every treasure chest",
    check: () => GameState.openedTreasures.length >= TOTAL_TREASURES,
  },
  {
    id: "collector",
    name: "COLLECTOR",
    desc: "Catch every catchable monster",
    check: () => CATCHABLE.every((def) => GameState.caught.includes(def.name)),
  },
  {
    id: "boss-slayer",
    name: "BOSS SLAYER",
    desc: "Defeat the KING SLIME",
    check: () => GameState.quest.bossDefeated,
  },
  {
    id: "golden-hunter",
    name: "GOLDEN HUNTER",
    desc: "Defeat a GOLDEN SLIME",
    check: () => GameState.quest.goldenSlimes >= 1,
  },
  {
    id: "golem-breaker",
    name: "GOLEM BREAKER",
    desc: "Defeat the MOSS GOLEM",
    check: () => GameState.quest.forestBoss,
  },
  {
    id: "legend",
    name: "LEGEND",
    desc: "Reach level 10",
    check: () => GameState.player.level >= 10,
  },
];

// Returns the ids of achievements that the current state newly satisfies.
export function claimAchievements(): string[] {
  const earned: string[] = [];
  for (const a of ACHIEVEMENTS) {
    if (GameState.achievements.includes(a.id)) continue;
    if (a.check()) {
      GameState.achievements.push(a.id);
      earned.push(a.id);
    }
  }
  return earned;
}
