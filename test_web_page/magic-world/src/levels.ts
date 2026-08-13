export const TILE = 32;

export const T_GRASS = 0;
export const T_WATER_A = 1;
export const T_WATER_B = 2;
export const T_TREE = 3;
export const T_PATH = 4;
export const T_TALL = 5;
export const T_HOUSE = 6;

export const MAP_W = 24;
export const MAP_H = 18;

export const SOLID = new Set<number>([T_WATER_A, T_WATER_B, T_TREE, T_HOUSE]);
export const TALL_GRASS = T_TALL;

export interface MonsterZone {
  cx: number;
  cy: number;
  w: number;
  h: number;
  count: number;
}

export const MONSTER_ZONES: MonsterZone[] = [
  { cx: 4 * TILE, cy: 14 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3 },
  { cx: 18 * TILE, cy: 13 * TILE, w: 2 * TILE, h: 2 * TILE, count: 3 },
];

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
  stamp(map, 1, 7, ["PPPPPPPPPPPPPPPPPPPP"]);
  stamp(map, 7, 3, ["P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P"]);
  stamp(map, 3, 13, ["hh", "hh"]);
  stamp(map, 17, 12, ["hh", "hh"]);
  stamp(map, 6, 4, [".T.", "TTT"]);
  stamp(map, 15, 5, [".T.", "TTT"]);
  stamp(map, 18, 9, ["T.T", ".T."]);
  stamp(map, 12, 2, ["T"]);

  return map;
}

export const PLAYER_SPAWN = { x: 9 * TILE + TILE / 2, y: 7 * TILE + TILE / 2 };
export const NPC_POS = { x: 11 * TILE + TILE / 2, y: 7 * TILE + TILE / 2 };
export const HOUSE_POS = { x: 3 * TILE, y: 2 * TILE };
