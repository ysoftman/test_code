import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";

// Panda 는 PostCSS(@pandacss/dev/postcss) 로 동작 — vite 플러그인 불필요.
// Served from GitHub Pages at /test_code/css-framework-comparison/panda-css/
export default defineConfig(({ command }) => ({
  base:
    command === "build"
      ? "/test_code/css-framework-comparison/panda-css/"
      : "/",
  plugins: [react()],
}));
