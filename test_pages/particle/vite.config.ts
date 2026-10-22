import { defineConfig } from "vite";

export default defineConfig({
  // GitHub Pages 하위 경로(/test_code/particle/) 배포 대비 상대 경로 사용
  base: "./",
  build: {
    // pixi 가 init 시 동적 import 하는 작은 청크들이 추가 왕복을 만들어 첫 화면이 늦어진다 → 단일 번들로 합친다.
    rolldownOptions: { output: { codeSplitting: false } },
  },
});
