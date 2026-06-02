import vue from "@vitejs/plugin-vue";
import path from "path";
import { defineConfig } from "vite";

// Served from GitHub Pages at /test_code/ysoftman-vue-app/
export default defineConfig(({ command }) => ({
  base: command === "build" ? "/test_code/ysoftman-vue-app/" : "/",
  plugins: [vue()],
  resolve: {
    alias: {
      "@": path.resolve(__dirname, "src"),
    },
  },
}));
