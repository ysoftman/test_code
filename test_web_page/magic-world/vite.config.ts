import { defineConfig } from "vite";

export default defineConfig({
  base: "./",
  server: {
    port: 5199,
    open: true,
  },
  build: {
    target: "es2020",
  },
});
