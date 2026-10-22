import react from "@vitejs/plugin-react";
import { defineConfig } from "vite";

// Served from GitHub Pages at /test_code/react-sample/
export default defineConfig(({ command }) => ({
  base: command === "build" ? "/test_code/react-sample/" : "/",
  plugins: [react()],
}));
