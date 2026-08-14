import Phaser from "phaser";
import { GAME_WIDTH, GAME_HEIGHT } from "../config";
import { retroStyle } from "../pixelart";

export class DialogueBox {
  private scene: Phaser.Scene;
  private lines: string[] = [];
  private index = 0;
  private charIndex = 0;
  private typing = false;
  private active = false;

  private border: Phaser.GameObjects.Rectangle;
  private box: Phaser.GameObjects.Rectangle;
  private text: Phaser.GameObjects.Text;
  private nameText: Phaser.GameObjects.Text;
  private timer?: Phaser.Time.TimerEvent;

  private z: Phaser.Input.Keyboard.Key;
  private space: Phaser.Input.Keyboard.Key;
  private enter: Phaser.Input.Keyboard.Key;
  private esc: Phaser.Input.Keyboard.Key;
  private advanceQueued = false;
  private escQueued = false;

  constructor(scene: Phaser.Scene, lines: string[]) {
    this.scene = scene;
    this.lines = lines;

    this.border = scene.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT - 68, GAME_WIDTH - 24, 104, 0xffffff)
      .setScrollFactor(0)
      .setDepth(200);
    this.box = scene.add
      .rectangle(GAME_WIDTH / 2, GAME_HEIGHT - 68, GAME_WIDTH - 32, 96, 0x0b0b2b)
      .setScrollFactor(0)
      .setDepth(201);
    this.text = scene.add
      .text(24, GAME_HEIGHT - 112, "", retroStyle(8, "#f5f5f5"))
      .setScrollFactor(0)
      .setDepth(202)
      .setWordWrapWidth(GAME_WIDTH - 64);
    this.nameText = scene.add
      .text(24, GAME_HEIGHT - 132, "", retroStyle(6, "#ffd166"))
      .setScrollFactor(0)
      .setDepth(202);

    this.border.setVisible(false);
    this.box.setVisible(false);
    this.text.setVisible(false);
    this.nameText.setVisible(false);

    const kb = scene.input.keyboard!;
    this.z = kb.addKey(Phaser.Input.Keyboard.KeyCodes.Z);
    this.space = kb.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);
    this.enter = kb.addKey(Phaser.Input.Keyboard.KeyCodes.ENTER);
    this.esc = kb.addKey(Phaser.Input.Keyboard.KeyCodes.ESC);
    const queueAdvance = () => {
      this.advanceQueued = true;
    };
    this.z.on(Phaser.Input.Keyboard.Events.DOWN, queueAdvance);
    this.space.on(Phaser.Input.Keyboard.Events.DOWN, queueAdvance);
    this.enter.on(Phaser.Input.Keyboard.Events.DOWN, queueAdvance);
    this.esc.on(Phaser.Input.Keyboard.Events.DOWN, () => {
      this.escQueued = true;
    });
  }

  start(lines?: string[], name?: string): void {
    if (lines) this.lines = lines;
    this.index = 0;
    this.charIndex = 0;
    this.active = true;
    this.advanceQueued = false;
    this.escQueued = false;

    this.border.setVisible(true);
    this.box.setVisible(true);
    this.text.setVisible(true);
    this.nameText.setVisible(name ? true : false);
    this.nameText.setText(name ?? "");

    this.typeLine();
  }

  private typeLine(): void {
    const line = this.lines[this.index];
    if (!line) {
      this.close();
      return;
    }
    this.text.setText("");
    this.typing = true;
    this.charIndex = 0;
    this.timer = this.scene.time.addEvent({
      delay: 22,
      repeat: line.length,
      callback: () => {
        this.charIndex++;
        this.text.setText(line.slice(0, this.charIndex));
        if (this.charIndex >= line.length) {
          this.typing = false;
          this.timer?.remove();
        }
      },
    });
  }

  update(): void {
    if (!this.active) return;
    if (this.escQueued) {
      this.escQueued = false;
      this.close();
      return;
    }
    if (!this.advanceQueued) return;
    this.advanceQueued = false;

    if (this.typing) {
      this.typing = false;
      this.timer?.remove();
      this.text.setText(this.lines[this.index]);
      return;
    }
    this.index++;
    if (this.index < this.lines.length) {
      this.typeLine();
    } else {
      this.close();
    }
  }

  private close(): void {
    this.active = false;
    this.border.setVisible(false);
    this.box.setVisible(false);
    this.text.setVisible(false);
    this.nameText.setVisible(false);
  }

  isActive(): boolean {
    return this.active;
  }

  destroy(): void {
    this.timer?.remove();
    this.border.destroy();
    this.box.destroy();
    this.text.destroy();
    this.nameText.destroy();
    this.z.destroy();
    this.space.destroy();
    this.enter.destroy();
    this.esc.destroy();
  }
}
