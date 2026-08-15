import { GameState } from "./gameState";

interface Note {
  freq: number | null; // null = rest
  dur: number; // seconds
}

// Looping chiptune backgrounds, one melodic line each (no separate bass) to
// keep the single-oscillator-per-note engine simple.
// A-A'-B-A form in C major, ~12s per loop
export const TITLE_THEME: Note[] = [
  // A
  { freq: 262, dur: 0.3 },
  { freq: 330, dur: 0.3 },
  { freq: 392, dur: 0.3 },
  { freq: 523, dur: 0.45 },
  { freq: 392, dur: 0.3 },
  { freq: 330, dur: 0.3 },
  { freq: 294, dur: 0.3 },
  { freq: null, dur: 0.3 },
  // A' — same rise, falls through A instead
  { freq: 262, dur: 0.3 },
  { freq: 330, dur: 0.3 },
  { freq: 392, dur: 0.3 },
  { freq: 523, dur: 0.45 },
  { freq: 440, dur: 0.3 },
  { freq: 392, dur: 0.3 },
  { freq: 330, dur: 0.3 },
  { freq: null, dur: 0.3 },
  // B — lifts to the subdominant
  { freq: 349, dur: 0.3 },
  { freq: 440, dur: 0.3 },
  { freq: 523, dur: 0.3 },
  { freq: 587, dur: 0.45 },
  { freq: 523, dur: 0.3 },
  { freq: 440, dur: 0.3 },
  { freq: 392, dur: 0.3 },
  { freq: null, dur: 0.3 },
  // A — cadence home
  { freq: 262, dur: 0.3 },
  { freq: 330, dur: 0.3 },
  { freq: 392, dur: 0.3 },
  { freq: 523, dur: 0.45 },
  { freq: 392, dur: 0.3 },
  { freq: 330, dur: 0.3 },
  { freq: 262, dur: 0.6 },
  { freq: null, dur: 0.45 },
];

// Four skipping phrases climbing then settling, ~6s per loop
export const OVERWORLD_THEME: Note[] = [
  { freq: 523, dur: 0.18 },
  { freq: 659, dur: 0.18 },
  { freq: 784, dur: 0.18 },
  { freq: 659, dur: 0.18 },
  { freq: 587, dur: 0.18 },
  { freq: 698, dur: 0.18 },
  { freq: 659, dur: 0.18 },
  { freq: 523, dur: 0.3 },
  { freq: 587, dur: 0.18 },
  { freq: 698, dur: 0.18 },
  { freq: 880, dur: 0.18 },
  { freq: 698, dur: 0.18 },
  { freq: 659, dur: 0.18 },
  { freq: 784, dur: 0.18 },
  { freq: 698, dur: 0.18 },
  { freq: 587, dur: 0.3 },
  { freq: 659, dur: 0.18 },
  { freq: 784, dur: 0.18 },
  { freq: 1047, dur: 0.18 },
  { freq: 784, dur: 0.18 },
  { freq: 698, dur: 0.18 },
  { freq: 880, dur: 0.18 },
  { freq: 784, dur: 0.18 },
  { freq: 659, dur: 0.3 },
  { freq: 523, dur: 0.18 },
  { freq: 587, dur: 0.18 },
  { freq: 659, dur: 0.18 },
  { freq: 784, dur: 0.18 },
  { freq: 659, dur: 0.18 },
  { freq: 587, dur: 0.18 },
  { freq: 523, dur: 0.36 },
  { freq: null, dur: 0.3 },
];

// Sparse minor phrases drifting lower each time, ~13s per loop
export const DUNGEON_THEME: Note[] = [
  { freq: 262, dur: 0.3 },
  { freq: null, dur: 0.2 },
  { freq: 311, dur: 0.3 },
  { freq: null, dur: 0.2 },
  { freq: 294, dur: 0.4 },
  { freq: null, dur: 0.3 },
  { freq: 196, dur: 0.5 },
  { freq: null, dur: 0.4 },
  { freq: 262, dur: 0.3 },
  { freq: null, dur: 0.2 },
  { freq: 349, dur: 0.3 },
  { freq: null, dur: 0.2 },
  { freq: 311, dur: 0.4 },
  { freq: null, dur: 0.3 },
  { freq: 233, dur: 0.5 },
  { freq: null, dur: 0.4 },
  { freq: 415, dur: 0.3 },
  { freq: null, dur: 0.2 },
  { freq: 392, dur: 0.3 },
  { freq: null, dur: 0.2 },
  { freq: 349, dur: 0.4 },
  { freq: null, dur: 0.3 },
  { freq: 294, dur: 0.5 },
  { freq: null, dur: 0.4 },
  { freq: 262, dur: 0.3 },
  { freq: null, dur: 0.2 },
  { freq: 294, dur: 0.3 },
  { freq: null, dur: 0.2 },
  { freq: 311, dur: 0.4 },
  { freq: null, dur: 0.3 },
  { freq: 262, dur: 0.6 },
  { freq: null, dur: 0.5 },
];

