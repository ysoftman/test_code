(() => {
	let saved = null;
	try {
		saved = localStorage.getItem("theme");
	} catch {}
	const os = matchMedia("(prefers-color-scheme: dark)").matches;
	document.documentElement.dataset.theme = saved || (os ? "dark" : "light");
})();

addEventListener("DOMContentLoaded", () => {
	const root = document.documentElement;
	const icon = document.getElementById("theme-icon");
	const text = document.getElementById("theme-text");
	const update = (t) => {
		root.dataset.theme = t;
		icon.textContent = t === "dark" ? "☀️" : "🌙";
		text.textContent = t === "dark" ? "Light" : "Dark";
	};
	update(root.dataset.theme);
	document.getElementById("theme-btn").addEventListener("click", () => {
		const next = root.dataset.theme === "dark" ? "light" : "dark";
		update(next);
		try {
			localStorage.setItem("theme", next);
		} catch {}
	});
});
