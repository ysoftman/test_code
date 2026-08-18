// Village rank board: a persistent top-10 leaderboard of level-ups, stored in
// its own localStorage key so it survives "new game" / delete-save — the board
// in town records every hero, not just the current run.

export interface RankEntry {
  name: string;
  level: number;
  date: string; // YYYY-MM-DD when the level was reached
}

const RANK_KEY = "magic-world-ranking";
export const MAX_RANKS = 10;

let ranks: RankEntry[] = loadRanks();

function loadRanks(): RankEntry[] {
  try {
    const raw = localStorage.getItem(RANK_KEY);
    if (!raw) return [];
    const parsed: unknown = JSON.parse(raw);
    if (!Array.isArray(parsed)) return [];
    return parsed
      .filter(
        (e): e is RankEntry =>
          !!e &&
          typeof (e as RankEntry).name === "string" &&
          typeof (e as RankEntry).level === "number" &&
          typeof (e as RankEntry).date === "string"
      )
      .sort(byLevel);
  } catch {
    return [];
  }
}

function byLevel(a: RankEntry, b: RankEntry): number {
  if (b.level !== a.level) return b.level - a.level;
  // same level: whoever reached it first ranks higher
  return a.date < b.date ? -1 : a.date > b.date ? 1 : 0;
}

function today(): string {
  const d = new Date();
  const pad = (n: number): string => String(n).padStart(2, "0");
  return `${d.getFullYear()}-${pad(d.getMonth() + 1)}-${pad(d.getDate())}`;
}

export function getRanks(): RankEntry[] {
  return ranks.slice();
}

// Records a level-up on the board. Returns the 1-based rank the entry earned
// (0 when the level didn't crack the top 10).
export function recordRank(name: string, level: number): number {
  const entry: RankEntry = { name, level, date: today() };
  ranks.push(entry);
  ranks.sort(byLevel);
  ranks = ranks.slice(0, MAX_RANKS);
  try {
    localStorage.setItem(RANK_KEY, JSON.stringify(ranks));
  } catch {
    /* storage full/blocked: the board still works for this session */
  }
  const idx = ranks.indexOf(entry);
  return idx >= 0 ? idx + 1 : 0;
}
