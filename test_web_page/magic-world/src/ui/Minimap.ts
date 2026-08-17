import Phaser from "phaser";
import { GAME_HEIGHT } from "../config";
import {
  TILE,
  T_GRASS,
  T_WATER_A,
  T_WATER_B,
  T_TREE,
  T_PATH,
  T_TALL,
  T_HOUSE,
} from "../levels";

export interface MinimapMarker {
  x: number;
  y: number;
  color: number;
}

// Tile index -> minimap color. Tiles the current scene doesn't know about
// (e.g. a future forest's own tile types) fall back to a neutral slate.
const TILE_COLORS: Record<number, number> = {
  [T_GRASS]: 0x1e7a34,
  [T_WATER_A]: 0x2563eb,
  [T_WATER_B]: 0x2563eb,
  [T_TREE]: 0x14532d,
  [T_PATH]: 0xb08968,
  [T_TALL]: 0x3fae49,
  [T_HOUSE]: 0x94a3b8,
};

const MAX_W = 160;
const MAX_H = 120;
const PAD = 2;
const DOT = 5;
// clears the two-line key hint every scene draws along the bottom edge
const BOTTOM_MARGIN = 68;

// Small fixed-screen minimap overlay: the scene's tilemap 2D array is drawn
// once into a Graphics as colored blocks, the player is a moving dot on top,
// and landmarks are passed in as world-space markers. Scroll-locked and
// anchored to the bottom-left corner so it clears the top HUD and the
// bottom-right hint text. Hidden until the scene toggles it (T key).
export class Minimap {
  private container: Phaser.GameObjects.Container;
  private playerDot: Phaser.GameObjects.Rectangle;
  private cell: number;
  private dotX: number;
  private dotY: number;
  private player: Phaser.GameObjects.Sprite;

  constructor(
    scene: Phaser.Scene,
    mapData: number[][],
    player: Phaser.GameObjects.Sprite,
    markers: MinimapMarker[] = []
  ) {
    this.player = player;
    const mapW = mapData.length > 0 ? mapData[0].length : 0;
    const mapH = mapData.length;
    const cell = mapW > 0 && mapH > 0 ? Math.min(MAX_W / mapW, MAX_H / mapH) : 1;
    this.cell = cell;
    const w = Math.floor(mapW * cell);
    const h = Math.floor(mapH * cell);
    this.dotX = PAD;
    this.dotY = PAD;

    const mapG = scene.add.graphics();
    mapG.fillStyle(0x0b0b2b, 1);
    mapG.fillRect(0, 0, w, h);
    for (let ty = 0; ty < mapH; ty++) {
      for (let tx = 0; tx < mapW; tx++) {
        mapG.fillStyle(TILE_COLORS[mapData[ty][tx]] ?? 0x334155, 1);
        // +0.5 so adjacent cells overlap instead of showing hairline seams
        mapG.fillRect(tx * cell, ty * cell, cell + 0.5, cell + 0.5);
      }
    }
    for (const m of markers) {
      mapG.fillStyle(m.color, 1);
      mapG.fillRect((m.x / TILE) * cell - 2, (m.y / TILE) * cell - 2, 4, 4);
    }

    this.playerDot = scene.add.rectangle(0, 0, DOT, DOT, 0xf5f5f5).setOrigin(0.5);

    const border = scene.add
      .rectangle(0, 0, w + PAD * 2, h + PAD * 2, 0x0b0b2b)
      .setOrigin(0)
      .setStrokeStyle(2, 0xffffff);

    this.container = scene.add
      .container(12, GAME_HEIGHT - BOTTOM_MARGIN - (h + PAD * 2), [border, mapG, this.playerDot])
      .setScrollFactor(0)
      .setDepth(96)
      .setVisible(false);
  }

  toggle(): void {
    this.container.setVisible(!this.container.visible);
    this.update();
  }

  isVisible(): boolean {
    return this.container.visible;
  }

  // Called every frame by the owning scene; cheap — just repositions the dot.
  update(): void {
    if (!this.container.visible) return;
    this.playerDot.setPosition(
      this.dotX + (this.player.x / TILE) * this.cell,
      this.dotY + (this.player.y / TILE) * this.cell
    );
  }

  destroy(): void {
    this.container.destroy();
  }
}
