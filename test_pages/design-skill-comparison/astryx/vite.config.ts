import react from "@vitejs/plugin-react";
import { defineConfig } from "vite";

// GitHub Pages serves this build from /test_code/design-skill-comparison/astryx/,
// so every asset URL stays relative.
export default defineConfig({
	base: "./",
	plugins: [react()],
	build: {
		outDir: "dist",
		emptyOutDir: true,
	},
});
