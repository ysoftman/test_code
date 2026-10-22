import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import tailwindcss from "@tailwindcss/vite";

// Served from GitHub Pages at /test_code/css-framework-comparison/tailwind/
export default defineConfig(({ command }) => ({
  base:
    command === "build" ? "/test_code/css-framework-comparison/tailwind/" : "/",
  plugins: [react(), tailwindcss()],
}));
