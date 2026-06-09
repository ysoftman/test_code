// Pixi.js v8 렌더러 셋업: 전체 화면 자동 리사이즈 캔버스 + 우주 배경.

import { Application } from "pixi.js";
import { COLORS } from "../constants";

/**
 * Pixi Application 을 생성·초기화한다 (v8 은 async init 필요).
 * 캔버스는 창 전체를 채우며 `resizeTo` 로 창 크기 변화를 따라간다.
 * 캔버스는 `parent` 에 붙인다 (기본 #app, 없으면 body).
 */
export async function createRenderer(parent?: HTMLElement): Promise<Application> {
  const app = new Application();
  await app.init({
    resizeTo: window,
    background: COLORS.background,
    antialias: true,
    // 고해상도 모바일 성능 보호: devicePixelRatio 를 최대 2 로 캡.
    resolution: Math.min(window.devicePixelRatio || 1, 2),
    autoDensity: true,
  });

  const host = parent ?? document.getElementById("app") ?? document.body;
  host.appendChild(app.canvas);

  // resizeTo:window 는 window 의 resize 이벤트를 따라가므로 모바일 주소창
  // 표시/숨김과 일반 회전에도 반응한다. 다만 일부 모바일 브라우저는
  // orientationchange 직후 resize 가 누락되거나 옛 크기를 보고할 수 있어,
  // 안전하게 한 번 더 강제 리사이즈한다.
  window.addEventListener("orientationchange", () => {
    app.resize();
  });

  return app;
}
