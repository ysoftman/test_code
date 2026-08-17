import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { nightFactor } from "../gameState";

// One night look shared by every scene. Before this, the overworld faded a
// 0x1a1a4a wash in and out with the clock while the cave and the forest sat
// under a fixed 0x0a0a2a that ignored the time of day entirely.
export const NIGHT_TINT = 0x1a1a4a;

// How dark full night gets on open ground. Enclosed scenes pass a smaller
// range and carry a constant `ambient` instead, so their own gloom stays but
// dusk and dawn still read the same way everywhere.
export const NIGHT_RANGE = 0.45;

// Encounters get riskier after dark by the same factor in every scene.
export const NIGHT_ENCOUNTER_MULT = 1.8;

export class NightOverlay {
  private rect: Phaser.GameObjects.Rectangle;
  private ambient: number;
  private range: number;

  constructor(scene: Phaser.Scene, ambient = 0, range = NIGHT_RANGE) {
    this.ambient = ambient;
    this.range = range;
    this.rect = scene.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT / 2, GAME_WIDTH, GAME_HEIGHT, NIGHT_TINT, 1)
      .setScrollFactor(0)
      .setDepth(90)
      .setAlpha(ambient);
  }

  // Call every frame; `nightFactor()` ramps across dusk and dawn so this is a
  // fade rather than a switch.
  update(): number {
    const factor = nightFactor();
    this.rect.setAlpha(this.ambient + factor * this.range);
    return factor;
  }

  destroy(): void {
    this.rect.destroy();
  }
}
