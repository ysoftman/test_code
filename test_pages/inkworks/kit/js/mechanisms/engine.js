/* =========================================================================
   Mechanism: inline-4, four-stroke petrol engine.
   Driver variable theta = crank degrees. One cycle = 720 (two crank turns).
   Everything below is closed-form from theta: crank, rods, pistons, cams,
   valves, belt, gas colour, spark, particles, heat.
   ========================================================================= */
import { HUES, mod, clamp01, smooth, D2R } from '../kit.js';

// ---------- geometry (scene units) ----------
const R = 0.45;                 // crank throw (half the stroke)
const L = 1.4;                  // con-rod centre to centre
const PIN_TO_CROWN = 0.3;
const CROWN_TDC = R + L + PIN_TO_CROWN;
const HEAD_Y = CROWN_TDC + 0.1; // -> compression ratio 10:1
const BORE = 0.42;
const CYL_X = [-1.725, -0.575, 0.575, 1.725];
const THROW = [0, 180, 180, 0];         // crank-pin angle per cylinder
const OFFSET = [0, 540, 180, 360];      // place in the 720 cycle -> fires 1-3-4-2
const VALVE_TILT = 18 * D2R;
const VALVE_Z = 0.2;
const CAM_DIST = 1.0;
const CAM_RB = 0.15;
const LIFT = 0.1;
const IN_MID = 105, EX_MID = 615, VALVE_DUR = 234;
const SPARK_AT = 345;           // 15 deg before top dead centre
const BELT_X = 2.66;
const CRANK_PULLEY = 0.22, CAM_PULLEY = 0.44;   // 2:1, cams turn at half speed
const PLENUM = { y: 2.78, z: -2.05 };

const camYZ = (side) => [HEAD_Y + CAM_DIST * Math.cos(VALVE_TILT), side * (VALVE_Z + CAM_DIST * Math.sin(VALVE_TILT))];

// ---------- kinematics ----------
const pinHeight = (aDeg) => { const a = aDeg * D2R; return R * Math.cos(a) + Math.sqrt(L * L - R * R * Math.sin(a) ** 2); };
const chamber = (phi) => HEAD_Y - (pinHeight(phi) + PIN_TO_CROWN);
const V_MAX = chamber(180);
function valveLift(phi, mid) {
  const d = mod(phi - mid + 360, 720) - 360, half = VALVE_DUR / 2;
  if (Math.abs(d) >= half) return 0;
  const c = Math.cos((Math.PI / 2) * d / half);
  return LIFT * c * c;
}
function pressure(phi, thr) {
  const pin = 0.35 + 0.65 * thr;           // manifold pressure: the throttle decides
  const n = 1.3, rise = 1.2 + 1.1 * thr;
  if (phi < 180) return 1.05 + (pin - 1.05) * smooth(0, 30, phi);
  if (phi < 540) return pin * Math.pow(V_MAX / chamber(phi), n) * (1 + rise * smooth(350, 392, phi));
  return 1.05 + (pin * (1 + rise) - 1.05) * Math.exp(-(phi - 540) / 14);
}

const C = { in: HUES.blue, co: HUES.ochre, pw: HUES.red, ex: HUES.grey };

