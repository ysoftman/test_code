import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import { vanillaExtractPlugin } from "@vanilla-extract/vite-plugin";

// Served from GitHub Pages at /test_code/css-framework-comparison/vanilla-extract/
export default defineConfig(({ command }) => ({
  base:
    command === "build"
      ? "/test_code/css-framework-comparison/vanilla-extract/"
      : "/",
  plugins: [react(), vanillaExtractPlugin()],
}));
