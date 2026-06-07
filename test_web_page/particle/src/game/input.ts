// 키보드 입력 처리 — 공유 InputState 객체에 상태를 기록한다.
// e.code 를 사용하므로 자판 배열/IME(한글 등)가 조작에 영향을 주지 않는다.

import type { InputState } from "../types";

/** 브라우저 기본 동작(스크롤)을 막아야 하는 키들. */
const PREVENT_DEFAULT_CODES = new Set(["Space", "ArrowUp", "ArrowDown", "ArrowLeft", "ArrowRight"]);

/**
 * window keydown/keyup 리스너로 항상 최신 상태가 유지되는 InputState 를 생성한다.
 * W/ArrowUp = 추진, S/ArrowDown = 후진,
 * A/ArrowLeft = 좌회전, D/ArrowRight = 우회전, Space = 발사.
 */
export function createInput(): InputState {
  const state: InputState = {
    thrust: false,
    reverse: false,
    turnLeft: false,
    turnRight: false,
    fire: false,
  };

  const apply = (code: string, pressed: boolean): void => {
    switch (code) {
      case "KeyW":
      case "ArrowUp":
        state.thrust = pressed;
        break;
      case "KeyS":
      case "ArrowDown":
        state.reverse = pressed;
        break;
      case "KeyA":
      case "ArrowLeft":
        state.turnLeft = pressed;
        break;
      case "KeyD":
      case "ArrowRight":
        state.turnRight = pressed;
        break;
      case "Space":
        state.fire = pressed;
        break;
    }
  };

  window.addEventListener("keydown", (e) => {
    if (PREVENT_DEFAULT_CODES.has(e.code)) e.preventDefault();
    apply(e.code, true);
  });

  window.addEventListener("keyup", (e) => {
    if (PREVENT_DEFAULT_CODES.has(e.code)) e.preventDefault();
    apply(e.code, false);
  });

  return state;
}
