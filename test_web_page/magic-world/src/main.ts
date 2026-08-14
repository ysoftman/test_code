import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "./config";
import { BootScene } from "./scenes/BootScene";
import { TitleScene } from "./scenes/TitleScene";
import { WorldScene } from "./scenes/WorldScene";
import { DungeonScene } from "./scenes/DungeonScene";
import { BattleScene } from "./scenes/BattleScene";
import { GameState } from "./gameState";
import { Sfx } from "./audio";

document.addEventListener("visibilitychange", () => {
  if (document.hidden) Sfx.suspendBgmForHiddenTab();
  else Sfx.resumeBgmFromHiddenTab();
});

const config: Phaser.Types.Core.GameConfig = {
  type: Phaser.AUTO,
  backgroundColor: "#0b0b2b",
  width: GAME_WIDTH,
  height: GAME_HEIGHT,
  pixelArt: true,
  roundPixels: true,
  physics: {
    default: "arcade",
    arcade: {
      gravity: { x: 0, y: 0 },
      debug: false,
    },
  },
  scale: {
    mode: Phaser.Scale.FIT,
    autoCenter: Phaser.Scale.CENTER_BOTH,
  },
  scene: [BootScene, TitleScene, WorldScene, DungeonScene, BattleScene],
};

// Canvas text bakes in whatever font is available at draw time; unlike DOM
// text it won't repaint when the webfont finishes loading later. Wait for it
// (bounded, so a slow/broken connection can't stall the game forever) before
// booting Phaser, so the title screen never flashes the fallback font.
const fontReady = document.fonts.load('16px "Press Start 2P"').catch(() => undefined);
const timeout = new Promise((resolve) => setTimeout(resolve, 2000));
Promise.race([fontReady, timeout]).finally(() => {
  GameState.loadSettings();
  new Phaser.Game(config);
});
