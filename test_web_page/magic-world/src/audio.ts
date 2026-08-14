import { GameState } from "./gameState";

export class Sfx {
  private static ctx: AudioContext | null = null;

  static ensure(): void {
    if (this.ctx) return;
    try {
      const AC =
        window.AudioContext ||
        (window as unknown as { webkitAudioContext: typeof AudioContext }).webkitAudioContext;
      this.ctx = new AC();
    } catch {
      this.ctx = null;
    }
  }

  static toggleMuted(): boolean {
    GameState.soundMuted = !GameState.soundMuted;
    GameState.saveSettings();
    return GameState.soundMuted;
  }

  private static tone(
    freq: number,
    dur: number,
    type: OscillatorType = "square",
    vol = 0.08,
    when = 0
  ): void {
    if (GameState.soundMuted) return;
    this.ensure();
    if (!this.ctx) return;
    const t = this.ctx.currentTime + when;
    const osc = this.ctx.createOscillator();
    const gain = this.ctx.createGain();
    osc.type = type;
    osc.frequency.setValueAtTime(freq, t);
    gain.gain.setValueAtTime(vol, t);
    gain.gain.exponentialRampToValueAtTime(0.001, t + dur);
    osc.connect(gain).connect(this.ctx.destination);
    osc.start(t);
    osc.stop(t + dur);
  }

  static move(): void {
    this.tone(600, 0.03, "square", 0.04);
  }

  static attack(): void {
    this.tone(240, 0.08, "square", 0.09);
    this.tone(180, 0.12, "square", 0.08, 0.03);
  }

  static magic(): void {
    this.tone(440, 0.12, "triangle", 0.08);
    this.tone(660, 0.14, "triangle", 0.07, 0.06);
    this.tone(880, 0.18, "triangle", 0.06, 0.12);
  }

  static hit(): void {
    this.tone(110, 0.16, "sawtooth", 0.1);
    this.tone(80, 0.2, "sawtooth", 0.08, 0.03);
  }

  static victory(): void {
    this.tone(523, 0.1, "square", 0.07);
    this.tone(659, 0.1, "square", 0.07, 0.09);
    this.tone(784, 0.18, "square", 0.07, 0.18);
  }

  static levelup(): void {
    this.tone(523, 0.09, "square", 0.08);
    this.tone(659, 0.09, "square", 0.08, 0.08);
    this.tone(784, 0.09, "square", 0.08, 0.16);
    this.tone(1047, 0.22, "square", 0.08, 0.24);
  }

  static capture(): void {
    this.tone(784, 0.1, "triangle", 0.08);
    this.tone(659, 0.1, "triangle", 0.08, 0.09);
    this.tone(523, 0.2, "triangle", 0.08, 0.18);
  }

  static buy(): void {
    this.tone(880, 0.06, "square", 0.06);
    this.tone(1320, 0.1, "square", 0.06, 0.05);
  }

  static error(): void {
    this.tone(160, 0.12, "sawtooth", 0.08);
  }

  static run(): void {
    this.tone(600, 0.06, "square", 0.06);
    this.tone(700, 0.06, "square", 0.06, 0.05);
    this.tone(800, 0.1, "square", 0.06, 0.1);
  }

  static boss(): void {
    this.tone(90, 0.35, "sawtooth", 0.11);
    this.tone(120, 0.35, "sawtooth", 0.09, 0.2);
  }

  static night(): void {
    this.tone(330, 0.1, "triangle", 0.05);
  }

  static gameover(): void {
    this.tone(392, 0.2, "square", 0.08);
    this.tone(330, 0.2, "square", 0.08, 0.18);
    this.tone(262, 0.3, "square", 0.08, 0.36);
    this.tone(196, 0.5, "square", 0.08, 0.56);
  }
}
