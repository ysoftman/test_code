/** @type {import('tailwindcss').Config} */
// Semantic tokens come from design-system/driftlog/MASTER.md (+ pages/landing.md overrides).
// Values live as RGB channels in src/input.css so light/dark switch via prefers-color-scheme.
const token = (name) => `rgb(var(--${name}) / <alpha-value>)`;

module.exports = {
	content: ["./src/**/*.{html,js}"],
	darkMode: "media",
	// Level classes are built at runtime in app.js (`lvl-${level}`), so JIT cannot see them.
	safelist: ["lvl-info", "lvl-warn", "lvl-error"],
	theme: {
		extend: {
			colors: {
				bg: token("bg"),
				surface: token("surface"),
				muted: token("muted"),
				fg: token("fg"),
				"fg-muted": token("fg-muted"),
				line: token("line"),
				"line-strong": token("line-strong"),
				accent: token("accent"),
				"on-accent": token("on-accent"),
				"accent-ink": token("accent-ink"),
				focus: token("focus"),
				info: token("info"),
				warn: token("warn"),
				danger: token("danger"),
				code: {
					bg: token("code-bg"),
					panel: token("code-panel"),
					line: token("code-line"),
					fg: token("code-fg"),
					muted: token("code-muted"),
					info: token("code-info"),
					warn: token("code-warn"),
					error: token("code-error"),
					ok: token("code-ok"),
				},
			},
			fontFamily: {
				sans: [
					"Inter",
					'"Noto Sans KR"',
					"system-ui",
					"-apple-system",
					'"Apple SD Gothic Neo"',
					"sans-serif",
				],
				mono: [
					'"JetBrains Mono"',
					"ui-monospace",
					"SFMono-Regular",
					"Menlo",
					"monospace",
				],
			},
			maxWidth: {
				page: "1200px",
			},
			boxShadow: {
				sm: "0 1px 2px rgba(0,0,0,0.05)",
				md: "0 4px 6px rgba(0,0,0,0.1)",
				lg: "0 10px 15px rgba(0,0,0,0.1)",
				xl: "0 20px 25px rgba(0,0,0,0.15)",
			},
		},
	},
	plugins: [],
};
