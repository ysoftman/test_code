import Phaser from "phaser";
import { RETRO_FONT } from "./config";

export interface PixelMap {
  [ch: string]: number;
}

export function retroStyle(
  size = 8,
  color = "#ffffff"
): Phaser.Types.GameObjects.Text.TextStyle {
  return {
    fontFamily: RETRO_FONT,
    fontSize: `${size}px`,
    color,
    align: "left",
    resolution: 1,
  };
}

export function drawRows(
  g: Phaser.GameObjects.Graphics,
  rows: string[],
  palette: PixelMap,
  ox: number,
  oy: number
): void {
  for (let y = 0; y < rows.length; y++) {
    const row = rows[y];
    for (let x = 0; x < row.length; x++) {
      const color = palette[row[x]];
      if (color !== undefined) {
        g.fillStyle(color, 1);
        g.fillRect(ox + x, oy + y, 1, 1);
      }
    }
  }
}

export function makeTexture(
  scene: Phaser.Scene,
  key: string,
  rows: string[],
  palette: PixelMap
): void {
  const w = Math.max(...rows.map((r) => r.length));
  const h = rows.length;
  const g = scene.add.graphics();
  drawRows(g, rows, palette, 0, 0);
  g.generateTexture(key, w, h);
  g.destroy();
}

export function makeTilesetTexture(
  scene: Phaser.Scene,
  key: string,
  tiles: Array<{ rows: string[]; palette: PixelMap }>,
  tileSize: number
): void {
  const g = scene.add.graphics();
  tiles.forEach((t, i) => drawRows(g, t.rows, t.palette, i * tileSize, 0));
  g.generateTexture(key, tiles.length * tileSize, tileSize);
  g.destroy();
}
