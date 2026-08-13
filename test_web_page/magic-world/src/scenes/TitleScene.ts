import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { retroStyle } from "../pixelart";

export class TitleScene extends Phaser.Scene {
  private started = false;

  constructor() {
    super("Title");
  }

  create(): void {
    this.add.image(GAME_WIDTH / 2, GAME_HEIGHT / 2, "title-bg");

    const title = this.add
      .text(GAME_WIDTH / 2, 54, "MAGIC WORLD", retroStyle(24, "#ffd166"))
      .setOrigin(0.5);
    title.setShadow(2, 2, "#7c2d12", 1, true, true);

    this.add
      .text(GAME_WIDTH / 2, 92, "A TALE OF MAGIC", retroStyle(8, "#c4b5fd"))
      .setOrigin(0.5);
    this.add
      .text(GAME_WIDTH / 2, 104, "AND ADVENTURE", retroStyle(8, "#c4b5fd"))
      .setOrigin(0.5);

    const prompt = this.add
      .text(GAME_WIDTH / 2, 156, "PRESS ENTER", retroStyle(8, "#ffffff"))
      .setOrigin(0.5);
    this.tweens.add({
      targets: prompt,
      alpha: 0,
      duration: 500,
      yoyo: true,
      repeat: -1,
    });

    this.input.keyboard!.on("keydown", (e: KeyboardEvent) => {
      if (e.key === "Enter" || e.key === "z" || e.key === "Z" || e.key === " ") {
        this.startGame();
      }
    });
    this.input.on("pointerdown", () => this.startGame());
  }

  private startGame(): void {
    if (this.started) return;
    this.started = true;
    this.cameras.main.fadeOut(400, 0, 0, 0);
    this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
      this.scene.start("World");
    });
  }
}
