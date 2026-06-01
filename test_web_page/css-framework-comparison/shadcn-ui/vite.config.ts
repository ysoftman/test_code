import { defineConfig } from "vite";
import { fileURLToPath, URL } from "node:url";
import react from "@vitejs/plugin-react";
import tailwindcss from "@tailwindcss/vite";

// Served from GitHub Pages at /test_code/css-framework-comparison/shadcn-ui/
export default defineConfig(({ command }) => ({
  base:
    command === "build"
      ? "/test_code/css-framework-comparison/shadcn-ui/"
      : "/",
  plugins: [react(), tailwindcss()],
  resolve: {
    alias: {
      "@": fileURLToPath(new URL("./src", import.meta.url)),
    },
  },
}));
