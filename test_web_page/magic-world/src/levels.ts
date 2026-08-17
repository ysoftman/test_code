export const TILE = 64;

export const T_GRASS = 0;
export const T_WATER_A = 1;
export const T_WATER_B = 2;
export const T_TREE = 3;
export const T_PATH = 4;
export const T_TALL = 5;
export const T_HOUSE = 6;

export const MAP_W = 32;
export const MAP_H = 24;

export const SOLID = new Set<number>([T_WATER_A, T_WATER_B, T_TREE, T_HOUSE]);
export const TALL_GRASS = T_TALL;

export interface MonsterZone {
  cx: number;
  cy: number;
  w: number;
  h: number;
  count: number;
  kind?: "slime" | "goblin" | "wolf" | "bat";
}

export const MONSTER_ZONES: MonsterZone[] = [
  { cx: 4 * TILE, cy: 14 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3 },
  { cx: 18 * TILE, cy: 13 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3 },
  { cx: 10 * TILE, cy: 20 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3 },
  { cx: 26 * TILE, cy: 8 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3, kind: "wolf" },
  { cx: 27 * TILE, cy: 17.5 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3, kind: "wolf" },
  { cx: 21.5 * TILE, cy: 3.5 * TILE, w: 2 * TILE, h: 2 * TILE, count: 2 },
];

// Battle ends leave the hero standing where the fight started — inside the
// monster zone, so the post-battle encounter lock expiring right there pulls
// them straight into another fight. This finds the nearest walkable tile
// outside every zone (within `maxTiles` tiles) for the scene to teleport to.
export function escapeFromZones(
  zones: MonsterZone[],
  x: number,
  y: number,
  walkable: (tx: number, ty: number) => boolean,
  maxTiles = 6
): { x: number; y: number } | null {
  // Clearance from the zone edge: half a tile, so the hero's 40x32 body
  // never reaches back into the zone (or into the dungeon exit trigger).
  const pad = TILE * 0.5;
  const inZone = (px: number, py: number, p: number): boolean =>
    zones.some(
      (z) =>
        Math.abs(px - z.cx) <= z.w / 2 + p &&
        Math.abs(py - z.cy) <= z.h / 2 + p
    );
  if (!inZone(x, y, TILE * 0.25)) return null;
  let best: { x: number; y: number; d: number } | null = null;
  const cx = Math.floor(x / TILE);
  const cy = Math.floor(y / TILE);
  for (let ty = cy - maxTiles; ty <= cy + maxTiles; ty++) {
    for (let tx = cx - maxTiles; tx <= cx + maxTiles; tx++) {
      const wx = tx * TILE + TILE / 2;
      const wy = ty * TILE + TILE / 2;
      if (inZone(wx, wy, pad)) continue;
      if (!walkable(tx, ty)) continue;
      const d = Math.hypot(wx - x, wy - y);
      if (!best || d < best.d) best = { x: wx, y: wy, d };
    }
  }
  return best ? { x: best.x, y: best.y } : null;
}

const CHARS: Record<string, number> = {
  G: T_GRASS,
  W: T_WATER_A,
  T: T_TREE,
  P: T_PATH,
  h: T_TALL,
  H: T_HOUSE,
};

function stamp(map: number[][], x0: number, y0: number, rows: string[]): void {
  for (let y = 0; y < rows.length; y++) {
    for (let x = 0; x < rows[y].length; x++) {
      const c = CHARS[rows[y][x]];
      if (c === undefined) continue;
      const tx = x0 + x;
      const ty = y0 + y;
      if (tx >= 0 && tx < MAP_W && ty >= 0 && ty < MAP_H) map[ty][tx] = c;
    }
  }
}

export function buildLevel(): number[][] {
  const map: number[][] = Array.from({ length: MAP_H }, () =>
    Array<number>(MAP_W).fill(T_GRASS)
  );

  for (let x = 0; x < MAP_W; x++) {
    map[0][x] = T_WATER_A;
    map[MAP_H - 1][x] = T_WATER_A;
  }
  for (let y = 0; y < MAP_H; y++) {
    map[y][0] = T_WATER_A;
    map[y][MAP_W - 1] = T_WATER_A;
  }

  stamp(map, 3, 2, ["HH", "HH"]);
  stamp(map, 1, 7, ["PPPPPPPPPPPPPPPPPPPPPPPP"]);
  stamp(map, 7, 3, ["P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P"]);
  stamp(map, 5, 7, ["P", "P"]);
  stamp(map, 3, 13, ["hh", "hh"]);
  stamp(map, 17, 12, ["hh", "hh"]);
  stamp(map, 6, 4, [".T.", "TTT"]);
  stamp(map, 15, 5, [".T.", "TTT"]);
  stamp(map, 18, 9, ["T.T", ".T."]);
  stamp(map, 12, 2, ["T"]);

  stamp(map, 25, 4, ["WWWW", "WWWW", "WWWW"]);
  stamp(map, 25, 7, ["hhh", "hhh", "hhh"]);
  stamp(map, 21, 3, ["hh", "hh"]);
  stamp(map, 24, 8, ["P", "P", "P", "P"]);
  stamp(map, 27, 2, [".T.", "TTT"]);
  stamp(map, 29, 6, ["T"]);
  stamp(map, 22, 12, ["T.T", ".T."]);
  stamp(map, 29, 12, ["T.T", ".T."]);
  stamp(map, 26, 14, ["T"]);
  stamp(map, 30, 15, [".T.", "TTT"]);

  stamp(map, 7, 14, ["P", "P", "P", "P", "P", "P", "P", "P"]);
  stamp(map, 9, 19, ["hhhh", "hhhh"]);
  stamp(map, 26, 17, ["hhh", "hhh"]);
  stamp(map, 2, 17, ["T"]);
  stamp(map, 6, 16, [".T.", "TTT"]);
  stamp(map, 14, 21, ["TTT", ".T."]);
  stamp(map, 20, 20, [".T.", "TTT"]);
  stamp(map, 5, 22, ["TT", ".."]);
  stamp(map, 16, 17, ["T"]);
  stamp(map, 11, 15, ["T"]);

  return map;
}

