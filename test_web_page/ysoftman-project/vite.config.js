import vue from "@vitejs/plugin-vue";
import path from "path";
import { defineConfig } from "vite";

// Served from GitHub Pages at /test_code/ysoftman-project/
export default defineConfig(({ command }) => ({
  base: command === "build" ? "/test_code/ysoftman-project/" : "/",
  plugins: [vue()],
  resolve: {
    alias: {
      "@": path.resolve(__dirname, "src"),
    },
  },
}));
