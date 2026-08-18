export const TILE = 64;

export const T_GRASS = 0;
export const T_WATER_A = 1;
export const T_WATER_B = 2;
export const T_TREE = 3;
export const T_PATH = 4;
export const T_TALL = 5;
export const T_HOUSE = 6;

export const MAP_W = 28;
export const MAP_H = 20;

export const SOLID = new Set<number>([T_WATER_A, T_WATER_B, T_TREE, T_HOUSE]);
export const TALL_GRASS = T_TALL;

export interface MonsterZone {
  cx: number;
  cy: number;
  w: number;
  h: number;
  count: number;
  kind?: "slime" | "goblin" | "wolf" | "bat" | "wasp" | "spider" | "orc";
}

export const MONSTER_ZONES: MonsterZone[] = [
  { cx: 4 * TILE, cy: 12 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3 },
  { cx: 17 * TILE, cy: 13 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3 },
  { cx: 10 * TILE, cy: 17 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3 },
  { cx: 24 * TILE, cy: 7 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3, kind: "wolf" },
  { cx: 23 * TILE, cy: 16 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3, kind: "wolf" },
  { cx: 21 * TILE, cy: 3 * TILE, w: 2 * TILE, h: 2 * TILE, count: 2 },
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

// Tall grass is how the map shows where monsters roam, so it is stamped from
// MONSTER_ZONES rather than positioned by hand — the two drifted apart when the
// map was resized and zones ended up marked in the wrong place, or not at all.
function markZones(map: number[][], zones: MonsterZone[]): void {
  for (const z of zones) {
    const x0 = Math.round((z.cx - z.w / 2) / TILE);
    const y0 = Math.round((z.cy - z.h / 2) / TILE);
    const x1 = Math.round((z.cx + z.w / 2) / TILE);
    const y1 = Math.round((z.cy + z.h / 2) / TILE);
    for (let ty = y0; ty < y1; ty++) {
      for (let tx = x0; tx < x1; tx++) {
        if (tx >= 0 && tx < map[0].length && ty >= 0 && ty < map.length) map[ty][tx] = T_TALL;
      }
    }
  }
}

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

  // No water border: the map edge is plain grass and the camera/physics world
  // bounds already stop the hero from walking off.

  // town: the east-west road at y=7 and the north-south road at x=7 cross by
  // the ELDER; everything else is dressing placed clear of those lanes
  stamp(map, 3, 2, ["HH", "HH"]);
  stamp(map, 1, 7, ["PPPPPPPPPPPPPPPPPPPPPPPPPP"]);
  stamp(map, 7, 3, ["P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P"]);
  stamp(map, 5, 7, ["P", "P"]);
  stamp(map, 6, 4, [".T.", "TTT"]);
  stamp(map, 15, 5, [".T.", "TTT"]);
  stamp(map, 18, 9, ["T.T", ".T."]);
  stamp(map, 12, 2, ["T"]);

  // east: pond and the lane down to the forest gate at (25, 10)
  stamp(map, 23, 3, ["WWW", "WWW"]);
  stamp(map, 21, 10, ["PPPP"]);
  stamp(map, 25, 2, [".T.", "TTT"]);
  stamp(map, 22, 12, ["T.T", ".T."]);
  stamp(map, 26, 13, ["T"]);
  stamp(map, 25, 16, [".T.", "TTT"]);

  // south
  stamp(map, 7, 14, ["P", "P", "P", "P", "P"]);
  stamp(map, 2, 16, ["T"]);
  stamp(map, 5, 17, [".T.", "TTT"]);
  stamp(map, 13, 17, ["TTT", ".T."]);
  stamp(map, 19, 16, [".T.", "TTT"]);
  stamp(map, 16, 15, ["T"]);
  stamp(map, 11, 13, ["T"]);

  // last, so a zone is never left partly under a tree the hero can't enter
  markZones(map, MONSTER_ZONES);

  return map;
}

export const PLAYER_SPAWN = { x: 9 * TILE + TILE / 2, y: 7 * TILE + TILE / 2 };
export const NPC_POS = { x: 11 * TILE + TILE / 2, y: 7 * TILE + TILE / 2 };
export const HOUSE_POS = { x: 3 * TILE, y: 2 * TILE };
export const SHOP_POS = { x: 5 * TILE + TILE / 2, y: 7 * TILE + TILE / 2 };
export const CAVE_POS = { x: 19 * TILE + TILE / 2, y: 2 * TILE + TILE / 2 };
// hero record board, three tiles east of the ELDER on the main road — clear of
// both his 120px talk radius and the ELDER name label, so nothing overlaps
export const RANK_BOARD_POS = { x: 14 * TILE + TILE / 2, y: 7 * TILE + TILE / 2 };