export default {
  id: 'engine',
  meta: {
    pageTitle: 'How a Car Engine Works',
    fig: 'Fig. 01',
    caption: 'Inline-4 · four-stroke petrol · cutaway',
    title: 'How a <em>car engine</em> turns fuel into motion',
    lede: 'Four pistons, four jobs, thousands of times a minute. Slow it right down and watch.',
    titleBlock: { title: 'Four-stroke engine', dwg: 'ENG-4S-001' },
    alt: 'Interactive 3D cutaway of a four-cylinder engine',
    layout: 'sheet',
  },
  cycle: 720,
  start: 30,
  phases: [
    { name: 'Intake', nick: 'suck', list: 'Suck', short: 'INTAKE', key: 'Air + fuel', color: C.in,
      text: 'The piston slides down with the intake valve open. That drop in pressure pulls a mist of air and petrol in from the manifold. The accelerator only decides how much air gets past the throttle plate.' },
    { name: 'Compression', nick: 'squeeze', list: 'Squeeze', short: 'COMPRESS', key: 'Squeezed', color: C.co,
      text: 'Both valves snap shut and the piston comes back up, crushing the charge to a tenth of its volume. Squeezed gas heats up, so it will burn fast and hard when the spark comes.' },
    { name: 'Power', nick: 'bang', list: 'Bang', short: 'POWER', key: 'Burning', color: C.pw,
      text: 'Just before the top, the spark plug fires. The mix burns in a few thousandths of a second and the pressure spike slams the piston down. The rod turns that push into crankshaft rotation. This is the only stroke that makes work.' },
    { name: 'Exhaust', nick: 'blow', list: 'Blow', short: 'EXHAUST', key: 'Exhaust', color: C.ex,
      text: 'The exhaust valve opens and the rising piston sweeps the spent gas out into the manifold, which heats up as it passes. Then the intake valve opens and it all starts again.' },
  ],
  instances: { count: 4, label: 'Cylinder', short: 'Cyl', offset: OFFSET },
  driver: {
    inputLabel: 'Accelerator',
    inputHint: 'Opens the throttle plate: more air in, bigger bang, higher rpm.',
    input: 0.15,
    start: 850,
    target: (x) => 800 + 5600 * Math.pow(x, 1.15),     // rpm
    inertia: 1.4,
    degPerSec: (rpm) => (rpm / 60) * 360,
  },
  speeds: [200, 60, 12],
  speed: 60,
  gauge: { max: 8000, red: 6500, minor: 250, major: 1000, tick: (v) => v / 1000, label: 'x1000 RPM', unit: 'rpm',
    value: (s) => s.rate, readout: (v) => Math.round(v / 10) * 10 },
  plot: { label: 'Pressure vs volume', x: (phi) => chamber(phi) / V_MAX, y: (phi, s) => pressure(phi, s.input), yUnit: 'bar', xTicks: ['TDC', 'volume', 'BDC'], yMin: 20 },
  chart: {
    label: 'Firing chart',
    note: 'Firing order 1-3-4-2: one cylinder is always on its power stroke. Drag to scrub, click a row to follow it.',
    markers: [{ at: SPARK_AT, kind: 'spark' }],
  },
  layers: [{ key: 'casing', label: 'Casing', on: true }, { key: 'flow', label: 'Gas flow', on: true }],
  view: { target: [0, 1.15, 0], dir: [6.4, 4.0, -9.0], radius: 3.9, radiusCompact: 4.7, radiusFigure: 3.75, minDist: 7, maxDist: 30,
    box: [[-3.0, -1.2, -2.1], [3.1, 3.5, 1.9]] },
  compactCallouts: [1, 3, 5, 6, 7],

  build(kit, { state }) {
    const { THREE, part, ghost, ghostRings, toon, M, lineMat, xCyl, aimX, markLine, inkRing, gearGeometry, springGeometry, hull, flash, stream, scene, INK } = kit;
    const engine = new THREE.Group();
    scene.add(engine);
    const tmpV = new THREE.Vector3();
    const tmpColor = new THREE.Color();
    const C_IN = new THREE.Color(C.in), C_CO = new THREE.Color(C.co), C_PW = new THREE.Color(C.pw), C_EX = new THREE.Color(C.ex);
    const C_HOT = new THREE.Color('#ffc93a'), C_EMBER = new THREE.Color('#a3341f'), EX_BASE = new THREE.Color('#aab4c2');

    /* ---------- crankshaft ---------- */
    const crank = new THREE.Group();
    engine.add(crank);
    const WEB = (() => {
      const s = new THREE.Shape();
      s.absarc(0, 0, 0.6, Math.PI * 0.6, Math.PI * 1.4, false);
      s.lineTo(R, -0.21);
      s.absarc(R, 0, 0.21, -Math.PI / 2, Math.PI / 2, false);
      s.closePath();
      const g = new THREE.ExtrudeGeometry(s, { depth: 0.12, bevelEnabled: false, curveSegments: 20 });
      g.rotateY(Math.PI / 2);
      g.translate(-0.06, 0, 0);
      return g;
    })();
    [-2.3, -1.15, 0, 1.15, 2.3].forEach((x) => { const j = part(xCyl(0.16, 0.26), M.steel); j.position.x = x; crank.add(j); });
    CYL_X.forEach((cx, i) => {
      const t = THROW[i] * D2R;
      const pin = part(xCyl(0.15, 0.3), M.steel);
      pin.position.set(cx, R * Math.cos(t), R * Math.sin(t));
      crank.add(pin);
      [-0.21, 0.21].forEach((dx) => {
        const w = part(WEB, M.steel);
        w.position.x = cx + dx;
        w.rotation.x = aimX(Math.cos(t), Math.sin(t));
        crank.add(w);
      });
    });
    const nose = part(xCyl(0.12, 0.36), M.steel); nose.position.x = 2.5; crank.add(nose);
    const crankPulley = part(xCyl(CRANK_PULLEY, 0.14, 40), M.dark); crankPulley.position.x = BELT_X; crank.add(crankPulley);
    const flywheel = part(gearGeometry(1.05, 48, 0.14), M.dark, { edges: 40 }); flywheel.position.x = -2.62; crank.add(flywheel);
    const flyHub = part(xCyl(0.3, 0.2), M.steel); flyHub.position.x = -2.5; crank.add(flyHub);
    const fwMark = markLine(0.55, 0.4); fwMark.position.x = -2.7; crank.add(fwMark);
    const cpMark = markLine(0.16, 0.04); cpMark.position.x = BELT_X + 0.08; crank.add(cpMark);

    /* ---------- rods + pistons + gas ---------- */
    const ROD_BEAM = new THREE.BoxGeometry(0.08, L - 0.3, 0.13).translate(0, L / 2, 0);
    const ROD_BIG = xCyl(0.2, 0.12, 28), ROD_SMALL = xCyl(0.1, 0.1, 20);
    const PISTON = new THREE.CylinderGeometry(BORE - 0.012, BORE - 0.012, 0.5, 40).translate(0, 0.05, 0);
    const WRIST = xCyl(0.06, 0.66, 12);
    const cyl = CYL_X.map((cx, i) => {
      const rod = new THREE.Group();
      rod.add(part(ROD_BEAM, M.steel), part(ROD_BIG, M.steel));
      const se = part(ROD_SMALL, M.steel); se.position.y = L; rod.add(se);
      rod.position.x = cx;
      engine.add(rod);
      const piston = new THREE.Group();
      piston.add(part(PISTON, M.alloy), part(WRIST, M.steel, { outline: false }));
      [0.24, 0.19, 0.13].forEach((y) => piston.add(inkRing(BORE - 0.009, y)));
      piston.position.x = cx;
      engine.add(piston);
      const gasMat = new THREE.MeshBasicMaterial({ color: C_IN, transparent: true, opacity: 0.3, depthWrite: false });
      const gas = new THREE.Mesh(new THREE.CylinderGeometry(BORE - 0.014, BORE - 0.014, 1, 40).translate(0, 0.5, 0), gasMat);
      gas.position.x = cx;
      gas.renderOrder = 2;
      engine.add(gas);
      return { cx, i, rod, piston, gas, gasMat, heat: 0, inFlow: 0, exFlow: 0, valves: {}, lift: { in: 0, ex: 0 } };
    });

    /* ---------- valvetrain ---------- */
    const LOBE = (() => {   // the lobe is extruded from the same lift profile the valves use
      const s = new THREE.Shape(), Nn = 96, half = VALVE_DUR / 2;
      for (let k = 0; k <= Nn; k++) {
        const psi = (k / Nn) * Math.PI * 2;
        const dCrank = mod(psi / D2R * 2 + 360, 720) - 360;
        let lift = 0;
        if (Math.abs(dCrank) < half) { const c = Math.cos((Math.PI / 2) * dCrank / half); lift = LIFT * c * c; }
        const r = CAM_RB + lift;
        k === 0 ? s.moveTo(r * Math.cos(psi), r * Math.sin(psi)) : s.lineTo(r * Math.cos(psi), r * Math.sin(psi));
      }
      const g = new THREE.ExtrudeGeometry(s, { depth: 0.16, bevelEnabled: false });
      g.rotateY(Math.PI / 2);
      g.translate(-0.08, 0, 0);
      return g;
    })();
    const camshafts = [-1, 1].map((side) => {
      const [y, z] = camYZ(side);
      const g = new THREE.Group();
      g.position.set(0, y, z);
      engine.add(g);
      const shaft = part(xCyl(0.07, 5.0, 16), M.steel); shaft.position.x = 0.1; g.add(shaft);
      const pulley = part(xCyl(CAM_PULLEY, 0.14, 48), M.dark); pulley.position.x = BELT_X; g.add(pulley);
      const mk = markLine(0.3, 0.08); mk.position.x = BELT_X + 0.08; g.add(mk);
      // each lobe's nose points down its valve exactly when that valve is fully open
      const aimAngle = aimX(-Math.cos(VALVE_TILT), -side * Math.sin(VALVE_TILT));
      const mid = side < 0 ? IN_MID : EX_MID;
      CYL_X.forEach((cx, i) => {
        const lobe = part(LOBE, M.steel);
        lobe.position.x = cx;
        lobe.rotation.x = aimAngle - ((OFFSET[i] + mid) * D2R) / 2;
        g.add(lobe);
      });
      return g;
    });
    const SPRING = springGeometry(0.07, 6, 0.009);
    const springMat = new THREE.MeshBasicMaterial({ color: INK });
    const STEM = new THREE.CylinderGeometry(0.025, 0.025, 0.8, 10).translate(0, 0.42, 0);
    const VHEAD = new THREE.CylinderGeometry(0.135, 0.06, 0.06, 28).translate(0, 0.02, 0);
    const BUCKET = new THREE.CylinderGeometry(0.09, 0.09, 0.1, 22).translate(0, 0.8, 0);
    cyl.forEach((c) => {
      [-1, 1].forEach((side) => {
        const fixed = new THREE.Group();
        fixed.position.set(c.cx, HEAD_Y, side * VALVE_Z);
        fixed.rotation.x = side * VALVE_TILT;
        engine.add(fixed);
        const moving = new THREE.Group();
        moving.add(part(STEM, M.valve, { outline: false }), part(VHEAD, M.valve), part(BUCKET, M.valve));
        fixed.add(moving);
        const spring = new THREE.Mesh(SPRING, springMat);
        spring.position.y = 0.38;
        fixed.add(spring);
        c.valves[side < 0 ? 'in' : 'ex'] = { fixed, moving, spring };
      });
      const plug = new THREE.Group();
      plug.position.set(c.cx, HEAD_Y, 0);
      plug.add(
        part(new THREE.CylinderGeometry(0.02, 0.02, 0.12, 8), M.copper, { outline: false }),
        part(new THREE.CylinderGeometry(0.06, 0.06, 0.3, 16).translate(0, 0.17, 0), M.steel),
        part(new THREE.CylinderGeometry(0.1, 0.1, 0.12, 6).translate(0, 0.38, 0), M.steel),
        part(new THREE.CylinderGeometry(0.045, 0.065, 0.55, 18).translate(0, 0.72, 0), M.ceramic),
        part(new THREE.CylinderGeometry(0.03, 0.03, 0.12, 10).translate(0, 1.05, 0), M.steel, { outline: false }));
      engine.add(plug);
      c.plug = plug;
      c.spark = flash();
      c.spark.position.set(c.cx, HEAD_Y - 0.06, 0);
      engine.add(c.spark);
    });

    /* ---------- timing belt ---------- */
    function beltLoop(extra) {
      const circles = [[0, 0, CRANK_PULLEY], [...camYZ(-1), CAM_PULLEY], [...camYZ(1), CAM_PULLEY]];
      const pts = [];
      circles.forEach(([y, z, r]) => { for (let k = 0; k < 90; k++) { const a = k / 90 * Math.PI * 2; pts.push([y + (r + extra) * Math.cos(a), z + (r + extra) * Math.sin(a)]); } });
      return hull(pts).map(([y, z]) => new THREE.Vector3(BELT_X, y, z));
    }
    const belt = new THREE.Group();
    engine.add(belt);
    [beltLoop(0.01), beltLoop(0.055)].forEach((loop) => belt.add(new THREE.LineLoop(new THREE.BufferGeometry().setFromPoints(loop), lineMat)));
    const beltCurve = new THREE.CatmullRomCurve3(beltLoop(0.032), true, 'catmullrom', 0);
    const beltLen = beltCurve.getLength();
    const BELT_TEETH = 70;
    const beltPts = new THREE.Points(new THREE.BufferGeometry().setAttribute('position', new THREE.Float32BufferAttribute(new Float32Array(BELT_TEETH * 3), 3)),
      new THREE.PointsMaterial({ color: 0x161b26, size: 3, sizeAttenuation: false }));
    belt.add(beltPts);

    /* ---------- manifolds ---------- */
    const plenum = part(xCyl(0.27, 4.8, 36), M.glass, { outline: false });
    plenum.position.set(0.2, PLENUM.y, PLENUM.z);
    engine.add(plenum);
    const tbody = part(xCyl(0.22, 0.5, 32, true), M.steel, { outline: false });
    tbody.position.set(2.85, PLENUM.y, PLENUM.z);
    engine.add(tbody);
    const plate = new THREE.Group();
    plate.position.set(2.88, PLENUM.y, PLENUM.z);
    plate.add(part(xCyl(0.2, 0.025, 28), M.valve, { outline: false }));
    plate.add(new THREE.Line(new THREE.BufferGeometry().setFromPoints([new THREE.Vector3(0, 0, -0.3), new THREE.Vector3(0, 0, 0.3)]), lineMat));
    engine.add(plate);
    engine.add(part(new THREE.TubeGeometry(new THREE.CatmullRomCurve3([
      new THREE.Vector3(3.08, PLENUM.y, PLENUM.z), new THREE.Vector3(3.45, PLENUM.y + 0.05, PLENUM.z), new THREE.Vector3(3.75, PLENUM.y + 0.35, PLENUM.z - 0.1)]), 20, 0.19, 24), M.glass, { edges: false, outline: false }));
    const exhaustMats = [];
    CYL_X.forEach((cx) => {
      const run = new THREE.CatmullRomCurve3([
        new THREE.Vector3(cx, 2.5, -0.32), new THREE.Vector3(cx, 2.62, -0.85), new THREE.Vector3(cx, 2.72, -1.4), new THREE.Vector3(cx, PLENUM.y, PLENUM.z + 0.08)]);
      engine.add(part(new THREE.TubeGeometry(run, 28, 0.12, 18), M.glass, { edges: false, outline: false }));
      engine.add(ghostRings(run, 0.12));
      const em = toon('#aab4c2');
      exhaustMats.push(em);
      const hdr = new THREE.CatmullRomCurve3([
        new THREE.Vector3(cx, 2.5, 0.32), new THREE.Vector3(cx, 2.6, 0.85), new THREE.Vector3(cx, 2.32, 1.35), new THREE.Vector3(cx * 0.55, 1.55, 1.66), new THREE.Vector3(cx * 0.12, 1.02, 1.76)]);
      engine.add(part(new THREE.TubeGeometry(hdr, 40, 0.1, 16), em, { edges: false }));
    });
    const pipeMat = toon('#aab4c2');
    engine.add(part(new THREE.TubeGeometry(new THREE.CatmullRomCurve3([
      new THREE.Vector3(0.1, 1.0, 1.76), new THREE.Vector3(-1.2, 0.74, 1.8), new THREE.Vector3(-2.6, 0.62, 1.8), new THREE.Vector3(-3.8, 0.6, 1.8)]), 30, 0.15, 20), pipeMat, { edges: false }));

    /* ---------- gas-flow particles ---------- */
    const flow = new THREE.Group();
    engine.add(flow);
    cyl.forEach((c) => {
      const cx = c.cx;
      c.inStream = stream([
        new THREE.Vector3(3.75, PLENUM.y + 0.35, PLENUM.z - 0.1), new THREE.Vector3(3.2, PLENUM.y, PLENUM.z),
        new THREE.Vector3((cx + 3.0) / 2, PLENUM.y, PLENUM.z), new THREE.Vector3(cx, PLENUM.y, PLENUM.z + 0.08),
        new THREE.Vector3(cx, 2.72, -1.4), new THREE.Vector3(cx, 2.62, -0.85), new THREE.Vector3(cx, 2.48, -0.3),
        new THREE.Vector3(cx, 2.1, -0.1), new THREE.Vector3(cx, 1.8, 0.05)], C_IN, { parent: flow });
      c.exStream = stream([
        new THREE.Vector3(cx, 1.95, 0.05), new THREE.Vector3(cx, 2.3, 0.2), new THREE.Vector3(cx, 2.5, 0.32),
        new THREE.Vector3(cx, 2.6, 0.85), new THREE.Vector3(cx, 2.32, 1.35), new THREE.Vector3(cx * 0.55, 1.55, 1.66),
        new THREE.Vector3(cx * 0.12, 1.02, 1.76), new THREE.Vector3(-1.2, 0.74, 1.8), new THREE.Vector3(-3.9, 0.6, 1.8)], C_EX, { parent: flow });
    });

    /* ---------- casing (hidden-line ghost) ---------- */
    const casing = new THREE.Group();
    engine.add(casing);
    const box = (w, hh, d, y) => { const g = ghost(new THREE.BoxGeometry(w, hh, d)); g.position.y = y; casing.add(g); };
    box(4.75, 2.6, 1.5, HEAD_Y - 1.3);
    box(4.75, 1.25, 1.75, HEAD_Y + 0.625);
    box(4.4, 0.75, 1.3, -0.725);
    CYL_X.forEach((cx) => {
      const liner = ghost(new THREE.CylinderGeometry(BORE + 0.02, BORE + 0.02, 1.35, 40, 1, true));
      liner.position.set(cx, HEAD_Y - 0.675, 0);
      casing.add(liner);
    });

    // focus ring on the deck of the followed cylinder
    const focusRing = inkRing(BORE + 0.1, 0, new THREE.LineBasicMaterial({ color: 0xffc857, transparent: true, opacity: 0.95 }), 64);
    focusRing.renderOrder = 6;
    focusRing.position.y = HEAD_Y;
    engine.add(focusRing);

    /* ---------- pose: everything from theta ---------- */
    let lastTheta = state.theta;
    function pose(theta, dt, s) {
      const dTheta = theta - lastTheta;
      lastTheta = theta;
      const thr = s.input;
      crank.rotation.x = theta * D2R;
      camshafts.forEach((g) => { g.rotation.x = (theta / 2) * D2R; });
      const s0 = mod((theta * D2R * CRANK_PULLEY) / beltLen, 1);   // belt teeth move at pulley surface speed
      const bp = beltPts.geometry.attributes.position;
      for (let k = 0; k < BELT_TEETH; k++) { beltCurve.getPointAt(mod(s0 + k / BELT_TEETH, 1), tmpV); bp.setXYZ(k, tmpV.x, tmpV.y, tmpV.z); }
      bp.needsUpdate = true;
      plate.rotation.y = thr * 1.35;

      cyl.forEach((c, i) => {
        const a = theta + THROW[i], ar = a * D2R;
        const py = R * Math.cos(ar), pz = R * Math.sin(ar), wy = pinHeight(a);
        c.rod.position.set(c.cx, py, pz);
        c.rod.rotation.x = Math.atan2(-pz, wy - py);
        c.piston.position.y = wy;
        const crown = wy + PIN_TO_CROWN;
        c.gas.position.y = crown;
        c.gas.scale.y = Math.max(0.001, HEAD_Y - crown);

        const phi = s.phi[i];
        const li = valveLift(phi, IN_MID), le = valveLift(phi, EX_MID);
        c.lift.in = li; c.lift.ex = le;
        for (const [k, lift] of [['in', li], ['ex', le]]) { c.valves[k].moving.position.y = -lift; c.valves[k].spring.scale.y = 0.37 - lift; }

        let col, op;
        if (phi < 180) { col = C_IN; op = 0.12 + 0.3 * (phi / 180) * (0.45 + 0.55 * thr); }
        else if (phi < SPARK_AT) { const k = (phi - 180) / (SPARK_AT - 180); col = tmpColor.copy(C_IN).lerp(C_CO, k); op = 0.42 + 0.33 * k; }
        else if (phi < 540) {
          const k = clamp01((phi - SPARK_AT) / (540 - SPARK_AT));
          col = k < 0.12 ? tmpColor.copy(C_CO).lerp(C_HOT, k / 0.12) : k < 0.45 ? tmpColor.copy(C_HOT).lerp(C_PW, (k - 0.12) / 0.33) : tmpColor.copy(C_PW).lerp(C_EMBER, (k - 0.45) / 0.55);
          op = 0.9 - 0.3 * k;
        } else { const k = (phi - 540) / 180; col = tmpColor.copy(C_EMBER).lerp(C_EX, Math.min(1, k * 2.5)); op = 0.6 - 0.45 * k; }
        c.gasMat.color.copy(col);
        c.gasMat.opacity = op;

        const sk = phi >= SPARK_AT - 2 && phi < SPARK_AT + 26 ? 1 - Math.abs(phi - (SPARK_AT + 6)) / 22 : 0;
        c.spark.scale.setScalar(Math.max(0.001, sk) * (0.55 + 0.35 * thr));
        c.spark.material.opacity = clamp01(sk * 1.4);

        // flow and heat follow how far the crank actually moved (scrub-safe)
        const step = Math.abs(dTheta) < 200 ? dTheta : 0;
        const inRate = (li / LIFT) * (0.35 + 0.65 * thr), exRate = le / LIFT;
        c.inStream.advance(step * inRate * 0.0042);
        c.exStream.advance(step * exRate * 0.0036);
        c.inFlow += ((li > 0.004 ? 1 : 0) - c.inFlow) * Math.min(1, dt * 6);
        c.exFlow += ((le > 0.004 ? 1 : 0) - c.exFlow) * Math.min(1, dt * 6);
        c.inStream.mat.opacity = c.inFlow * (0.5 + 0.5 * thr);
        c.exStream.mat.opacity = c.exFlow * 0.9;
        c.heat = Math.min(1, c.heat * Math.exp(-dt * 0.5) + exRate * Math.abs(step) * 0.004 * (0.5 + thr));
        exhaustMats[i].color.copy(EX_BASE).lerp(C_PW, c.heat * 0.8);   // heat = colour, not emissive (washes out on white)
      });
      const avgHeat = cyl.reduce((a, c) => a + c.heat, 0) / 4;
      pipeMat.color.copy(EX_BASE).lerp(C_PW, avgHeat * 0.55);
      const f = cyl[s.focus];
      focusRing.position.x = f.cx;
      focusRing.material.color.set(phaseColor(f, s));
    }
    const phaseColors = [C.in, C.co, C.pw, C.ex];
    const phaseColor = (f, s) => phaseColors[Math.floor(s.phi[f.i] / 180)];

    const focused = () => cyl[state.focus];
    const valveText = (lift) => (lift > 0.003 ? { text: `open ${Math.round(lift / LIFT * 100)}%`, cls: 'on' } : 'shut');
    return {
      root: engine,
      pose,
      setLayer(key, on) {
        if (key === 'casing') casing.visible = on;
        if (key === 'flow') { flow.visible = on; cyl.forEach((c) => { c.gas.visible = on; }); }
      },
      tagAnchor(i, v, where) {
        const cx = CYL_X[i];
        if (where === 'below') return v.set(cx, -1.4, -0.7);
        if (where === 'above') return v.set(cx, HEAD_Y + 2.05, 0);
        return v.set(cx, HEAD_Y + 1.15, 0);     // 'point': top of the spark plug
      },
      callouts: [
        { n: 1, name: 'Spark plug', at: (v) => focused().plug.localToWorld(v.set(0, 1.08, 0)) },
        { n: 2, name: 'Camshaft', at: (v) => v.set(-1.15, ...camYZ(-1)) },
        { n: 3, name: 'Intake valve', at: (v) => focused().valves.in.fixed.localToWorld(v.set(0, 0.55, 0)) },
        { n: 4, name: 'Exhaust valve', at: (v) => focused().valves.ex.fixed.localToWorld(v.set(0, 0.5, 0)) },
        { n: 5, name: 'Piston', at: (v) => focused().piston.localToWorld(v.set(0, 0.05, -BORE)) },
        { n: 6, name: 'Connecting rod', at: (v) => focused().rod.localToWorld(v.set(0, L * 0.4, 0)) },
        { n: 7, name: 'Crankshaft', at: (v) => v.set(-0.6, -0.35, -0.3) },
        { n: 8, name: 'Flywheel', at: (v) => v.set(-2.7, -0.75, -0.7) },
        { n: 9, name: 'Timing belt', at: (v) => v.set(BELT_X, 1.4, -0.6) },
        { n: 10, name: 'Throttle', at: (v) => v.set(2.88, PLENUM.y + 0.22, PLENUM.z) },
        { n: 11, name: 'Intake manifold', at: (v) => v.set(-1.9, PLENUM.y + 0.2, PLENUM.z) },
        { n: 12, name: 'Exhaust manifold', at: (v) => v.set(-1.6, 0.72, 1.8) },
      ],
      readouts: [
        { label: 'Crank angle', value: ({ phi }) => `${Math.round(phi)}° of 720°` },
        { label: 'Intake valve', value: () => valveText(focused().lift.in) },
        { label: 'Exhaust valve', value: () => valveText(focused().lift.ex) },
        { label: 'Spark', value: ({ phi }) => (phi >= SPARK_AT - 2 && phi < SPARK_AT + 30 ? { text: 'FIRING', cls: 'hot' }
          : phi >= 180 && phi < SPARK_AT ? `in ${Math.round(SPARK_AT - phi)}°` : 'off') },
        { label: 'Cylinder pressure', value: ({ phi, s }) => `${pressure(phi, s.input).toFixed(1)} bar` },
      ],
    };
  },
};

// exported for the sound script and tests
export { pressure, chamber, SPARK_AT };
