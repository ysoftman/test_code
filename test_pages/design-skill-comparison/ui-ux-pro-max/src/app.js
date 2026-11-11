(() => {
	const $ = (sel, root = document) => root.querySelector(sel);
	const $$ = (sel, root = document) => Array.from(root.querySelectorAll(sel));
	const reduceMotion = window.matchMedia("(prefers-reduced-motion: reduce)");

	/* ---------- Mobile menu ---------- */
	const menuBtn = $("#menu-button");
	const menu = $("#mobile-menu");
	if (menuBtn && menu) {
		const setOpen = (open) => {
			menuBtn.setAttribute("aria-expanded", String(open));
			menuBtn.setAttribute("aria-label", open ? "메뉴 닫기" : "메뉴 열기");
			$("[data-icon-open]", menuBtn).classList.toggle("hidden", open);
			$("[data-icon-close]", menuBtn).classList.toggle("hidden", !open);
			menu.hidden = !open;
		};
		menuBtn.addEventListener("click", () =>
			setOpen(menuBtn.getAttribute("aria-expanded") !== "true"),
		);
		menu.addEventListener("click", (e) => {
			if (e.target.closest("a")) setOpen(false);
		});
		document.addEventListener("keydown", (e) => {
			if (
				e.key === "Escape" &&
				menuBtn.getAttribute("aria-expanded") === "true"
			) {
				setOpen(false);
				menuBtn.focus();
			}
		});
		window.matchMedia("(min-width: 768px)").addEventListener("change", (e) => {
			if (e.matches) setOpen(false);
		});
	}

	/* ---------- Scroll spy for nav-state-active ---------- */
	const spyLinks = $$("[data-spy]");
	if (spyLinks.length && "IntersectionObserver" in window) {
		const spy = new IntersectionObserver(
			(entries) => {
				entries.forEach((entry) => {
					if (!entry.isIntersecting) return;
					spyLinks.forEach((link) => {
						if (link.dataset.spy === entry.target.id)
							link.setAttribute("aria-current", "true");
						else link.removeAttribute("aria-current");
					});
				});
			},
			{ rootMargin: "-45% 0px -50% 0px" },
		);
		["top", "features", "pricing", "faq"].forEach((id) => {
			const el = document.getElementById(id);
			if (el) spy.observe(el);
		});
	}

	/* ---------- Copy install command ---------- */
	const copyStatus = $("#copy-status");
	$$("[data-copy-target]").forEach((btn) => {
		const label = $("[data-copy-label]", btn);
		let resetTimer;
		btn.addEventListener("click", async () => {
			const text = document
				.getElementById(btn.dataset.copyTarget)
				.textContent.trim();
			let msg = "복사됨";
			try {
				await navigator.clipboard.writeText(text);
			} catch {
				msg = "복사 실패";
			}
			label.textContent = msg;
			if (copyStatus)
				copyStatus.textContent =
					msg === "복사됨"
						? "설치 명령을 클립보드에 복사했습니다."
						: "복사하지 못했습니다. 직접 선택해 복사해 주세요.";
			clearTimeout(resetTimer);
			resetTimer = setTimeout(() => (label.textContent = "복사"), 2000);
		});
	});

	/* ---------- Interactive log search demo ---------- */
	const app = $("#demo-app");
	if (!app) return;

	const form = $("#query-form");
	const input = $("#query");
	const runBtn = $("#run-button");
	const list = $("#log-list");
	const empty = $("#log-empty");
	const meta = $("#result-meta");
	const queryStatus = $("#query-status");
	const histogram = $("#histogram");
	const tailBtn = $("#tail-button");
	const tailText = $("[data-tail-text]");
	const tailIcon = $("[data-tail-icon] use");
	const MAX_LINES = 9;

	const NS = {
		checkout: "prod",
		payments: "prod",
		gateway: "prod",
		inventory: "prod",
		auth: "staging",
		"batch-report": "staging",
	};
	const TEMPLATES = {
		info: [
			[
				"checkout",
				() =>
					`order placed id=${hex()} items=${int(1, 6)} total=${int(12, 240) * 100}`,
			],
			["gateway", () => `GET /api/v1/cart 200 ${int(12, 90)}ms`],
			[
				"inventory",
				() => `stock synced sku=SKU-${int(1000, 9999)} qty=${int(1, 400)}`,
			],
			["auth", () => `token refreshed user=u_${hex()}`],
			[
				"payments",
				() => `charge captured id=pay_${hex()} amount=${int(5, 90) * 1000}`,
			],
			["batch-report", () => `daily report chunk ${int(1, 40)}/40 written`],
		],
		warn: [
			[
				"payments",
				() =>
					`retrying PG request attempt=${int(2, 3)}/3 latency=${int(900, 2400)}ms`,
			],
			["gateway", () => `slow upstream checkout-svc p99=${int(1200, 2900)}ms`],
			["inventory", () => `cache miss ratio ${int(31, 48)}% above threshold`],
		],
		error: [
			["checkout", () => `payment timeout after 3000ms order=${hex()}`],
			["payments", () => `upstream returned 502 Bad Gateway pg=kcp-2`],
			[
				"gateway",
				() => `circuit open for checkout-svc (5 consecutive failures)`,
			],
		],
	};

	function int(min, max) {
		return Math.floor(Math.random() * (max - min + 1)) + min;
	}
	function hex() {
		return Math.random().toString(16).slice(2, 6);
	}

	// Deterministic seed data so the first paint is always the same
	const SEED = [
		[
			"14:21:08.912",
			"error",
			"checkout",
			"payment timeout after 3000ms order=9b1e",
		],
		["14:21:08.604", "info", "gateway", "GET /api/v1/cart 200 41ms"],
		[
			"14:21:08.217",
			"warn",
			"payments",
			"retrying PG request attempt=2/3 latency=2140ms",
		],
		[
			"14:21:07.955",
			"error",
			"payments",
			"upstream returned 502 Bad Gateway pg=kcp-2",
		],
		[
			"14:21:07.412",
			"info",
			"checkout",
			"order placed id=8f2c items=3 total=48000",
		],
		["14:21:06.880", "info", "inventory", "stock synced sku=SKU-4821 qty=120"],
		[
			"14:21:06.301",
			"warn",
			"gateway",
			"slow upstream checkout-svc p99=2310ms",
		],
		["14:21:05.776", "info", "auth", "token refreshed user=u_31af"],
		[
			"14:21:05.190",
			"error",
			"gateway",
			"circuit open for checkout-svc (5 consecutive failures)",
		],
		[
			"14:21:04.633",
			"info",
			"payments",
			"charge captured id=pay_77d0 amount=32000",
		],
		[
			"14:21:04.002",
			"warn",
			"inventory",
			"cache miss ratio 42% above threshold",
		],
		[
			"14:21:03.518",
			"info",
			"batch-report",
			"daily report chunk 12/40 written",
		],
		[
			"14:21:02.947",
			"error",
			"checkout",
			"payment timeout after 3000ms order=c40a",
		],
		["14:21:02.311", "info", "gateway", "GET /api/v1/cart 200 18ms"],
		[
			"14:21:01.760",
			"info",
			"checkout",
			"order placed id=1d9e items=1 total=12000",
		],
	];
	const lines = SEED.map(([time, level, appName, msg]) => ({
		time,
		level,
		app: appName,
		ns: NS[appName],
		msg,
	}));

	// Mock clock continues from the newest seed line
	let clockMs = toMs(SEED[0][0]);
	function toMs(t) {
		const [h, m, rest] = t.split(":");
		return ((+h * 60 + +m) * 60 + parseFloat(rest)) * 1000;
	}
	function fmt(ms) {
		const pad = (n, l = 2) => String(n).padStart(l, "0");
		const total = Math.floor(ms);
		const h = Math.floor(total / 3600000) % 24;
		const m = Math.floor(total / 60000) % 60;
		const s = Math.floor(total / 1000) % 60;
		return `${pad(h)}:${pad(m)}:${pad(s)}.${pad(total % 1000, 3)}`;
	}

	/* Query parsing: {label="value", ...} |= "text" != "text" | level="error"  — or plain text */
	function parse(raw) {
		const q = {
			labels: {},
			contains: [],
			excludes: [],
			level: null,
			invalid: false,
		};
		const text = raw.trim();
		if (!text) return q;
		const selector = text.match(/^\{([^}]*)\}/);
		if (!selector && !/\|=|!=|\|~/.test(text)) {
			q.contains.push(text.toLowerCase());
			return q;
		}
		if (selector) {
			for (const m of selector[1].matchAll(/(\w+)\s*=\s*"([^"]*)"/g))
				q.labels[m[1]] = m[2];
		}
		for (const m of text.matchAll(/\|[=~]\s*"([^"]*)"/g))
			q.contains.push(m[1].toLowerCase());
		for (const m of text.matchAll(/!=\s*"([^"]*)"/g))
			q.excludes.push(m[1].toLowerCase());
		const lvl = text.match(/\|\s*level\s*=\s*"?(\w+)"?/i);
		if (lvl) q.level = lvl[1].toLowerCase();
		return q;
	}

	const state = {
		query: parse(input.value),
		level: "all",
		live: false,
		visible: false,
	};

	function matches(line) {
		const { labels, contains, excludes, level } = state.query;
		for (const [k, v] of Object.entries(labels)) {
			const value =
				k === "namespace"
					? line.ns
					: k === "app"
						? line.app
						: k === "level"
							? line.level
							: undefined;
			if (value !== v) return false;
		}
		const hay = `${line.app} ${line.msg}`.toLowerCase();
		if (contains.some((c) => !hay.includes(c))) return false;
		if (excludes.some((c) => hay.includes(c))) return false;
		if (level && line.level !== level) return false;
		if (state.level !== "all" && line.level !== state.level) return false;
		return true;
	}

	function highlight(el, text) {
		const terms = state.query.contains.filter(Boolean);
		if (!terms.length) {
			el.textContent = text;
			return;
		}
		const lower = text.toLowerCase();
		let i = 0;
		while (i < text.length) {
			let next = -1;
			let term = "";
			for (const t of terms) {
				const idx = lower.indexOf(t, i);
				if (idx !== -1 && (next === -1 || idx < next)) {
					next = idx;
					term = t;
				}
			}
			if (next === -1) {
				el.append(text.slice(i));
				break;
			}
			if (next > i) el.append(text.slice(i, next));
			const mark = document.createElement("mark");
			mark.textContent = text.slice(next, next + term.length);
			el.append(mark);
			i = next + term.length;
		}
	}

	function lineEl(line, isNew = false) {
		const li = document.createElement("li");
		li.className = "log-line" + (isNew ? " is-new" : "");
		const time = document.createElement("span");
		time.className = "tabular text-code-muted";
		time.textContent = line.time.slice(0, 8);
		const ms = document.createElement("span");
		ms.className = "hidden sm:inline";
		ms.textContent = line.time.slice(8);
		time.append(ms);
		const lvl = document.createElement("span");
		lvl.className = `lvl lvl-${line.level}`;
		lvl.textContent = line.level.toUpperCase();
		const appEl = document.createElement("span");
		appEl.className = "hidden truncate text-code-info md:block";
		appEl.textContent = line.app;
		appEl.title = `namespace=${line.ns} app=${line.app}`;
		const msg = document.createElement("span");
		msg.className = "log-msg min-w-0 break-words text-code-fg";
		const appPrefix = document.createElement("span");
		appPrefix.className = "text-code-info md:hidden";
		appPrefix.textContent = `${line.app} `;
		msg.append(appPrefix);
		const body = document.createElement("span");
		highlight(body, line.msg);
		msg.append(body);
		li.append(time, lvl, appEl, msg);
		return li;
	}

	function render() {
		const hits = lines.filter(matches);
		list.replaceChildren(...hits.slice(0, MAX_LINES).map((l) => lineEl(l)));
		empty.classList.toggle("hidden", hits.length > 0);
		return hits.length;
	}

	function setMeta(count, seconds) {
		meta.textContent =
			`${count.toLocaleString("ko-KR")}개 라인 일치` +
			(seconds ? ` · ${seconds}초` : "");
	}

	/* ---------- Histogram (2-minute buckets, last 60 minutes) ---------- */
	const seeded = (() => {
		let s = 7;
		return () => {
			s = (s * 1664525 + 1013904223) % 4294967296;
			return s / 4294967296;
		};
	})();
	const SPIKE = { 23: 70, 24: 156, 25: 118, 26: 38 };
	const buckets = Array.from({ length: 30 }, (_, i) => ({
		info: 150 + Math.round(40 * Math.sin(i / 3.5)) + Math.round(seeded() * 30),
		warn: 12 + Math.round(seeded() * 14) + (SPIKE[i] ? 26 : 0),
		error: 3 + Math.round(seeded() * 5) + (SPIKE[i] || 0),
	}));

	function renderHistogram() {
		const max = Math.max(...buckets.map((b) => b.info + b.warn + b.error));
		const frag = document.createDocumentFragment();
		buckets.forEach((b, i) => {
			const col = document.createElement("div");
			col.className = "relative flex h-full flex-col-reverse overflow-visible";
			const total = b.info + b.warn + b.error;
			const pct = (n) => `${(n / max) * 100}%`;
			[
				["info", b.info],
				["warn", b.warn],
				["error", b.error],
			].forEach(([lvl, n], idx, arr) => {
				const seg = document.createElement("span");
				seg.className =
					`seg seg-${lvl}` + (idx === arr.length - 1 ? " rounded-t-[2px]" : "");
				seg.style.height = pct(n);
				col.append(seg);
			});
			if (i === 24) {
				const note = document.createElement("span");
				note.className =
					"pointer-events-none absolute right-0 flex items-center gap-1 whitespace-nowrap rounded bg-code-error/15 px-1.5 py-0.5 font-mono text-[10px] font-semibold text-code-error";
				note.style.bottom = `calc(${(total / max) * 100}% + 4px)`;
				note.innerHTML =
					'<svg class="icon h-3 w-3" aria-hidden="true"><use href="#i-alert"/></svg>ERROR 급증';
				col.append(note);
			}
			frag.append(col);
		});
		histogram.replaceChildren(frag);
		const peak = buckets[24];
		histogram.setAttribute(
			"aria-label",
			`최근 60분 로그량 히스토그램, 2분 단위 30구간. 평소 2분당 약 ${Math.round(buckets[5].info + buckets[5].warn + buckets[5].error)}건이며, ` +
				`12분 전 ERROR가 2분간 ${peak.error}건으로 급증했습니다.`,
		);
	}

	/* ---------- Query submit with loading feedback ---------- */
	function setBusy(busy) {
		runBtn.disabled = busy;
		runBtn.classList.toggle("opacity-70", busy);
		$("[data-spinner]", runBtn).classList.toggle("hidden", !busy);
		$("[data-run-label]", runBtn).textContent = busy ? "검색 중" : "실행";
		list.setAttribute("aria-busy", String(busy));
		list.classList.toggle("opacity-50", busy);
	}

	function runQuery(announce = true) {
		state.query = parse(input.value);
		if (
			state.query.level &&
			["info", "warn", "error"].includes(state.query.level)
		)
			setLevel(state.query.level, false);
		setBusy(true);
		const started = performance.now();
		setTimeout(() => {
			setBusy(false);
			const count = render();
			const seconds = (
				0.31 +
				(performance.now() - started) / 1000 +
				Math.random() * 0.4
			).toFixed(2);
			setMeta(count, seconds);
			if (announce)
				queryStatus.textContent = count
					? `${count}개 로그 라인을 찾았습니다.`
					: "일치하는 로그가 없습니다. 추천 쿼리를 사용해 보세요.";
		}, 380);
	}

	form.addEventListener("submit", (e) => {
		e.preventDefault();
		if (!runBtn.disabled) runQuery();
	});

	for (const chip of $$("[data-preset]")) {
		chip.addEventListener("click", () => {
			input.value = chip.dataset.preset;
			runQuery();
		});
	}

	/* ---------- Level filter ---------- */
	const levelBtns = $$(".level-btn");
	function setLevel(level, rerender = true) {
		state.level = level;
		for (const b of levelBtns)
			b.setAttribute("aria-pressed", String(b.dataset.level === level));
		if (level === "all") histogram.removeAttribute("data-filter");
		else histogram.setAttribute("data-filter", level);
		if (rerender) {
			const count = render();
			setMeta(count);
		}
	}
	for (const b of levelBtns)
		b.addEventListener("click", () => setLevel(b.dataset.level));

	/* ---------- "/" focuses the query (keyboard-shortcuts must-have for dev tools) ---------- */
	document.addEventListener("keydown", (e) => {
		if (e.key !== "/" || e.metaKey || e.ctrlKey || e.altKey || !state.visible)
			return;
		if (e.target.closest("input, textarea, select, [contenteditable='true']"))
			return;
		e.preventDefault();
		input.focus();
		input.select();
	});

	/* ---------- Live tail ---------- */
	let timer = null;

	function makeLine() {
		const r = Math.random();
		const level = r < 0.68 ? "info" : r < 0.88 ? "warn" : "error";
		const pool = TEMPLATES[level];
		const [appName, msg] = pool[Math.floor(Math.random() * pool.length)];
		clockMs += int(250, 1400);
		return {
			time: fmt(clockMs),
			level,
			app: appName,
			ns: NS[appName],
			msg: msg(),
		};
	}

	function tick() {
		const line = makeLine();
		lines.unshift(line);
		if (lines.length > 300) lines.pop();
		buckets[buckets.length - 1][line.level] += 1;
		renderHistogram();
		if (!matches(line)) return;
		list.prepend(lineEl(line, !reduceMotion.matches));
		while (list.children.length > MAX_LINES) list.lastElementChild.remove();
		empty.classList.add("hidden");
		setMeta(lines.filter(matches).length);
	}

	function syncTail() {
		const running = state.live && state.visible && !document.hidden;
		if (running && !timer) timer = setInterval(tick, 1300);
		if (!running && timer) {
			clearInterval(timer);
			timer = null;
		}
		app.dataset.live = state.live ? "on" : "off";
		tailBtn.setAttribute("aria-pressed", String(state.live));
		tailText.textContent = state.live ? "실시간 수신 중" : "일시정지됨";
		tailIcon.setAttribute("href", state.live ? "#i-pause" : "#i-play");
	}

	tailBtn.addEventListener("click", () => {
		state.live = !state.live;
		syncTail();
	});
	document.addEventListener("visibilitychange", syncTail);

	if ("IntersectionObserver" in window) {
		new IntersectionObserver(
			([entry]) => {
				state.visible = entry.isIntersecting;
				syncTail();
			},
			{ threshold: 0.25 },
		).observe(app);
	} else {
		state.visible = true;
	}

	// Auto-start the stream only when motion is welcome; otherwise the user opts in.
	state.live = !reduceMotion.matches;
	reduceMotion.addEventListener("change", (e) => {
		if (e.matches) {
			state.live = false;
			syncTail();
		}
	});

	renderHistogram();
	setMeta(render(), "0.42");
	syncTail();
})();
