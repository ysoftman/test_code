import { defineTheme } from "@astryxdesign/core/theme";
import { neutralTheme } from "@astryxdesign/theme-neutral";

// Neutral, unchanged in color and type, plus two page-level fixes:
// - keep-all breaks Korean lines between words (어절), not between syllables.
// - scrollMarginTop keeps anchored text (#features, #pricing, ...) clear of
//   AppShell's sticky TopNav when the page jumps to it.
const anchorClearance = "calc(var(--spacing-12) * 2)";

export const driftlogTheme = defineTheme({
	name: "driftlog",
	extends: neutralTheme,
	components: {
		text: {
			base: { wordBreak: "keep-all", scrollMarginTop: anchorClearance },
		},
		heading: {
			base: { wordBreak: "keep-all", scrollMarginTop: anchorClearance },
		},
	},
});
