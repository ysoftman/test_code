import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { GameState } from "../gameState";
import { retroStyle } from "../pixelart";
import { Sfx, TITLE_THEME } from "../audio";

export class TitleScene extends Phaser.Scene {
  private started = false;

  constructor() {
    super("Title");
  }

  create(): void {
    this.started = false;
    Sfx.playBgm(TITLE_THEME);

    this.add.image(GAME_WIDTH / 2, GAME_HEIGHT / 2, "title-bg");

    const title = this.add
      .text(GAME_WIDTH / 2, 108, "MAGIC WORLD", retroStyle(24, "#ffd166"))
      .setOrigin(0.5);
    title.setShadow(4, 4, "#7c2d12", 1, true, true);

    this.add
      .text(GAME_WIDTH / 2, 184, "A TALE OF MAGIC", retroStyle(8, "#c4b5fd"))
      .setOrigin(0.5);
    this.add
      .text(GAME_WIDTH / 2, 208, "AND ADVENTURE", retroStyle(8, "#c4b5fd"))
      .setOrigin(0.5);

    const hasSave = GameState.hasSave();

    const prompt = this.add
      .text(GAME_WIDTH / 2, 296, hasSave ? "PRESS ENTER TO CONTINUE" : "PRESS ENTER", retroStyle(8, "#ffffff"))
      .setOrigin(0.5);
    this.tweens.add({
      targets: prompt,
      alpha: 0,
      duration: 500,
      yoyo: true,
      repeat: -1,
    });

    const continueText = this.add
      .text(
        GAME_WIDTH / 2,
        330,
        hasSave ? "C: CONTINUE  N: NEW GAME  Q: DELETE SAVE" : "NO SAVE FOUND",
        retroStyle(6, "#8ecbff")
      )
      .setOrigin(0.5);

    const start = (continueGame: boolean) => {
      if (this.started) return;
      this.started = true;
      Sfx.buy();
      if (continueGame) {
        GameState.load();
        // resume in the monster-free town center (PLAYER_SPAWN fallback)
        // instead of wherever the save happened, which can be mid-grass
        // next to a roamer and trigger an instant battle
        GameState.pos = undefined;
        this.scene.start("World");
        return;
      }
      GameState.reset();
      GameState.clearSave();
      this.cameras.main.fadeOut(400, 0, 0, 0);
      this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
        this.scene.start("World");
      });
    };

    this.input.keyboard!.on("keydown", (e: KeyboardEvent) => {
      // holding Q through the world's save-and-quit would land repeat Q
      // events here and delete the save that was just written
      if (e.repeat) return;
      Sfx.ensure();
      if (e.key === "Enter" || e.key === "z" || e.key === "Z" || e.key === " ") {
        start(GameState.hasSave());
      } else if (e.key === "n" || e.key === "N") {
        start(false);
      } else if ((e.key === "c" || e.key === "C") && GameState.hasSave()) {
        start(true);
      } else if (e.key === "q" || e.key === "Q") {
        GameState.clearSave();
        continueText.setText("NO SAVE FOUND");
        prompt.setText("PRESS ENTER");
      }
    });
    this.input.on("pointerdown", () => {
      Sfx.ensure();
      start(GameState.hasSave());
    });
  }
}