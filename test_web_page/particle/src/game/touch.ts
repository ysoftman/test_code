// 모바일 터치 조작 오버레이 — 공유 InputState 객체의 플래그를 토글한다.
// 키보드 입력(input.ts)과 동일한 InputState 를 공유하므로 Ship 은 입력 출처를
// 구분하지 않는다. 터치 기기가 아니면 아무 DOM 도 만들지 않고 조용히 반환한다.

import "./touch.css";
import type { InputState } from "../types";

/** 토글 가능한 InputState 의 boolean 플래그 키. */
type FlagKey = "thrust" | "reverse" | "turnLeft" | "turnRight" | "fire";

interface TouchButton {
  readonly el: HTMLButtonElement;
  readonly flag: FlagKey;
}

/** ('ontouchstart' in window) || navigator.maxTouchPoints > 0 로 터치 기기를 감지. */
function isTouchDevice(): boolean {
  return "ontouchstart" in window || navigator.maxTouchPoints > 0;
}

/**
 * 터치 기기에서 화면 코너에 가상 조작 버튼 오버레이를 만든다.
 * 왼쪽 엄지로 4방향 이동을, 오른쪽 엄지로 발사를 담당하는 배치다.
 * - 좌하단: 십자(D-패드) — ▲ 추진(thrust) / ◀ 좌회전(turnLeft) / ▶ 우회전(turnRight) / ▼ 후진(reverse)
 * - 우하단: FIRE(발사)
 *
 * 멀티터치를 위해 각 활성 터치(identifier)가 어느 버튼 위에 있는지 추적하고,
 * 손가락이 버튼 밖으로 슬라이드되면 해당 플래그를 해제한다. 한 손가락으로 회전하며
 * 다른 손가락으로 추진+발사가 동시에 가능하다.
 *
 * @param input 키보드 입력과 공유되는 InputState (이 함수가 플래그를 직접 토글).
 * @returns 생성된 오버레이 엘리먼트, 터치 기기가 아니면 null.
 */
export function createTouchControls(input: InputState): HTMLElement | null {
  if (!isTouchDevice()) return null;

  const overlay = document.createElement("div");
  overlay.className = "touch-overlay";

  const buttons: TouchButton[] = [];

  const makeButton = (flag: FlagKey, label: string, extraClass: string): HTMLButtonElement => {
    const el = document.createElement("button");
    el.type = "button";
    el.className = `touch-btn ${extraClass}`;
    el.textContent = label;
    el.setAttribute("aria-label", flag);
    buttons.push({ el, flag });
    return el;
  };

  // 좌하단: 4방향 십자(D-패드) — 한 엄지로 ▲추진 / ◀▶회전 / ▼후진.
  const left = document.createElement("div");
  left.className = "touch-cluster touch-left touch-dpad";
  left.appendChild(makeButton("thrust", "▲", "touch-dir touch-up"));
  left.appendChild(makeButton("turnLeft", "◀", "touch-dir touch-turnleft"));
  left.appendChild(makeButton("turnRight", "▶", "touch-dir touch-turnright"));
  left.appendChild(makeButton("reverse", "▼", "touch-dir touch-down"));

  // 우하단: 발사. 오른쪽 엄지로 조작.
  const right = document.createElement("div");
  right.className = "touch-cluster touch-right";
  right.appendChild(makeButton("fire", "FIRE", "touch-fire"));

  overlay.appendChild(left);
  overlay.appendChild(right);

  const host = document.getElementById("app") ?? document.body;
  host.appendChild(overlay);

  // 각 터치 identifier 가 현재 어느 버튼 위에 있는지 추적한다.
  const assignments = new Map<number, TouchButton>();

  /** 주어진 화면 좌표 위에 있는 버튼을 반환(없으면 null). */
  const buttonAt = (x: number, y: number): TouchButton | null => {
    for (const b of buttons) {
      const r = b.el.getBoundingClientRect();
      if (x >= r.left && x <= r.right && y >= r.top && y <= r.bottom) return b;
    }
    return null;
  };

  /** 현재 assignments 를 기준으로 InputState 플래그와 버튼 하이라이트를 동기화. */
  const refreshFlags = (): void => {
    const active = new Set<FlagKey>();
    for (const b of assignments.values()) active.add(b.flag);

    input.thrust = active.has("thrust");
    input.reverse = active.has("reverse");
    input.turnLeft = active.has("turnLeft");
    input.turnRight = active.has("turnRight");
    input.fire = active.has("fire");

    for (const b of buttons) b.el.classList.toggle("is-active", active.has(b.flag));
  };

  /** 한 터치 identifier 의 현재 버튼 소속을 갱신(슬라이드로 버튼이 바뀌면 자동 이동). */
  const assignTouch = (id: number, btn: TouchButton | null): void => {
    if (btn) assignments.set(id, btn);
    else assignments.delete(id);
  };

  const onStartOrMove = (e: TouchEvent): void => {
    e.preventDefault();
    const touches = e.changedTouches;
    for (let i = 0; i < touches.length; i++) {
      const t = touches[i];
      assignTouch(t.identifier, buttonAt(t.clientX, t.clientY));
    }
    refreshFlags();
  };

  const onEnd = (e: TouchEvent): void => {
    e.preventDefault();
    const touches = e.changedTouches;
    for (let i = 0; i < touches.length; i++) {
      assignments.delete(touches[i].identifier);
    }
    refreshFlags();
  };

  // passive:false 로 등록해야 preventDefault() 가 스크롤/줌을 막을 수 있다.
  const opts: AddEventListenerOptions = { passive: false };
  overlay.addEventListener("touchstart", onStartOrMove, opts);
  overlay.addEventListener("touchmove", onStartOrMove, opts);
  overlay.addEventListener("touchend", onEnd, opts);
  overlay.addEventListener("touchcancel", onEnd, opts);

  return overlay;
}
