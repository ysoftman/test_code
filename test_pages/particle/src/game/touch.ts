// 모바일 터치 조작 오버레이 — 공유 InputState 를 갱신한다.
// 키보드 입력(input.ts)과 동일한 InputState 를 공유하므로 Ship 은 입력 출처를
// 구분하지 않는다. 터치 기기가 아니면 아무 DOM 도 만들지 않고 조용히 반환한다.

import "./touch.css";
import type { InputState } from "../types";

/** 조이스틱 중심에서 이 비율(0..1) 미만의 기울기는 무시(데드존). */
const JOY_DEADZONE = 0.15;

/** ('ontouchstart' in window) || navigator.maxTouchPoints > 0 로 터치 기기를 감지. */
function isTouchDevice(): boolean {
  return "ontouchstart" in window || navigator.maxTouchPoints > 0;
}

/**
 * 터치 기기에서 화면 코너에 가상 조작 UI 오버레이를 만든다.
 * - 좌하단: 아날로그 조이스틱 — 누른 채 드래그하면 그 방향(360°)으로 비행체가 향하고
 *   중심에서 멀어질수록(magnitude) 강하게 추진한다. (input.aim 갱신)
 * - 우하단: FIRE(발사) 버튼. (input.fire 토글)
 *
 * 조이스틱과 FIRE 는 각자 독립된 터치 identifier 를 추적하므로, 한 손으로 조종하며
 * 다른 손으로 동시에 발사할 수 있다(멀티터치). 손가락이 FIRE 밖으로 슬라이드되면 해제된다.
 *
 * @param input 키보드 입력과 공유되는 InputState (이 함수가 aim/fire 를 직접 갱신).
 * @returns 생성된 오버레이 엘리먼트, 터치 기기가 아니면 null.
 */
export function createTouchControls(input: InputState): HTMLElement | null {
  if (!isTouchDevice()) return null;

  const overlay = document.createElement("div");
  overlay.className = "touch-overlay";

  // 좌하단: 아날로그 조이스틱 (베이스 + 안쪽 썸).
  const joyBase = document.createElement("div");
  joyBase.className = "touch-joy-base";
  const joyThumb = document.createElement("div");
  joyThumb.className = "touch-joy-thumb";
  joyBase.appendChild(joyThumb);

  // 우하단: 발사 버튼.
  const fireBtn = document.createElement("button");
  fireBtn.type = "button";
  fireBtn.className = "touch-btn touch-fire";
  fireBtn.textContent = "FIRE";
  fireBtn.setAttribute("aria-label", "fire");

  overlay.appendChild(joyBase);
  overlay.appendChild(fireBtn);

  const host = document.getElementById("app") ?? document.body;
  host.appendChild(overlay);

  // --- 조이스틱 ---
  let joyTouchId: number | null = null;

  /** 터치 좌표로 조이스틱 썸 위치와 input.aim(angle, magnitude)을 갱신한다. */
  const updateJoy = (clientX: number, clientY: number): void => {
    const r = joyBase.getBoundingClientRect();
    const cx = r.left + r.width / 2;
    const cy = r.top + r.height / 2;
    const maxR = r.width / 2;
    const dx = clientX - cx;
    const dy = clientY - cy;
    const dist = Math.hypot(dx, dy);
    const angle = Math.atan2(dy, dx);
    const clamped = Math.min(dist, maxR);

    // 썸을 베이스 반경 안으로 클램프해 이동.
    joyThumb.style.transform = `translate(${Math.cos(angle) * clamped}px, ${Math.sin(angle) * clamped}px)`;

    const raw = maxR > 0 ? clamped / maxR : 0;
    if (raw < JOY_DEADZONE) {
      input.aim = null;
    } else {
      // 데드존을 제외한 구간을 0..1 로 재매핑.
      const magnitude = Math.min(1, (raw - JOY_DEADZONE) / (1 - JOY_DEADZONE));
      input.aim = { angle, magnitude };
    }
  };

  const resetJoy = (): void => {
    joyTouchId = null;
    joyThumb.style.transform = "translate(0px, 0px)";
    input.aim = null;
  };

  // --- FIRE ---
  let fireTouchId: number | null = null;

  const setFire = (on: boolean): void => {
    input.fire = on;
    fireBtn.classList.toggle("is-active", on);
  };

  const within = (el: HTMLElement, x: number, y: number): boolean => {
    const r = el.getBoundingClientRect();
    return x >= r.left && x <= r.right && y >= r.top && y <= r.bottom;
  };

  const onStart = (e: TouchEvent): void => {
    e.preventDefault();
    for (const t of Array.from(e.changedTouches)) {
      if (joyTouchId === null && within(joyBase, t.clientX, t.clientY)) {
        joyTouchId = t.identifier;
        updateJoy(t.clientX, t.clientY);
      } else if (fireTouchId === null && within(fireBtn, t.clientX, t.clientY)) {
        fireTouchId = t.identifier;
        setFire(true);
      }
    }
  };

  const onMove = (e: TouchEvent): void => {
    e.preventDefault();
    for (const t of Array.from(e.changedTouches)) {
      if (t.identifier === joyTouchId) {
        // 손가락이 베이스를 벗어나도 추적 유지(반경 클램프).
        updateJoy(t.clientX, t.clientY);
      } else if (t.identifier === fireTouchId && !within(fireBtn, t.clientX, t.clientY)) {
        // 손가락이 FIRE 밖으로 슬라이드되면 해제.
        fireTouchId = null;
        setFire(false);
      }
    }
  };

  const onEnd = (e: TouchEvent): void => {
    e.preventDefault();
    for (const t of Array.from(e.changedTouches)) {
      if (t.identifier === joyTouchId) {
        resetJoy();
      } else if (t.identifier === fireTouchId) {
        fireTouchId = null;
        setFire(false);
      }
    }
  };

  // passive:false 로 등록해야 preventDefault() 가 스크롤/줌을 막을 수 있다.
  const opts: AddEventListenerOptions = { passive: false };
  overlay.addEventListener("touchstart", onStart, opts);
  overlay.addEventListener("touchmove", onMove, opts);
  overlay.addEventListener("touchend", onEnd, opts);
  overlay.addEventListener("touchcancel", onEnd, opts);

  return overlay;
}
