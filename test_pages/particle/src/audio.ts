// 효과음 — Web Audio API 로 절차적으로 생성한다(에셋 파일 불필요).
// 리프 유틸 모듈: 게임 로직에 의존하지 않으므로 entities/game/main 어디서든 import 가능.
// 브라우저 자동재생 정책상 첫 사용자 제스처에서 unlockAudio() 로 컨텍스트를 깨워야 한다.

let ctx: AudioContext | null = null;

/** AudioContext 를 지연 생성한다. 미지원 환경(SSR 등)에서는 null. */
function getCtx(): AudioContext | null {
  if (typeof window === "undefined") return null;
  if (!ctx) {
    const AC =
      window.AudioContext ??
      (window as unknown as { webkitAudioContext?: typeof AudioContext }).webkitAudioContext;
    if (!AC) return null;
    ctx = new AC();
  }
  return ctx;
}

/**
 * 첫 사용자 제스처(키다운/포인터/터치) 핸들러에서 호출한다.
 * suspended 상태의 컨텍스트를 resume 해 이후 효과음 재생을 가능하게 한다.
 */
export function unlockAudio(): void {
  const c = getCtx();
  if (c && c.state === "suspended") {
    void c.resume();
  }
}

/** 발사음 — 짧게 떨어지는 사각파 "퓨". */
export function playFire(): void {
  const c = getCtx();
  if (c?.state !== "running") return;
  const t = c.currentTime;
  const osc = c.createOscillator();
  const gain = c.createGain();
  osc.type = "square";
  osc.frequency.setValueAtTime(880, t);
  osc.frequency.exponentialRampToValueAtTime(180, t + 0.12);
  gain.gain.setValueAtTime(0.1, t);
  gain.gain.exponentialRampToValueAtTime(0.0008, t + 0.14);
  osc.connect(gain).connect(c.destination);
  osc.start(t);
  osc.stop(t + 0.15);
}

/** 명중/파괴음 — 저역으로 떨어지는 노이즈 버스트 "펑". */
export function playHit(): void {
  const c = getCtx();
  if (c?.state !== "running") return;
  const t = c.currentTime;
  const dur = 0.22;

  const buffer = c.createBuffer(1, Math.max(1, Math.floor(c.sampleRate * dur)), c.sampleRate);
  const data = buffer.getChannelData(0);
  for (let i = 0; i < data.length; i++) {
    // 시간이 지날수록 감쇠하는 화이트 노이즈.
    data[i] = (Math.random() * 2 - 1) * (1 - i / data.length);
  }

  const noise = c.createBufferSource();
  noise.buffer = buffer;

  const filter = c.createBiquadFilter();
  filter.type = "lowpass";
  filter.frequency.setValueAtTime(1400, t);
  filter.frequency.exponentialRampToValueAtTime(180, t + dur);

  const gain = c.createGain();
  gain.gain.setValueAtTime(0.22, t);
  gain.gain.exponentialRampToValueAtTime(0.0008, t + dur);

  noise.connect(filter).connect(gain).connect(c.destination);
  noise.start(t);
  noise.stop(t + dur);
}
