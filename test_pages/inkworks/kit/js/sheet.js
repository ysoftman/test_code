/* =========================================================================
   Inkworks: the page around a mechanism.
   Builds the DOM from the mechanism's metadata, owns the state, the loop,
   the layout (sheet or figure), controls, gauge, charts, callouts and tags.
   A mechanism only supplies geometry + kinematics + words (see mechanisms/).
   ========================================================================= */
import { makeKit, THREE, D2R, mod, clamp01, INK_HEX, PAPER_HEX } from './kit.js';

const $ = (id) => document.getElementById(id);
const h = (html) => { const t = document.createElement('template'); t.innerHTML = html.trim(); return t.content.firstChild; };
const esc = (s) => String(s).replace(/[&<>"]/g, (c) => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;' }[c]));
const ICON = {
  prev: '<svg viewBox="0 0 24 24"><path d="M6 5v14M19 5 9 12l10 7z"/></svg>',
  next: '<svg viewBox="0 0 24 24"><path d="M18 5v14M5 5l10 7-10 7z"/></svg>',
  pause: '<svg viewBox="0 0 24 24" class="i-pause"><path d="M8 5v14M16 5v14"/></svg>',
  play: '<svg viewBox="0 0 24 24" class="i-play"><path d="M7 5l12 7-12 7z"/></svg>',
};
const speedLabel = (s) => (s === 1 ? '1x' : `1/${s}`);

export function createSheet(mech, { layout: forcedLayout } = {}) {
  const q = new URLSearchParams(location.search);
  const layoutName = forcedLayout || q.get('layout') || document.body.dataset.layout || mech.meta.layout || 'sheet';
  document.body.dataset.layout = layoutName;
  const figure = layoutName === 'figure';
  const N = mech.instances.count;
  const CYCLE = mech.cycle;
  const EPS = CYCLE / 180;                       // land a hair inside a phase, not on its edge
  const P = mech.phases;
  document.documentElement.style.setProperty('--n-phases', P.length);
  P.forEach((p, k) => document.documentElement.style.setProperty(`--ph${k}`, p.color));
  if (mech.meta.pageTitle) document.title = mech.meta.pageTitle;

  /* ---------------- DOM ---------------- */
  buildDom(mech, figure);

  /* ---------------- state ---------------- */
  const reduceMotion = matchMedia('(prefers-reduced-motion: reduce)').matches;
  const D = mech.driver;
  const layers = { callouts: true, orbit: false };
  (mech.layers || []).forEach((l) => { layers[l.key] = l.on !== false; });
  const state = {
    theta: mech.start ?? 0,        // the ONE driver variable: cycle degrees, unbounded
    playing: !reduceMotion,
    input: D.input,                // 0..1 from the slider
    rate: D.start ?? D.target(D.input),
    slow: mech.speed ?? mech.speeds[1] ?? mech.speeds[0],
    focus: 0,
    tween: null,
    scrubbing: false,
    phi: new Array(N).fill(0),
    layers,
    mech: {},                      // mechanism-private state (tyre pressure, heat...)
  };
  const bounds = () => (mech.bounds ? mech.bounds(state) : P.map((_, k) => (k * CYCLE) / P.length));
  const phaseOf = (phi, b = bounds()) => { let k = 0; for (let j = 0; j < b.length; j++) if (phi >= b[j]) k = j; return k; };
  const phiOf = (i, theta = state.theta) => mod(theta - (mech.instances.offset?.[i] ?? 0), CYCLE);
  const api = { state, phaseOf, phiOf, bounds, cycle: CYCLE };

  /* ---------------- 3D ---------------- */
  const stageEl = $('stage');
  const kit = makeKit($('gl'));
  const { renderer, scene, camera, controls } = kit;
  const V = mech.view;
  const TARGET = new THREE.Vector3(...V.target);
  const VIEW_DIR = new THREE.Vector3(...V.dir).normalize();
  controls.target.copy(TARGET);
  controls.minDistance = V.minDist ?? 5;
  controls.maxDistance = V.maxDist ?? 40;
  const model = mech.build(kit, api);
  if (model.root && !model.root.parent) scene.add(model.root);
  for (let i = 0; i < N; i++) state.phi[i] = phiOf(i);
  model.pose(state.theta, 0, state);

  /* ---------------- controls ---------------- */
  const playBtn = $('playBtn');
  function setPlaying(p) {
    state.playing = p;
    playBtn.classList.toggle('paused', !p);
    playBtn.setAttribute('aria-label', p ? 'Pause' : 'Play');
  }
  setPlaying(state.playing);
  playBtn.addEventListener('click', () => { state.tween = null; setPlaying(!state.playing); });

  function jumpTo(phiTarget, dir = 0) {
    const cur = state.phi[state.focus];
    let d = mod(phiTarget - cur, CYCLE);
    if (dir < 0 && d > 0) d -= CYCLE;                 // stepping back always goes back
    else if (dir === 0 && d > CYCLE / 2) d -= CYCLE;  // clicked phase: shortest way round
    state.tween = { from: state.theta, to: state.theta + d, t: 0, dur: 0.5 + (Math.abs(d) / CYCLE) * 0.9 };
    setPlaying(false);
  }
  const stepPhase = (dir) => {
    const b = bounds(), phi = state.phi[state.focus], k = phaseOf(phi, b);
    if (dir > 0) jumpTo(b[(k + 1) % b.length] + EPS, 1);
    else {
      const into = mod(phi - b[k], CYCLE);
      const back = into > (CYCLE / 24) ? k : (k - 1 + b.length) % b.length;
      jumpTo(b[back] + EPS, -1);
    }
  };
  $('nextBtn').addEventListener('click', () => stepPhase(1));
  $('prevBtn').addEventListener('click', () => stepPhase(-1));
  addEventListener('keydown', (e) => {
    if (e.target.closest('input, button, [tabindex]')) return;
    if (e.code === 'Space') { e.preventDefault(); setPlaying(!state.playing); }
    if (e.key === 'ArrowRight') stepPhase(1);
    if (e.key === 'ArrowLeft') stepPhase(-1);
  });

  const phaseListEls = [...document.querySelectorAll('#phaseList li')];
  phaseListEls.forEach((li) => {
    li.tabIndex = 0;
    const go = () => jumpTo(bounds()[+li.dataset.s] + EPS);
    li.addEventListener('click', go);
    li.addEventListener('keydown', (e) => { if (e.key === 'Enter' || e.key === ' ') { e.preventDefault(); go(); } });
  });

  function setFocus(i) {
    state.focus = i;
    document.querySelectorAll('#focusSeg button').forEach((x) => x.classList.toggle('on', +x.dataset.c === i));
    for (const id of ['plotInst', 'chipInst']) { const el = $(id); if (el) el.textContent = i + 1; }
    shownPhase = -1;
    model.focusChanged?.(i, state);
  }
  document.querySelectorAll('#focusSeg button').forEach((b) => b.addEventListener('click', () => setFocus(+b.dataset.c)));

  const drive = $('drive');
  const setInput = () => {
    state.input = drive.value / 100;
    $('driveVal').textContent = D.inputFormat ? D.inputFormat(state.input) : `${drive.value}%`;
    drive.style.setProperty('--fill', `${drive.value}%`);
  };
  drive.value = Math.round(D.input * 100);
  drive.addEventListener('input', setInput);
  setInput();

  document.querySelectorAll('#slowSeg button').forEach((b) => b.addEventListener('click', () => {
    state.slow = +b.dataset.s;
    document.querySelectorAll('#slowSeg button').forEach((x) => x.classList.toggle('on', x === b));
    const sv = $('slowVal'); if (sv) sv.textContent = `${speedLabel(state.slow)} speed`;
  }));

  (mech.actions || []).forEach((a, k) => {
    const b = $(`act${k}`);
    if (b) b.addEventListener('click', () => a.run(state, api));
  });

  document.querySelectorAll('.tog').forEach((b) => b.addEventListener('click', () => {
    const k = b.dataset.layer;
    layers[k] = !layers[k];
    b.classList.toggle('on', layers[k]);
    b.setAttribute('aria-pressed', String(layers[k]));
    applyLayers();
  }));
  function applyLayers() {
    for (const l of mech.layers || []) model.setLayer?.(l.key, layers[l.key]);
    stageEl.classList.toggle('no-callouts', !layers.callouts);
    controls.autoRotate = layers.orbit;
  }
  applyLayers();

  /* ---------------- phase panel / status ---------------- */
  let shownPhase = -1;
  const roBox = $('readout');
  const readoutEls = (model.readouts || []).map((r) => {
    if (!roBox) return null;
    const row = h(`<div><dt>${esc(r.label)}</dt><dd></dd></div>`);
    roBox.appendChild(row);
    return row.lastChild;
  });
  function updatePanel() {
    const i = state.focus, phi = state.phi[i], s = phaseOf(phi);
    if (s !== shownPhase) {
      shownPhase = s;
      const d = P[s];
      const set = (id, v) => { const el = $(id); if (el) el.textContent = v; };
      set('phaseNum', String(s + 1).padStart(2, '0'));
      set('phaseName', d.name);
      set('phaseNick', `"${d.nick}"`);
      set('phaseText', d.text);
      set('chipPhase', d.name);
      document.body.style.setProperty('--accent', d.color);
      phaseListEls.forEach((li) => li.classList.toggle('on', +li.dataset.s === s));
    }
    const ctx = { phi, i, s: state, phase: s, api };
    (model.readouts || []).forEach((r, k) => {
      const el = readoutEls[k]; if (!el) return;
      const v = r.value(ctx);
      const text = typeof v === 'string' ? v : v.text;
      if (el.textContent !== text) el.textContent = text;
      el.className = (typeof v === 'object' && v.cls) || '';
    });
    const st = $('statusSpeed');
    if (st) {
      st.textContent = `Shown at ${speedLabel(state.slow)} speed`;
      $('statusPlay').textContent = state.tween ? 'stepping' : state.scrubbing ? 'scrubbing' : state.playing ? 'running' : 'paused';
    }
  }

  /* ---------------- gauge ---------------- */
  const G = mech.gauge;
  let needle = null;
  const A0 = -210, A1 = 30;
  const gPt = (v, r) => { const a = (A0 + (A1 - A0) * clamp01(v / G.max)) * D2R; return [100 + r * Math.cos(a), 100 + r * Math.sin(a)]; };
  if ($('gauge') && G) {
    let s = '';
    if (G.red != null) {
      const [rx0, ry0] = gPt(G.red, 88), [rx1, ry1] = gPt(G.max, 88);
      const big = (G.max - G.red) / G.max * 240 > 180 ? 1 : 0;
      s += `<path d="M${rx0} ${ry0} A88 88 0 ${big} 1 ${rx1} ${ry1}" fill="none" stroke="#e5482f" stroke-width="4"/>`;
    }
    const [ax0, ay0] = gPt(0, 92), [ax1, ay1] = gPt(G.max, 92);
    s += `<path d="M${ax0} ${ay0} A92 92 0 1 1 ${ax1} ${ay1}" fill="none" stroke="rgba(22,27,38,.6)" stroke-width="1"/>`;
    for (let v = 0; v <= G.max + 1e-6; v += G.minor) {
      const major = Math.abs(v / G.major - Math.round(v / G.major)) < 1e-6;
      const [x0, y0] = gPt(v, major ? 78 : 83), [x1, y1] = gPt(v, 91);
      s += `<line x1="${x0}" y1="${y0}" x2="${x1}" y2="${y1}" stroke="${G.red != null && v >= G.red ? '#e5482f' : INK_HEX}" stroke-width="${major ? 1.6 : 0.8}"/>`;
      if (major) { const [tx, ty] = gPt(v, 66); s += `<text x="${tx}" y="${ty + 3.5}" text-anchor="middle" font-family="Geist Mono" font-size="10" fill="rgba(22,27,38,.8)">${G.tick ? G.tick(v) : v}</text>`; }
    }
    s += `<text x="100" y="58" text-anchor="middle" font-family="Geist Mono" font-size="7" letter-spacing="1.2" fill="rgba(22,27,38,.45)">${esc(G.label)}</text>`;
    s += `<g id="needle"><line x1="100" y1="100" x2="100" y2="22" stroke="#e5482f" stroke-width="2" stroke-linecap="round"/><line x1="100" y1="100" x2="100" y2="114" stroke="#e5482f" stroke-width="2.2"/></g>`;
    s += `<circle cx="100" cy="100" r="6" fill="${PAPER_HEX}" stroke="${INK_HEX}" stroke-width="1.3"/>`;
    $('gauge').innerHTML = s;
    needle = $('gauge').querySelector('#needle');
  }
  function updateGauge() {
    if (!needle) return;
    const v = G.value(state);
    $('gaugeVal').textContent = G.readout ? G.readout(v) : Math.round(v);
    needle.setAttribute('transform', `rotate(${A0 + (A1 - A0) * clamp01(v / G.max) + 90} 100 100)`);
  }

  /* ---------------- cycle chart ---------------- */
  const chart = $('chart');
  const cctx = chart?.getContext('2d');
  const plot = $('plot');
  const pctx = plot?.getContext('2d');
  let chartW = 0, chartH = 0;
  function sizeCharts() {
    if (chart) {
      const r = chart.getBoundingClientRect();
      const dpr = Math.min(devicePixelRatio, 2);
      chartW = r.width; chartH = r.height;
      chart.width = Math.round(r.width * dpr); chart.height = Math.round(r.height * dpr);
      cctx.setTransform(dpr, 0, 0, dpr, 0, 0);
    }
    if (plot) {   // the plot draws in 2x canvas pixels; size from the box so it never squashes
      const pr = plot.getBoundingClientRect();
      if (pr.width) { plot.width = Math.round(pr.width * 2); plot.height = Math.round(pr.height * 2); }
    }
  }
  const GUT = 52;
  const rowCount = () => N;
  function drawChart() {
    const W = chartW, H = chartH, ctx = cctx;
    if (!W) return;
    ctx.clearRect(0, 0, W, H);
    const top = 4, axisH = 16, rowH = (H - top - axisH) / rowCount();
    const xOf = (deg) => GUT + (W - GUT - 6) * deg / CYCLE;
    const b = bounds();
    ctx.font = '500 10px Geist Mono';
    ctx.textBaseline = 'middle';
    for (let i = 0; i < N; i++) {
      const y = top + i * rowH;
      const focus = i === state.focus;
      const off = mech.instances.offset?.[i] ?? 0;
      ctx.fillStyle = focus ? INK_HEX : 'rgba(22,27,38,.5)';
      ctx.fillText(N > 1 ? `${mech.instances.short.toUpperCase()} ${i + 1}` : mech.instances.short.toUpperCase(), 4, y + rowH / 2);
      for (let s = 0; s < P.length; s++) {
        const len = mod((b[(s + 1) % b.length] ?? CYCLE) - b[s], CYCLE) || CYCLE;
        const start = mod(off + b[s], CYCLE);
        const segs = start + len > CYCLE ? [[start, CYCLE], [0, start + len - CYCLE]] : [[start, start + len]];
        segs.forEach(([a, z]) => {
          const x0 = xOf(a), x1 = xOf(z);
          ctx.fillStyle = P[s].color;
          ctx.globalAlpha = focus ? 0.92 : 0.28;
          ctx.fillRect(x0 + 1, y + 3, Math.max(0, x1 - x0 - 2), rowH - 6);
          ctx.globalAlpha = 1;
          if (x1 - x0 > ctx.measureText(P[s].short).width + 14) {
            ctx.fillStyle = focus ? '#ffffff' : 'rgba(22,27,38,.6)';
            ctx.fillText(P[s].short, x0 + 7, y + rowH / 2 + 0.5);
          }
        });
      }
      for (const m of mech.chart?.markers || []) {
        const at = typeof m.at === 'function' ? m.at(state) : m.at;
        const sx = xOf(mod(off + at, CYCLE));
        ctx.strokeStyle = focus ? '#ffffff' : INK_HEX; ctx.lineWidth = 1.4;
        ctx.beginPath();
        if (m.kind === 'spark') { ctx.moveTo(sx - 3, y + 5); ctx.lineTo(sx + 1, y + rowH / 2); ctx.lineTo(sx - 2, y + rowH / 2); ctx.lineTo(sx + 2, y + rowH - 5); }
        else { ctx.moveTo(sx, y + 4); ctx.lineTo(sx, y + rowH - 4); }
        ctx.stroke();
      }
    }
    ctx.strokeStyle = 'rgba(22,27,38,.4)'; ctx.lineWidth = 1;
    ctx.fillStyle = 'rgba(22,27,38,.5)';
    ctx.textAlign = 'center';
    const step = CYCLE / 8;
    for (let d = 0; d <= CYCLE + 1e-6; d += step) {
      const x = xOf(d);
      ctx.beginPath(); ctx.moveTo(x, H - axisH); ctx.lineTo(x, H - axisH + 4); ctx.stroke();
      if (W > 520 || Math.round(d / step) % 2 === 0) ctx.fillText(`${Math.round(d)}°`, Math.min(Math.max(x, GUT + 10), W - 16), H - 6);
    }
    ctx.textAlign = 'left';
    const x = xOf(mod(state.theta, CYCLE));
    ctx.strokeStyle = INK_HEX; ctx.lineWidth = 1.5;
    ctx.beginPath(); ctx.moveTo(x, 0); ctx.lineTo(x, H - axisH); ctx.stroke();
    ctx.fillStyle = INK_HEX;
    ctx.beginPath(); ctx.moveTo(x - 5, 0); ctx.lineTo(x + 5, 0); ctx.lineTo(x, 6); ctx.fill();
  }
  let scrubWasPlaying = false;
  function scrubAt(e) {
    const r = chart.getBoundingClientRect();
    const deg = clamp01((e.clientX - r.left - GUT) / (r.width - GUT - 6)) * CYCLE;
    let d = deg - mod(state.theta, CYCLE);
    if (d > CYCLE / 2) d -= CYCLE; if (d < -CYCLE / 2) d += CYCLE;
    state.theta += d;
  }
  if (chart) {
    chart.addEventListener('pointerdown', (e) => {
      const r = chart.getBoundingClientRect();
      if (e.clientX - r.left < GUT) {   // row label: follow that instance
        const row = Math.floor((e.clientY - r.top - 4) / ((r.height - 20) / rowCount()));
        if (row >= 0 && row < N) setFocus(row);
        return;
      }
      chart.setPointerCapture(e.pointerId);
      state.scrubbing = true; state.tween = null;
      scrubWasPlaying = state.playing; setPlaying(false);
      scrubAt(e);
    });
    chart.addEventListener('pointermove', (e) => { if (state.scrubbing) scrubAt(e); });
    const endScrub = () => { if (!state.scrubbing) return; state.scrubbing = false; if (scrubWasPlaying) setPlaying(true); };
    chart.addEventListener('pointerup', endScrub);
    chart.addEventListener('pointercancel', endScrub);
  }

  /* ---------------- x-y loop plot (P-V and friends) ---------------- */
  const PL = mech.plot;
  let plotMax = PL?.yMin ?? 1;
  function drawPlot() {
    if (!pctx || !PL) return;
    const ctx = pctx, W = plot.width, H = plot.height;
    ctx.clearRect(0, 0, W, H);
    const padL = 58, padB = 44, padT = 14, padR = 14;
    let peak = 0;
    for (let phi = 0; phi < CYCLE; phi += CYCLE / 180) peak = Math.max(peak, PL.y(phi, state));
    plotMax += (Math.max(PL.yMin ?? 1, peak * 1.15) - plotMax) * 0.08;
    const X = (v) => padL + (W - padL - padR) * clamp01(v);
    const Y = (p) => H - padB - (H - padB - padT) * (p / plotMax);
    ctx.strokeStyle = 'rgba(22,27,38,.14)'; ctx.lineWidth = 1;
    for (let k = 0; k <= 4; k++) { const y = padT + (H - padB - padT) * k / 4; ctx.beginPath(); ctx.moveTo(padL, y); ctx.lineTo(W - padR, y); ctx.stroke(); }
    ctx.strokeStyle = 'rgba(22,27,38,.6)';
    ctx.beginPath(); ctx.moveTo(padL, padT); ctx.lineTo(padL, H - padB); ctx.lineTo(W - padR, H - padB); ctx.stroke();
    ctx.fillStyle = 'rgba(22,27,38,.55)';
    ctx.font = '500 19px Geist Mono';
    ctx.textAlign = 'right';
    ctx.fillText(plotMax >= 10 ? `${Math.round(plotMax)}` : plotMax.toFixed(1), padL - 8, padT + 6);
    ctx.fillText('0', padL - 8, H - padB + 2);
    ctx.save(); ctx.translate(18, (H - padB + padT) / 2); ctx.rotate(-Math.PI / 2); ctx.textAlign = 'center'; ctx.fillText(PL.yUnit, 0, 0); ctx.restore();
    const [xl, xm, xr] = PL.xTicks;
    ctx.textAlign = 'left'; ctx.fillText(xl, padL + 4, H - 14);
    ctx.textAlign = 'right'; ctx.fillText(xr, W - padR, H - 14);
    ctx.textAlign = 'center'; ctx.fillText(xm, (padL + W) / 2, H - 14);
    ctx.lineWidth = 3.2; ctx.lineJoin = 'round';
    const b = bounds();
    for (let s = 0; s < P.length; s++) {
      const a = b[s], len = mod((b[(s + 1) % b.length] ?? CYCLE) - a, CYCLE) || CYCLE;
      ctx.strokeStyle = P[s].color;
      ctx.beginPath();
      const n = Math.max(4, Math.ceil(len / (CYCLE / 360)));
      for (let k = 0; k <= n; k++) {
        let phi = a + len * k / n;
        if (phi > CYCLE) phi -= CYCLE;   // keep the end of the last phase at CYCLE, not 0
        const x = X(PL.x(phi, state)), y = Y(PL.y(phi, state));
        k === 0 ? ctx.moveTo(x, y) : ctx.lineTo(x, y);
      }
      ctx.stroke();
    }
    const phi = state.phi[state.focus];
    const x = X(PL.x(phi, state)), y = Y(PL.y(phi, state));
    ctx.fillStyle = PAPER_HEX; ctx.strokeStyle = INK_HEX; ctx.lineWidth = 3;
    ctx.beginPath(); ctx.arc(x, y, 8, 0, Math.PI * 2); ctx.fill(); ctx.stroke();
  }

  /* ---------------- callouts ---------------- */
  // Drafting balloons in two columns either side of the model, elbow leaders,
  // de-overlapped every frame so orbiting never piles them up.
  const CALLOUTS = model.callouts || [];
  const calloutLayer = $('callouts');
  const leaderSvg = $('leaders');
  const SVGNS = 'http://www.w3.org/2000/svg';
  CALLOUTS.forEach((c) => {
    c.el = h(`<div class="callout"><span class="bn">${c.n}</span><span class="nm">${esc(c.name)}</span></div>`);
    calloutLayer.appendChild(c.el);
    c.line = document.createElementNS(SVGNS, 'polyline');
    c.line.setAttribute('fill', 'none');
    c.line.setAttribute('stroke', 'rgba(22,27,38,.62)');
    c.line.setAttribute('stroke-width', '1');
    leaderSvg.appendChild(c.line);
    c.dot = document.createElementNS(SVGNS, 'circle');
    c.dot.setAttribute('r', '2.4');
    c.dot.setAttribute('fill', INK_HEX);
    leaderSvg.appendChild(c.dot);
  });
  const cv3 = new THREE.Vector3();
  const BOX = [];
  const [bmin, bmax] = V.box;
  for (const x of [bmin[0], bmax[0]]) for (const y of [bmin[1], bmax[1]]) for (const z of [bmin[2], bmax[2]]) BOX.push(new THREE.Vector3(x, y, z));
  const toScreen = (v, W, H) => [(v.x * 0.5 + 0.5) * W, (-v.y * 0.5 + 0.5) * H];
  function footprint(W, H) {
    let minX = Infinity, maxX = -Infinity, minY = Infinity, maxY = -Infinity;
    BOX.forEach((p) => { cv3.copy(p).project(camera); const [x, y] = toScreen(cv3, W, H); minX = Math.min(minX, x); maxX = Math.max(maxX, x); minY = Math.min(minY, y); maxY = Math.max(maxY, y); });
    return { minX, maxX, minY, maxY };
  }
  function placeCallouts(W, H) {
    if (!layers.callouts) return;
    const { minX, maxX, minY, maxY } = footprint(W, H);
    const compact = W < 700;
    const items = CALLOUTS.filter((c) => !compact || !mech.compactCallouts || mech.compactCallouts.includes(c.n));
    CALLOUTS.forEach((c) => { c.el.style.opacity = 0; c.line.style.opacity = 0; c.dot.style.opacity = 0; });
    const shown = [];
    items.forEach((c) => {
      c.at(cv3, state); cv3.project(camera);
      if (cv3.z >= 1) return;
      [c.ax, c.ay] = toScreen(cv3, W, H);
      shown.push(c);
    });
    shown.sort((a, b) => a.ax - b.ax);
    const half = Math.ceil(shown.length / 2);
    const sides = { L: shown.slice(0, half), R: shown.slice(half) };
    const gap = compact ? 22 : 27;
    const wL = Math.max(0, ...sides.L.map((c) => c.el.offsetWidth));
    const wR = Math.max(0, ...sides.R.map((c) => c.el.offsetWidth));
    const fL = compact ? 4 : free.x, fR = compact ? W - 4 : free.x + free.w;
    const reach = figure ? 70 : 36;
    const colL = Math.max(fL + wL + 4, minX - (compact ? 4 : reach));
    const colR = Math.min(fR - wR - 4, maxX + (compact ? 4 : reach));
    const yTop = free.y + 8, yBot = free.y + free.h - 8;
    for (const [key, list] of Object.entries(sides)) {
      list.sort((a, b) => a.ay - b.ay);
      let y = -Infinity;
      list.forEach((c) => { c.ly = Math.max(c.ay, y + gap, yTop); y = c.ly; });
      const over = y - Math.min(yBot, Math.max(maxY, minY + list.length * gap) + 10);
      if (over > 0) list.forEach((c) => { c.ly -= over; });
      for (let k = list.length - 2; k >= 0; k--) list[k].ly = Math.min(list[k].ly, list[k + 1].ly - gap);
      list.forEach((c) => {
        const left = key === 'L';
        const colX = left ? colL : colR;
        c.el.classList.toggle('left', left);
        const ex = left ? colX - c.el.offsetWidth : colX;
        c.el.style.transform = `translate(${ex.toFixed(1)}px, ${(c.ly - 10).toFixed(1)}px)`;
        const elbow = left ? colX + 8 : colX - 8;
        c.line.setAttribute('points', `${c.ax.toFixed(1)},${c.ay.toFixed(1)} ${elbow.toFixed(1)},${c.ly.toFixed(1)} ${colX.toFixed(1)},${c.ly.toFixed(1)}`);
        c.dot.setAttribute('cx', c.ax.toFixed(1)); c.dot.setAttribute('cy', c.ay.toFixed(1));
        c.el.style.opacity = 1; c.line.style.opacity = 1; c.dot.style.opacity = 1;
      });
    }
  }

  /* ---------------- instance tags ---------------- */
  // sheet: numbered balloons under the model. figure: "Cyl 1" header tags above it with a dashed leader.
  const tags = [];
  const tagLines = [];
  if (N > 1 && model.tagAnchor) {
    for (let i = 0; i < N; i++) {
      const el = figure
        ? h(`<button class="itag" type="button">${esc(mech.instances.short)} ${i + 1}</button>`)
        : h(`<div class="callout cyltag"><span class="bn">${i + 1}</span></div>`);
      el.addEventListener('click', () => setFocus(i));
      stageEl.appendChild(el);
      tags.push(el);
      if (figure) {
        const ln = document.createElementNS(SVGNS, 'line');
        ln.setAttribute('stroke', 'rgba(22,27,38,.55)'); ln.setAttribute('stroke-width', '1'); ln.setAttribute('stroke-dasharray', '3 3');
        leaderSvg.appendChild(ln);
        tagLines.push(ln);
      }
    }
  }
  const tv = new THREE.Vector3();
  function placeTags(W, H) {
    tags.forEach((el, i) => {
      const s = phaseOf(state.phi[i]);
      if (el.dataset.s !== String(s)) {
        el.dataset.s = s;
        el.style.setProperty('--tagc', P[s].color);
        el.title = `${mech.instances.label} ${i + 1}: ${P[s].name}`;
      }
      el.classList.toggle('focus', i === state.focus);
      if (figure) {
        model.tagAnchor(i, cv3, 'above'); cv3.project(camera);
        const [x, y] = toScreen(cv3, W, H);
        model.tagAnchor(i, tv, 'point'); tv.project(camera);
        const [px, py] = toScreen(tv, W, H);
        const w = el.offsetWidth, hh = el.offsetHeight;
        el.style.transform = `translate(${(x - w / 2).toFixed(1)}px, ${(y - hh).toFixed(1)}px)`;
        const ln = tagLines[i];
        ln.setAttribute('x1', x.toFixed(1)); ln.setAttribute('y1', y.toFixed(1));
        ln.setAttribute('x2', px.toFixed(1)); ln.setAttribute('y2', py.toFixed(1));
      } else {
        model.tagAnchor(i, cv3, 'below'); cv3.project(camera);
        const [x, y] = toScreen(cv3, W, H);
        const bn = el.firstChild;
        bn.style.borderColor = bn.style.color = P[s].color;
        el.style.transform = `translate(${(x - 9).toFixed(1)}px, ${(y - 9).toFixed(1)}px)`;
      }
    });
  }

  /* ---------------- layout: centre the model in the free region ---------------- */
  let vw = 0, vh = 0, fitDist = 15;
  const free = { x: 0, y: 0, w: 0, h: 0 };
  function layout() {
    const r = stageEl.getBoundingClientRect();
    vw = r.width; vh = r.height;
    renderer.setSize(vw, vh, false);
    camera.aspect = vw / vh;
    let fx = 0, fy = 0, fw = vw, fh = vh;
    const rect = (sel) => document.querySelector(sel)?.getBoundingClientRect();
    if (figure) {
      const card = rect('.card'), head = rect('.fig-head'), foot = rect('.fig-foot');
      fx = card.left - r.left + 12; fw = card.width - 24;
      fy = (head ? head.bottom : card.top) - r.top + 8;
      fh = (foot ? foot.top : card.bottom) - r.top - 8 - fy;
    } else if (innerWidth > 960) {
      const left = rect('.phase-panel'), right = rect('.instr-panel'), head = rect('.topbar'), foot = rect('.chart-panel');
      fx = left.right + 10; fw = right.left - 10 - fx;
      fy = head.bottom + 4; fh = foot.top - 8 - fy;
    }
    Object.assign(free, { x: fx, y: fy, w: fw, h: fh });
    const offX = (fx + fw / 2) - vw / 2, offY = (fy + fh / 2) - vh / 2;
    camera.setViewOffset(vw, vh, -offX, -offY, vw, vh);
    camera.updateProjectionMatrix();
    const vFov = camera.fov * D2R;
    const tanV = Math.tan(vFov / 2) * (fh / vh);
    const tanH = Math.tan(vFov / 2) * camera.aspect * (fw / vw);
    const radius = innerWidth < 700 ? (V.radiusCompact ?? V.radius * 1.2) : figure ? (V.radiusFigure ?? V.radius * 1.15) : V.radius;
    fitDist = radius / Math.min(tanV, tanH);
    fitDist = Math.min(Math.max(fitDist, controls.minDistance + 0.5), controls.maxDistance);
    kit.outlineMat.uniforms.uPx.value = (2 * Math.tan(vFov / 2) / vh) * 1.4;
    sizeCharts();
  }
  addEventListener('resize', layout);
  if (document.fonts) document.fonts.ready.then(layout);

  /* ---------------- loop ---------------- */
  const clock = new THREE.Clock();
  let intro = 0;
  layout();
  camera.position.copy(TARGET).addScaledVector(VIEW_DIR, fitDist * 1.6);
  let lastFit = fitDist;
  const tmpV = new THREE.Vector3();

  function frame() {
    const dt = Math.min(clock.getDelta(), 0.05);
    // the rate follows the input with some inertia
    state.rate += (D.target(state.input) - state.rate) * (1 - Math.exp(-dt * (D.inertia ?? 1.4)));
    if (state.tween) {
      const tw = state.tween;
      tw.t += dt / tw.dur;
      const k = tw.t >= 1 ? 1 : 0.5 - 0.5 * Math.cos(Math.PI * tw.t);
      state.theta = tw.from + (tw.to - tw.from) * k;
      if (tw.t >= 1) state.tween = null;
    } else if (state.playing) {
      state.theta += D.degPerSec(state.rate) / state.slow * dt;
    }
    for (let i = 0; i < N; i++) state.phi[i] = phiOf(i);
    model.pose(state.theta, dt, state);

    if (intro < 1) {
      intro = Math.min(1, intro + dt / 1.8);
      const e = 1 - Math.pow(1 - intro, 3);
      tmpV.copy(camera.position).sub(controls.target).normalize();
      camera.position.copy(controls.target).addScaledVector(tmpV, fitDist * (1.6 - 0.6 * e));
    } else if (Math.abs(fitDist - lastFit) > 0.01) {
      tmpV.copy(camera.position).sub(controls.target).multiplyScalar(fitDist / lastFit);
      camera.position.copy(controls.target).add(tmpV);
    }
    lastFit = fitDist;
    controls.update();
    renderer.render(scene, camera);

    placeCallouts(vw, vh);
    placeTags(vw, vh);
    updatePanel();
    if (chart) drawChart();
    drawPlot();
    updateGauge();
    requestAnimationFrame(frame);
  }
  requestAnimationFrame(frame);

  // for scripted shots, the clip recorder and the console
  window.__sheet = { state, model, mech, kit, api, setFocus, jumpTo, setPlaying, layout };
  return window.__sheet;
}

/* =========================================================================
   DOM, generated from the mechanism so index.html stays generic
   ========================================================================= */
function buildDom(mech, figure) {
  const m = mech.meta, P = mech.phases, N = mech.instances.count;
  const layerBtns = [...(mech.layers || []), { key: 'callouts', label: 'Labels', on: true }, { key: 'orbit', label: 'Orbit', on: false }]
    .map((l) => `<button class="tog${l.on !== false ? ' on' : ''}" data-layer="${l.key}" aria-pressed="${l.on !== false}">${esc(l.label)}</button>`).join('');
  const speeds = mech.speeds.map((s) => `<button data-s="${s}"${s === (mech.speed ?? mech.speeds[1] ?? mech.speeds[0]) ? ' class="on"' : ''}>${speedLabel(s)}</button>`).join('');
  const focusSeg = N > 1
    ? `<div class="seg seg-mini" id="focusSeg" role="group" aria-label="Follow ${esc(mech.instances.label.toLowerCase())}">${Array.from({ length: N }, (_, i) => `<button data-c="${i}"${i ? '' : ' class="on"'}>${i + 1}</button>`).join('')}</div>`
    : '';
  const transport = `<div class="transport">
      <button class="tbtn" id="prevBtn" title="Back one phase" aria-label="Back one phase">${ICON.prev}</button>
      <button class="tbtn play" id="playBtn" aria-label="Pause">${ICON.pause}${ICON.play}</button>
      <button class="tbtn" id="nextBtn" title="Forward one phase" aria-label="Forward one phase">${ICON.next}</button>
    </div>`;
  const D = mech.driver;
  const actions = (mech.actions || []).map((a, k) => `<button class="act" id="act${k}" type="button">${esc(a.label)}</button>`).join('');
  const stage = `<div class="stage" id="stage"><canvas id="gl" aria-label="${esc(m.alt || 'Interactive 3D model')}"></canvas><svg class="leaders" id="leaders"></svg><div class="callouts" id="callouts"></div></div>`;

  if (figure) {
    document.body.insertAdjacentHTML('afterbegin', `
      <div class="card" aria-hidden="true"></div>
      ${stage}
      <main class="fig">
        <header class="fig-head">
          <div class="status">
            <div><b id="statusSpeed">Shown at ${speedLabel(mech.speed ?? mech.speeds[0])} speed</b> &middot; <span id="statusPlay">running</span></div>
            <div class="chip"><span>${esc(N > 1 ? `${mech.instances.short} ` : '')}</span>${N > 1 ? '<span id="chipInst">1</span> &middot; ' : ''}<b id="chipPhase">${esc(P[0].name)}</b></div>
          </div>
          <div class="fig-title"><h1>${m.title}</h1><div class="toggles" role="group" aria-label="Layers">${layerBtns}</div></div>
        </header>
        <footer class="fig-foot">
          ${transport}
          <div class="seg" id="slowSeg" role="group" aria-label="Speed">${speeds}</div>
          <div class="ctrl ctrl-inline"><label for="drive">${esc(D.inputLabel)}</label><input type="range" id="drive" min="0" max="100"><span id="driveVal"></span></div>
          ${actions ? `<div class="acts">${actions}</div>` : ''}
          ${focusSeg}
          <span class="orbit-hint">Drag to orbit</span>
        </footer>
      </main>`);
    return;
  }

  const zones = (n, l) => Array.from({ length: n }, (_, i) => `<span>${l ? String.fromCharCode(65 + i) : i + 1}</span>`).join('');
  document.body.insertAdjacentHTML('afterbegin', `
    <div class="sheet" aria-hidden="true">
      <div class="zones zones-top">${zones(8)}</div><div class="zones zones-bottom">${zones(8)}</div>
      <div class="zones zones-left">${zones(5, 1)}</div><div class="zones zones-right">${zones(5, 1)}</div>
    </div>
    ${stage}
    <main class="layout">
      <header class="topbar">
        <div class="fig-tag"><b>${esc(m.fig)}</b><span>${esc(m.caption)}</span></div>
        <div class="toggles" role="group" aria-label="Layers"><span class="lbl">Show</span>${layerBtns}</div>
      </header>
      <section class="masthead"><h1>${m.title}</h1><p class="lede">${esc(m.lede)}</p></section>
      <section class="block phase-panel" aria-live="polite">
        <div class="block-head"><span class="ph-n">A</span><span>${esc(mech.instances.label)}</span>${focusSeg}</div>
        <div class="phase-now">
          <div class="phase-num" id="phaseNum">01</div>
          <div><div class="phase-name" id="phaseName">${esc(P[0].name)}</div><div class="phase-nick" id="phaseNick"></div></div>
        </div>
        <p class="phase-text" id="phaseText"></p>
        <ol class="phase-list" id="phaseList" style="grid-template-columns: repeat(${P.length}, 1fr)">
          ${P.map((p, k) => `<li data-s="${k}" title="${esc(p.name)}"><i style="background:${p.color}"></i>${esc(p.list || p.nick)}</li>`).join('')}
        </ol>
        <dl class="readout" id="readout"></dl>
      </section>
      <section class="block instr-panel">
        <div class="block-head"><span class="ph-n">B</span><span>Instruments</span></div>
        ${mech.gauge ? `<div class="gauge-wrap"><svg class="gauge" id="gauge" viewBox="0 0 200 150"></svg><div class="gauge-read"><b id="gaugeVal"></b><span>${esc(mech.gauge.unit)}</span></div></div>` : ''}
        <div class="ctrl">
          <div class="ctrl-row"><label for="drive">${esc(D.inputLabel)}</label><span id="driveVal"></span></div>
          <input type="range" id="drive" min="0" max="100">
          ${D.inputHint ? `<p class="hint">${esc(D.inputHint)}</p>` : ''}
        </div>
        <div class="ctrl">
          <div class="ctrl-row"><label>Slow motion</label><span id="slowVal">${speedLabel(mech.speed ?? mech.speeds[0])} speed</span></div>
          <div class="seg seg-wide" id="slowSeg">${speeds}</div>
        </div>
        ${mech.plot ? `<div class="plot-box"><div class="plot-head"><span>${esc(mech.plot.label)}</span>${N > 1 ? `<span class="plot-sub">${esc(mech.instances.short.toLowerCase())} <b id="plotInst">1</b></span>` : ''}</div><canvas id="plot" width="560" height="300"></canvas></div>` : ''}
        ${actions ? transport.replace('</div>', `<span class="acts">${actions}</span></div>`) : transport}
        <div class="title-block" aria-label="Drawing information">
          <div class="tb-main"><span>Title</span><b>${esc(m.titleBlock.title)}</b></div>
          <div class="tb-grid">
            <div><span>Dwg no.</span><b>${esc(m.titleBlock.dwg)}</b></div>
            <div><span>Scale</span><b>${esc(m.titleBlock.scale || 'NTS')}</b></div>
            <div><span>Sheet</span><b>1 / 1</b></div>
          </div>
        </div>
      </section>
      <section class="block chart-panel" style="--rows:${N}">
        <div class="block-head"><span class="ph-n">C</span><span>${esc(mech.chart?.label || 'Cycle chart')}</span>
          <ul class="key" aria-label="Key">${P.map((p) => `<li><i style="background:${p.color}"></i>${esc(p.key || p.name)}</li>`).join('')}</ul>
        </div>
        <canvas id="chart"></canvas>
        ${mech.chart?.note ? `<p class="chart-note">${esc(mech.chart.note)}</p>` : ''}
      </section>
    </main>`);
}