export const PLAYER_SPAWN = { x: 9 * TILE + TILE / 2, y: 7 * TILE + TILE / 2 };
export const NPC_POS = { x: 11 * TILE + TILE / 2, y: 7 * TILE + TILE / 2 };
export const HOUSE_POS = { x: 3 * TILE, y: 2 * TILE };
export const SHOP_POS = { x: 5 * TILE + TILE / 2, y: 7 * TILE + TILE / 2 };
export const CAVE_POS = { x: 19 * TILE + TILE / 2, y: 2 * TILE + TILE / 2 };

export const DUNGEON_W = 24;
export const DUNGEON_H = 16;
export const DUNGEON_ENTRY = { x: 10 * TILE + TILE / 2, y: 1 * TILE + TILE / 2 };

export const DUNGEON_ZONES: MonsterZone[] = [
  { cx: 4 * TILE, cy: 5 * TILE, w: 3 * TILE, h: 2 * TILE, count: 3 },
  { cx: 15 * TILE, cy: 6 * TILE, w: 3 * TILE, h: 2 * TILE, count: 3 },
  { cx: 10 * TILE, cy: 12 * TILE, w: 3 * TILE, h: 2 * TILE, count: 1 },
  { cx: 11 * TILE, cy: 3 * TILE, w: 3 * TILE, h: 2 * TILE, count: 3, kind: "bat" },
  { cx: 21 * TILE, cy: 10 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3, kind: "bat" },
  { cx: 4 * TILE, cy: 12 * TILE, w: 2 * TILE, h: 2 * TILE, count: 2, kind: "bat" },
];

export const TREASURE_POS: Array<{ id: string; x: number; y: number }> = [
  { id: "dungeon-1", x: 7 * TILE + TILE / 2, y: 4 * TILE + TILE / 2 },
  { id: "dungeon-2", x: 17 * TILE + TILE / 2, y: 10 * TILE + TILE / 2 },
  { id: "dungeon-3", x: 22 * TILE + TILE / 2, y: 12 * TILE + TILE / 2 },
];

export function buildDungeon(): number[][] {
  const map: number[][] = Array.from({ length: DUNGEON_H }, () =>
    Array<number>(DUNGEON_W).fill(T_PATH)
  );

  for (let x = 0; x < DUNGEON_W; x++) {
    map[0][x] = T_TREE;
    map[DUNGEON_H - 1][x] = T_TREE;
  }
  for (let y = 0; y < DUNGEON_H; y++) {
    map[y][0] = T_TREE;
    map[y][DUNGEON_W - 1] = T_TREE;
  }

  stamp(map, 1, 2, ["WWW", "WWW"]);
  stamp(map, 14, 2, ["WWW", "WWW", "WWW"]);
  stamp(map, 2, 9, ["WWW", "WWW"]);
  stamp(map, 15, 9, ["WW", "WW", "WW"]);

  stamp(map, 8, 4, ["TT", "..", ".."]);
  stamp(map, 4, 7, [".T", "T."]);

  for (let x = 6; x <= 13; x++) {
    if (x === 9 || x === 10) continue; // doorway down into the boss room
    map[10][x] = T_TREE;
  }
  map[11][6] = T_TREE;
  map[12][6] = T_TREE;
  map[11][13] = T_TREE;
  map[12][13] = T_TREE;

  stamp(map, 21, 4, ["WW", "WW", "WW"]);
  stamp(map, 19, 5, [".T", "TT"]);
  stamp(map, 19, 13, ["TT"]);
  stamp(map, 21, 12, ["T"]);
  stamp(map, 3, 14, ["T.", ".T"]);
  stamp(map, 17, 14, ["TT"]);
  stamp(map, 20, 2, ["T"]);
  stamp(map, 23, 12, ["T", "T"]);

  return map;
}
