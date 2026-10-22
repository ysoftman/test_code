import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";

// Served from GitHub Pages at /test_code/css-framework-comparison/styled-components/
export default defineConfig(({ command }) => ({
  base:
    command === "build"
      ? "/test_code/css-framework-comparison/styled-components/"
      : "/",
  plugins: [react()],
}));