export const DUNGEON_W = 24;
export const DUNGEON_H = 16;
export const DUNGEON_ENTRY = { x: 10 * TILE + TILE / 2, y: 1 * TILE + TILE / 2 };

export const DUNGEON_ZONES: MonsterZone[] = [
  { cx: 4 * TILE, cy: 5 * TILE, w: 3 * TILE, h: 2 * TILE, count: 3 },
  { cx: 15 * TILE, cy: 6 * TILE, w: 3 * TILE, h: 2 * TILE, count: 3 },
  { cx: 10 * TILE, cy: 12 * TILE, w: 3 * TILE, h: 2 * TILE, count: 1 },
  // clear of the entry spawn at (10.5, 3.5) — this zone used to cover it, so
  // walking into the cave dropped the player straight onto a bat
  { cx: 11 * TILE, cy: 5 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3, kind: "bat" },
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

// Forest: 26x18 wall of trees around a grassy glade, path from entrance to boss clearing
export const FOREST_W = 26;
export const FOREST_H = 18;
export const FOREST_ENTRY = { x: 12 * TILE + TILE / 2, y: 1 * TILE + TILE / 2 };

// World-map position of the forest entrance (east side, far from CAVE/HOUSE)
export const FOREST_POS = { x: 25 * TILE + TILE / 2, y: 10 * TILE + TILE / 2 };

export const FOREST_ZONES: Array<MonsterZone & { kind?: "wasp" | "spider" | "orc" }> = [
  { cx: 4 * TILE, cy: 3 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3, kind: "wasp" },
  { cx: 21 * TILE, cy: 3 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3, kind: "wasp" },
  { cx: 5 * TILE, cy: 10 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3, kind: "spider" },
  { cx: 21 * TILE, cy: 9 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3, kind: "spider" },
  { cx: 6 * TILE, cy: 14 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3, kind: "orc" },
  { cx: 14 * TILE, cy: 13 * TILE, w: 3 * TILE, h: 2 * TILE, count: 1 }, // moss golem boss
];

export const FOREST_TREASURE_POS: Array<{ id: string; x: number; y: number }> = [
  { id: "forest-1", x: 4 * TILE + TILE / 2, y: 7 * TILE + TILE / 2 },
  { id: "forest-2", x: 19 * TILE + TILE / 2, y: 8 * TILE + TILE / 2 },
  { id: "forest-3", x: 9 * TILE + TILE / 2, y: 4 * TILE + TILE / 2 },
  { id: "forest-4", x: 16 * TILE + TILE / 2, y: 13 * TILE + TILE / 2 },
];

export function buildForest(): number[][] {
  const map: number[][] = Array.from({ length: FOREST_H }, () =>
    Array<number>(FOREST_W).fill(T_GRASS)
  );

  for (let x = 0; x < FOREST_W; x++) {
    map[0][x] = T_TREE;
    map[FOREST_H - 1][x] = T_TREE;
  }
  for (let y = 0; y < FOREST_H; y++) {
    map[y][0] = T_TREE;
    map[y][FOREST_W - 1] = T_TREE;
  }

  // winding path: entrance (top-center) down, across, down into the clearing
  stamp(map, 11, 1, ["PP", "PP", "PP"]);
  stamp(map, 13, 3, ["PPPPPP"]);
  stamp(map, 18, 4, ["P", "P", "P", "P"]);
  stamp(map, 13, 7, ["PPPPPP"]);
  stamp(map, 13, 8, ["P", "P", "P"]);
  stamp(map, 14, 10, ["PPPP"]);

  // small ponds
  stamp(map, 1, 6, ["WW", "WW", "WW"]);
  stamp(map, 23, 12, ["WW", "WW", "WW"]);

  // tree clusters
  stamp(map, 2, 2, ["T"]);
  stamp(map, 8, 5, [".T.", "TTT"]);
  stamp(map, 22, 6, ["T.T", ".T."]);
  stamp(map, 2, 10, ["T"]);
  stamp(map, 18, 11, [".T.", "TTT"]);
  stamp(map, 12, 11, ["T.T"]);
  stamp(map, 15, 15, ["T"]);
  stamp(map, 9, 14, ["T"]);
  stamp(map, 18, 15, [".T", "TT"]);
  stamp(map, 24, 5, ["T"]);
  stamp(map, 2, 14, ["TTT", ".T."]);

  // same marking rule as the overworld; the boss clearing stays unmarked so
  // the MOSS GOLEM is still a surprise
  markZones(map, FOREST_ZONES.filter((z) => z.count > 1));

  return map;
}