// Driving riff with two variations and a run back home, ~4s per loop
export const BATTLE_THEME: Note[] = [
  { freq: 523, dur: 0.12 },
  { freq: 392, dur: 0.12 },
  { freq: 523, dur: 0.12 },
  { freq: 392, dur: 0.12 },
  { freq: 659, dur: 0.12 },
  { freq: 523, dur: 0.12 },
  { freq: 587, dur: 0.12 },
  { freq: 494, dur: 0.12 },
  { freq: 523, dur: 0.12 },
  { freq: 392, dur: 0.12 },
  { freq: 523, dur: 0.12 },
  { freq: 392, dur: 0.12 },
  { freq: 698, dur: 0.12 },
  { freq: 587, dur: 0.12 },
  { freq: 659, dur: 0.12 },
  { freq: 523, dur: 0.12 },
  { freq: 440, dur: 0.12 },
  { freq: 659, dur: 0.12 },
  { freq: 440, dur: 0.12 },
  { freq: 659, dur: 0.12 },
  { freq: 698, dur: 0.12 },
  { freq: 659, dur: 0.12 },
  { freq: 587, dur: 0.12 },
  { freq: 494, dur: 0.12 },
  { freq: 523, dur: 0.12 },
  { freq: 659, dur: 0.12 },
  { freq: 784, dur: 0.12 },
  { freq: 659, dur: 0.12 },
  { freq: 587, dur: 0.12 },
  { freq: 494, dur: 0.12 },
  { freq: 523, dur: 0.24 },
  { freq: null, dur: 0.12 },
];

export class Sfx {
  private static ctx: AudioContext | null = null;
  private static bgmTimer: ReturnType<typeof setTimeout> | null = null;
  private static bgmTrack: Note[] | null = null;

  static ensure(): void {
    if (this.ctx) {
      // autoplay policies can start (or leave) the context suspended when
      // it's created before any user gesture, e.g. by the title screen's
      // BGM starting on load; nothing else in this file ever resumes it
      if (this.ctx.state === "suspended") void this.ctx.resume();
      return;
    }
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

  static playBgm(track: Note[]): void {
    if (this.bgmTrack === track) return; // already looping this one
    this.bgmTrack = track;
    this.restartBgmLoop();
  }

  private static restartBgmLoop(): void {
    if (this.bgmTimer !== null) clearTimeout(this.bgmTimer);
    this.bgmTimer = null;
    const track = this.bgmTrack;
    if (!track) return;
    let i = 0;
    const step = (): void => {
      const note = track[i % track.length];
      if (note.freq) this.tone(note.freq, note.dur * 0.9, "triangle", 0.035);
      i++;
      this.bgmTimer = setTimeout(step, note.dur * 1000);
    };
    step();
  }

  // A hidden tab clamps setTimeout to >=1000ms, which would otherwise turn
  // the loop into a slow, distorted dribble of single notes. Go silent
  // instead and pick the same track back up (from its first note) on
  // return. Wired to document visibilitychange in main.ts.
  static suspendBgmForHiddenTab(): void {
    if (this.bgmTimer !== null) clearTimeout(this.bgmTimer);
    this.bgmTimer = null;
  }

  static resumeBgmFromHiddenTab(): void {
    if (this.bgmTrack && this.bgmTimer === null) this.restartBgmLoop();
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
    // autoplay policy: a context created before any user gesture stays
    // suspended with currentTime frozen, so every scheduled note would pile
    // onto the same timestamp and fire at once on resume — skip them instead
    if (this.ctx.state !== "running") return;
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

  static critical(): void {
    this.tone(150, 0.05, "square", 0.1);
    this.tone(700, 0.1, "square", 0.09, 0.04);
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

  static pickup(): void {
    this.tone(880, 0.07, "square", 0.06);
    this.tone(1175, 0.12, "square", 0.06, 0.06);
  }

  static spark(): void {
    this.tone(1400, 0.04, "square", 0.05);
    this.tone(900, 0.06, "square", 0.04, 0.03);
  }

  static chest(): void {
    this.tone(200, 0.12, "sawtooth", 0.08);
    this.tone(150, 0.1, "sawtooth", 0.07, 0.08);
    this.tone(660, 0.14, "square", 0.06, 0.14);
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
