import Phaser from "phaser";
import { RETRO_FONT, PIXEL, GAME_WIDTH } from "./config";

export interface PixelMap {
  [ch: string]: number;
}

export function retroStyle(
  size = 8,
  color = "#ffffff"
): Phaser.Types.GameObjects.Text.TextStyle {
  return {
    fontFamily: RETRO_FONT,
    fontSize: `${size * PIXEL}px`,
    color,
    align: "left",
    resolution: 1,
  };
}

const TOAST_NAME = "__toast";

export function showToast(scene: Phaser.Scene, text: string): void {
  // Reuse one toast per scene instead of stacking a new Text on every call —
  // otherwise mashing the key that triggers it (e.g. mute) overlaps garbled
  // text from multiple in-flight instances.
  let t = scene.children.getByName(TOAST_NAME) as Phaser.GameObjects.Text | null;
  if (!t) {
    t = scene.add
      .text(GAME_WIDTH / 2, 8, "", retroStyle(5, "#8ecbff"))
      .setName(TOAST_NAME)
      .setOrigin(0.5, 0)
      .setScrollFactor(0)
      .setDepth(200)
      .setAlpha(0);
  }
  scene.tweens.killTweensOf(t);
  t.setText(text).setAlpha(0);
  scene.tweens.add({
    targets: t,
    alpha: 1,
    duration: 200,
    yoyo: true,
    hold: 900,
  });
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
        g.fillRect(ox + x * PIXEL, oy + y * PIXEL, PIXEL, PIXEL);
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
  g.generateTexture(key, w * PIXEL, h * PIXEL);
  g.destroy();
}

export function makeTilesetTexture(
  scene: Phaser.Scene,
  key: string,
  tiles: Array<{ rows: string[]; palette: PixelMap }>,
  tileSize: number
): void {
  const g = scene.add.graphics();
  tiles.forEach((t, i) => drawRows(g, t.rows, t.palette, i * tileSize * PIXEL, 0));
  g.generateTexture(key, tiles.length * tileSize * PIXEL, tileSize * PIXEL);
  g.destroy();
}
