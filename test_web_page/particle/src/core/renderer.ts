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
    resolution: window.devicePixelRatio || 1,
    autoDensity: true,
  });

  const host = parent ?? document.getElementById("app") ?? document.body;
  host.appendChild(app.canvas);
  return app;
}
