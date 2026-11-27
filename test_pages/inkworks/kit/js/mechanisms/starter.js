/* =========================================================================
   STARTER mechanism: the smallest complete Inkworks machine.
   A crank wheel drives a slider through a connecting rod (slider-crank).
   Copy this file, rename it, and replace geometry + kinematics + words.
   Every field the page uses is here, with a comment saying what it does.
   ========================================================================= */
import { HUES, D2R, mod } from '../kit.js';

// ---------- 1. constants + closed-form kinematics: everything from ONE angle ----------
const R = 0.8;              // crank radius
const L = 2.4;              // rod length
const slideX = (a) => R * Math.cos(a * D2R) + Math.sqrt(L * L - (R * Math.sin(a * D2R)) ** 2);   // slider position

export default {
  id: 'starter',
  // ---------- 2. words: title, sheet caption, title block ----------
  meta: {
    pageTitle: 'How a Slider-Crank Works',
    fig: 'Fig. 00',
    caption: 'Slider-crank · the starter mechanism',
    title: 'How a <em>crank</em> turns spin into push',     // one <em> phrase goes red italic
    lede: 'A wheel goes round, a block goes back and forth. The rod in between does the translating.',
    titleBlock: { title: 'Slider-crank', dwg: 'STR-00-000' },
    alt: 'Interactive 3D slider-crank',
    layout: 'sheet',                                         // default layout: 'sheet' or 'figure'
  },
  // ---------- 3. the cycle and its phases ----------
  cycle: 360,               // driver degrees per full cycle
  start: 20,                // where theta starts
  phases: [                 // equal slices of the cycle unless you add bounds(state)
    { name: 'Pull back', nick: 'in', list: 'In', short: 'IN', key: 'Moving in', color: HUES.blue,
      text: 'From the far end the crank pin swings up and over, and the rod drags the block back towards the wheel.' },
    { name: 'Push out', nick: 'out', list: 'Out', short: 'OUT', key: 'Moving out', color: HUES.red,
      text: 'Past the near end the pin comes round underneath and the rod shoves the block away again.' },
  ],
  // bounds: (s) => [0, 180],  // optional: phase start angles computed from state (see pump.js)
  instances: { count: 1, label: 'Crank', short: 'Crank', offset: [0] },   // >1 = cylinders, pistons... with phase offsets
  // ---------- 4. what the slider drives and how fast theta moves ----------
  driver: {
    inputLabel: 'Motor speed',
    inputHint: 'How fast the wheel turns.',
    input: 0.3,
    target: (x) => 10 + 110 * x,              // the "rate" (here rpm) the input asks for
    inputFormat: (x) => `${Math.round(10 + 110 * x)} rpm`,
    inertia: 2,                               // how quickly the rate follows the input
    degPerSec: (rpm) => (rpm / 60) * 360,     // rate -> driver degrees per second at 1x
  },
  speeds: [8, 4, 1],        // slow-motion divisors shown as buttons (1 = real time)
  speed: 4,
  // ---------- 5. instruments (sheet layout): a gauge and an x-y loop ----------
  gauge: { max: 120, red: 100, minor: 5, major: 20, label: 'RPM', unit: 'rpm', value: (s) => s.rate, readout: (v) => Math.round(v) },
  plot: { label: 'Slider position vs crank angle', x: (phi) => phi / 360, y: (phi) => slideX(phi) - (L - R), yUnit: 'pos', xTicks: ['0°', 'crank angle', '360°'], yMin: 1.8 },
  chart: { label: 'Cycle chart', note: 'Drag to scrub through one turn.', markers: [] },
  // ---------- 6. layers the toggles switch (Labels + Orbit are added for you) ----------
  layers: [{ key: 'casing', label: 'Guide', on: true }],
  // ---------- 7. camera: what to look at, from where, and the model's bounding box ----------
  view: { target: [1.45, 0, 0.2], dir: [1.2, 1.6, 5], radius: 2.75, minDist: 4, maxDist: 30, box: [[-1.2, -1.2, -0.6], [4.2, 1.2, 0.6]] },
  compactCallouts: [1, 2, 3],

  // ---------- 8. build the model once; return pose() + labels + readouts ----------
  build(kit, { state }) {
    const { THREE, part, ghost, M, xCyl, markLine, scene } = kit;
    const root = new THREE.Group();
    scene.add(root);
    const zCyl = (r, len, seg = 40) => new THREE.CylinderGeometry(r, r, len, seg).rotateX(Math.PI / 2);

    const wheel = new THREE.Group();
    root.add(wheel);
    wheel.add(part(zCyl(R + 0.18, 0.16), M.steel));
    const pin = part(zCyl(0.1, 0.5, 20), M.steel); pin.position.set(R, 0, 0.2); wheel.add(pin);
    const mark = markLine(0.3, 0.05); mark.rotation.z = -Math.PI / 2; mark.position.z = 0.11; wheel.add(mark);

    const rod = new THREE.Group();
    root.add(rod);
    const beam = part(new THREE.BoxGeometry(L, 0.14, 0.1).translate(L / 2, 0, 0), M.steel);
    rod.add(beam);
    rod.position.z = 0.4;

    const block = part(new THREE.BoxGeometry(0.7, 0.5, 0.6), M.alloy);
    root.add(block);
    const guide = ghost(new THREE.BoxGeometry(2.7, 0.7, 0.8));   // hidden-line housing
    guide.position.set(2.4, 0, 0.4);
    root.add(guide);

    // pose(theta, dt, state): place every part from the driver angle. No wall-clock time in here.
    function pose(theta) {
      const a = theta * D2R;
      wheel.rotation.z = a;
      const px = R * Math.cos(a), py = R * Math.sin(a);
      const sx = slideX(theta);
      rod.position.x = px; rod.position.y = py;
      rod.rotation.z = Math.atan2(-py, sx - px);
      block.position.set(sx, 0, 0.4);
    }
    return {
      root,
      pose,
      setLayer(key, on) { if (key === 'casing') guide.visible = on; },
      // tagAnchor(i, v, where): only needed when instances.count > 1
      callouts: [   // n = balloon number; at(v) writes the world point the leader touches
        { n: 1, name: 'Crank wheel', at: (v) => v.set(-0.6, -0.7, 0.1) },
        { n: 2, name: 'Connecting rod', at: (v) => rod.localToWorld(v.set(L * 0.5, 0, 0)) },
        { n: 3, name: 'Slider', at: (v) => block.localToWorld(v.set(0, 0.25, 0)) },
        { n: 4, name: 'Guide', at: (v) => v.set(3.6, 0.35, 0.8) },
      ],
      readouts: [   // value(ctx) returns text, or { text, cls: 'on' | 'hot' } for colour
        { label: 'Crank angle', value: ({ phi }) => `${Math.round(phi)}°` },
        { label: 'Slider', value: ({ phi }) => `${(slideX(phi) - (L - R)).toFixed(2)} from home` },
        { label: 'Direction', value: ({ phi }) => (mod(phi, 360) < 180 ? 'returning' : { text: 'outward', cls: 'on' }) },
      ],
    };
  },
};
