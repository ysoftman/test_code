import "@astryxdesign/core/reset.css";
import "@astryxdesign/core/astryx.css";
import { Theme } from "@astryxdesign/core/theme";
import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import { defaultThemeSlug, themes } from "./astryx-themes";
import LandingPage from "./page";

const root = document.getElementById("root");
if (root == null) {
	throw new Error("Missing #root element");
}

// Theme mode defaults to 'system', so light/dark follows prefers-color-scheme.
createRoot(root).render(
	<StrictMode>
		<Theme theme={themes[defaultThemeSlug]}>
			<LandingPage />
		</Theme>
	</StrictMode>,
);
