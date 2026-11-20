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
		icon.innerHTML = `<svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="display:block"><path d="${t === "dark" ? "M12 8a4 4 0 1 0 0 8 4 4 0 0 0 0-8ZM12 2v2M12 20v2M4.93 4.93l1.41 1.41M17.66 17.66l1.41 1.41M2 12h2M20 12h2M6.34 17.66l-1.41 1.41M19.07 4.93l-1.41 1.41" : "M12 3a6 6 0 0 0 9 9 9 9 0 1 1-9-9Z"}"/></svg>`;
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
