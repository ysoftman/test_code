/* =========================================================================
   Mechanism: bicycle floor pump inflating a tyre.
   Driver variable theta = handle cycle degrees. One cycle = 360 (one up + one down stroke).
   phi 0 = piston at the bottom, 180 = at the top.
   The delivery phase starts where the barrel pressure reaches the tyre's, so its start
   moves later as the tyre fills: bounds() is computed from state every frame.
   ========================================================================= */
import { HUES, mod, clamp01, smooth, D2R } from '../kit.js';

// ---------- geometry (scene units) ----------
const BARREL_R = 0.42, WALL = 0.03;
const BARREL_Y0 = 0.72, BARREL_Y1 = 4.35;
const PB0 = 0.86;                   // piston bottom face at the bottom of the stroke
const STROKE = 3.0;
const HANDLE = BARREL_Y1 + 0.38 - PB0;   // handle height above the piston: sits just over the cap at the bottom
const ROD_LEN = HANDLE - 0.28;
const WHEEL = { x: 3.95, y: 1.96, R: 1.7, tube: 0.25, rim: 1.43 };
const VALVE_ANG = 215 * D2R;        // where the presta valve sits on the rim
const DEAD = 0.06;                  // dead volume under the piston, as a fraction of the stroke
const VMAX = 1 + DEAD;
const RATIO = 0.3;                  // barrel volume / tyre volume (sets how fast the tyre fills)
const TYRE_START = 0.4;             // bar (gauge): nearly flat

const h = (phi) => (1 - Math.cos(phi * D2R)) / 2;          // piston height 0..1
function openAngle(tyre) {                                  // where the check valve opens on the down stroke
  const pt = tyre + 1;
  const hOpen = VMAX / pt - DEAD;
  if (hOpen <= 0.002) return 359.5;
  return 360 - Math.acos(Math.max(-1, Math.min(1, 1 - 2 * hOpen))) / D2R;
}
function barrel(phi, tyre) {                                // absolute pressure under the piston (bar)
  const pt = tyre + 1, v = DEAD + h(phi);
  if (phi < 180) return Math.max(0.97, pt * DEAD / v);      // leftover air re-expands, then fresh air at ~1 bar
  return Math.min(VMAX / v, pt);
}

const C = { in: HUES.blue, co: HUES.ochre, pw: HUES.red };
const valvePos = (THREE) => new THREE.Vector3(WHEEL.x + WHEEL.rim * Math.cos(VALVE_ANG), WHEEL.y + WHEEL.rim * Math.sin(VALVE_ANG), 0);

export default {
  id: 'pump',
  meta: {
    pageTitle: 'How a Bike Pump Works',
    fig: 'Fig. 02',
    caption: 'Floor pump · cup seal · ball check valve',
    title: 'How a <em>bike pump</em> pushes air into a tyre',
    lede: 'Two valves and a rubber cup. Each stroke squeezes a barrel of air until it beats the tyre, then shoves it in.',
    titleBlock: { title: 'Floor pump', dwg: 'PMP-FL-002' },
    alt: 'Interactive 3D cutaway of a bicycle floor pump connected to a wheel',
    layout: 'figure',
  },
  cycle: 360,
  start: 30,
  phases: [
    { name: 'Up stroke', nick: 'draw', list: 'Draw', short: 'UP', key: 'Fresh air', color: C.in,
      text: 'The handle comes up. The cup seal is a soft rubber cone pointing down, so its lip folds in and air slips past it into the barrel underneath. The check valve at the bottom stays shut and keeps the tyre\'s air in the hose.' },
    { name: 'Squeeze', nick: 'build', list: 'Squeeze', short: 'SQUEEZE', key: 'Squeezed', color: C.co,
      text: 'Push down. The cup flares against the wall and seals, so the air under it is trapped and squeezed. Nothing leaves yet: the check valve only opens once the barrel beats the tyre. The harder the tyre, the longer this part lasts.' },
    { name: 'Deliver', nick: 'push', list: 'Push', short: 'DELIVER', key: 'Into the tyre', color: C.pw,
      text: 'The barrel pressure passes the tyre\'s, the ball lifts off its seat and the air rushes down the hose into the tyre. Every stroke adds a little more, so the gauge climbs.' },
  ],
  bounds: (s) => [0, 180, openAngle(s.mech.tyre ?? TYRE_START)],
  instances: { count: 1, label: 'Pump', short: 'Pump', offset: [0] },
  driver: {
    inputLabel: 'Pumping speed',
    inputHint: 'How fast you work the handle, in strokes per minute.',
    input: 0.4,
    target: (x) => 20 + 70 * x,                 // strokes per minute
    inputFormat: (x) => `${Math.round(20 + 70 * x)}/min`,
    inertia: 2.5,
    degPerSec: (spm) => (spm / 60) * 360,
  },
  speeds: [4, 2, 1],
  speed: 2,
  gauge: { max: 10, red: 8, minor: 0.5, major: 1, label: 'TYRE · BAR', unit: 'bar',
    value: (s) => s.mech.tyre ?? TYRE_START, readout: (v) => v.toFixed(1) },
  plot: { label: 'Barrel pressure vs volume', x: (phi) => (DEAD + h(phi)) / VMAX, y: (phi, s) => barrel(phi, s.mech.tyre ?? TYRE_START),
    yUnit: 'bar', xTicks: ['bottom', 'volume', 'top'], yMin: 3 },
  chart: {
    label: 'Stroke chart',
    note: 'Watch the red band: it starts later as the tyre fills, because the barrel has to out-push the tyre first.',
    markers: [],
  },
  layers: [{ key: 'barrel', label: 'Barrel', on: true }, { key: 'flow', label: 'Air flow', on: true }],
  actions: [{ label: 'Let air out', run: (s) => { s.mech.deflating = true; } }],
  view: { target: [2.15, 3.75, 0], dir: [1.6, 1.05, 4.2], radius: 4.3, radiusCompact: 4.9, radiusFigure: 4.2, minDist: 6, maxDist: 40,
    box: [[-1.5, 0, -0.9], [5.8, 7.9, 0.9]] },
  compactCallouts: [1, 4, 6, 8, 10],

  build(kit, { state }) {
    const { THREE, part, ghost, ghostRings, toon, M, lineMat, xCyl, inkRing, stream, scene, INK } = kit;
    const root = new THREE.Group();
    scene.add(root);
    state.mech.tyre = TYRE_START;
    state.mech.strokes = 0;
    const C_IN = new THREE.Color(C.in), C_CO = new THREE.Color(C.co), C_PW = new THREE.Color(C.pw);
    const tmpColor = new THREE.Color();
    const zCyl = (r, len, seg = 32) => new THREE.CylinderGeometry(r, r, len, seg).rotateX(Math.PI / 2);

    /* ---------- floor + foot plate + base ---------- */
    root.add(new THREE.Line(new THREE.BufferGeometry().setFromPoints([new THREE.Vector3(-1.9, 0, 0), new THREE.Vector3(6.3, 0, 0)]), lineMat));
    const foot = part(new THREE.BoxGeometry(2.6, 0.14, 1.1), M.dark);
    foot.position.set(0, 0.07, 0);
    root.add(foot);
    const baseGroup = new THREE.Group();
    root.add(baseGroup);
    const baseShell = ghost(new THREE.CylinderGeometry(0.62, 0.7, 0.58, 40));
    baseShell.position.y = 0.43;
    baseGroup.add(baseShell);
    const seat = part(new THREE.CylinderGeometry(0.16, 0.2, 0.08, 24), M.steel);   // valve seat
    seat.position.y = 0.6;
    root.add(seat);
    const ball = part(new THREE.SphereGeometry(0.12, 24, 16), M.ceramic);
    ball.position.y = 0.5;
    root.add(ball);
    const outlet = part(xCyl(0.09, 0.62, 18), M.steel);
    outlet.position.set(0.55, 0.36, 0.12);
    root.add(outlet);

    /* ---------- barrel (translucent, so the piston shows) ---------- */
    const barrelGroup = new THREE.Group();
    root.add(barrelGroup);
    const barrelMesh = part(new THREE.CylinderGeometry(BARREL_R, BARREL_R, BARREL_Y1 - BARREL_Y0, 48, 1, true), M.glass, { edges: false, outline: false });
    barrelMesh.position.y = (BARREL_Y0 + BARREL_Y1) / 2;
    barrelGroup.add(barrelMesh);
    const barrelLines = ghost(new THREE.CylinderGeometry(BARREL_R + 0.005, BARREL_R + 0.005, BARREL_Y1 - BARREL_Y0, 48, 1, true));
    barrelLines.position.y = barrelMesh.position.y;
    barrelGroup.add(barrelLines);
    [BARREL_Y0, BARREL_Y1].forEach((y) => barrelGroup.add(inkRing(BARREL_R + 0.005, y, lineMat, 64)));
    const cap = part(new THREE.CylinderGeometry(BARREL_R + 0.05, BARREL_R + 0.05, 0.26, 40), M.dark);
    cap.position.y = BARREL_Y1 + 0.1;
    root.add(cap);
    const collar = part(new THREE.CylinderGeometry(BARREL_R + 0.06, BARREL_R + 0.1, 0.2, 40), M.dark);
    collar.position.y = BARREL_Y0 + 0.02;
    root.add(collar);
    const vent = part(xCyl(0.05, 0.12, 12), M.rubber, { outline: false });   // air inlet under the cap
    vent.position.set(BARREL_R + 0.02, BARREL_Y1 - 0.12, 0);
    root.add(vent);

    /* ---------- piston, cup seal, rod, handle ---------- */
    const moving = new THREE.Group();
    root.add(moving);
    const head = part(new THREE.CylinderGeometry(BARREL_R - 0.09, BARREL_R - 0.09, 0.16, 36), M.alloy);
    head.position.y = 0.2;
    moving.add(head);
    const cupGeo = new THREE.CylinderGeometry(BARREL_R - 0.1, BARREL_R - WALL, 0.2, 40, 1, true);  // cone, lip at the bottom
    const cup = part(cupGeo, M.rubber);
    cup.position.y = 0.1;
    moving.add(cup);
    const rod = part(new THREE.CylinderGeometry(0.055, 0.055, ROD_LEN, 16), M.steel);
    rod.position.y = 0.28 + ROD_LEN / 2;
    moving.add(rod);
    const handleY = HANDLE;
    const tee = part(new THREE.CylinderGeometry(0.1, 0.1, 0.24, 20), M.dark);
    tee.position.y = handleY;
    moving.add(tee);
    const bar = part(xCyl(0.075, 2.0, 18), M.steel);
    bar.position.y = handleY;
    moving.add(bar);
    [-0.78, 0.78].forEach((x) => { const g = part(xCyl(0.13, 0.55, 24), M.rubber); g.position.set(x, handleY, 0); moving.add(g); });

    /* ---------- air column under the piston ---------- */
    const gasMat = new THREE.MeshBasicMaterial({ color: C_IN, transparent: true, opacity: 0.25, depthWrite: false });
    const gas = new THREE.Mesh(new THREE.CylinderGeometry(BARREL_R - WALL - 0.005, BARREL_R - WALL - 0.005, 1, 40).translate(0, 0.5, 0), gasMat);
    gas.position.y = BARREL_Y0;
    gas.renderOrder = 2;
    root.add(gas);

    /* ---------- hose ---------- */
    const vp = valvePos(THREE);
    const inward = new THREE.Vector3(WHEEL.x, WHEEL.y, 0).sub(vp).normalize();
    const stemEnd = vp.clone().addScaledVector(inward, 0.36);
    const hoseCurve = new THREE.CatmullRomCurve3([
      new THREE.Vector3(0.86, 0.36, 0.12), new THREE.Vector3(1.5, 0.22, 0.45), new THREE.Vector3(2.25, 0.5, 0.62),
      stemEnd.clone().add(new THREE.Vector3(-0.32, -0.35, 0.36)), stemEnd.clone().add(new THREE.Vector3(-0.05, -0.04, 0.12))]);
    root.add(part(new THREE.TubeGeometry(hoseCurve, 60, 0.085, 16), M.glass, { edges: false, outline: false }));
    root.add(ghostRings(hoseCurve, 0.085, 7));
    const chuck = part(new THREE.CylinderGeometry(0.11, 0.11, 0.3, 20), M.dark);
    chuck.position.copy(stemEnd).addScaledVector(inward, -0.02);
    chuck.quaternion.setFromUnitVectors(new THREE.Vector3(0, 1, 0), inward);
    root.add(chuck);

    /* ---------- wheel ---------- */
    const wheel = new THREE.Group();
    wheel.position.set(WHEEL.x, WHEEL.y, 0);
    root.add(wheel);
    const tyre = part(new THREE.TorusGeometry(WHEEL.R, WHEEL.tube, 20, 96), M.rubber, { edges: false });
    wheel.add(tyre);
    const tyreAirMat = new THREE.MeshBasicMaterial({ color: C_PW, transparent: true, opacity: 0.0, depthWrite: false });
    const tyreAir = new THREE.Mesh(new THREE.TorusGeometry(WHEEL.R, WHEEL.tube * 0.62, 12, 96), tyreAirMat);
    tyreAir.position.z = WHEEL.tube * 0.45;
    tyreAir.renderOrder = 4;
    wheel.add(tyreAir);
    const rim = part(new THREE.TorusGeometry(WHEEL.rim, 0.06, 10, 96), M.steel);
    wheel.add(rim);
    const hub = part(zCyl(0.16, 0.3, 24), M.steel);
    wheel.add(hub);
    const spokes = [];
    for (let k = 0; k < 20; k++) {
      const a = k / 20 * Math.PI * 2 + 0.08, side = k % 2 ? 0.11 : -0.11;
      spokes.push(new THREE.Vector3(0, 0, side), new THREE.Vector3(Math.cos(a) * WHEEL.rim, Math.sin(a) * WHEEL.rim, 0));
    }
    wheel.add(new THREE.LineSegments(new THREE.BufferGeometry().setFromPoints(spokes), lineMat));
    const stem = part(new THREE.CylinderGeometry(0.035, 0.035, 0.42, 10), M.steel);
    stem.position.copy(vp).addScaledVector(inward, 0.15);
    stem.quaternion.setFromUnitVectors(new THREE.Vector3(0, 1, 0), inward);
    root.add(stem);

    /* ---------- pressure gauge on the base ---------- */
    const gauge = new THREE.Group();
    gauge.position.set(-0.78, 0.38, 0.5);
    gauge.rotation.x = 1.15;
    root.add(gauge);
    gauge.add(part(new THREE.CylinderGeometry(0.34, 0.34, 0.1, 40), M.dark));
    const face = new THREE.Mesh(new THREE.CircleGeometry(0.29, 40).rotateX(-Math.PI / 2), new THREE.MeshBasicMaterial({ color: 0xffffff }));
    face.position.y = 0.052;
    gauge.add(face);
    const ticks = [];
    for (let k = 0; k <= 10; k++) {
      const a = (-225 + 270 * k / 10) * D2R, r0 = k % 5 === 0 ? 0.19 : 0.22;
      ticks.push(new THREE.Vector3(Math.cos(a) * r0, 0.055, -Math.sin(a) * r0), new THREE.Vector3(Math.cos(a) * 0.27, 0.055, -Math.sin(a) * 0.27));
    }
    gauge.add(new THREE.LineSegments(new THREE.BufferGeometry().setFromPoints(ticks), lineMat));
    const needle = new THREE.Group();
    needle.position.y = 0.058;
    needle.add(new THREE.Line(new THREE.BufferGeometry().setFromPoints([new THREE.Vector3(0, 0, 0), new THREE.Vector3(0.24, 0, 0)]), new THREE.LineBasicMaterial({ color: 0xe5482f })));
    gauge.add(needle);

    /* ---------- air flow ---------- */
    const flow = new THREE.Group();
    root.add(flow);
    const inStream = stream([
      new THREE.Vector3(BARREL_R + 0.55, BARREL_Y1 - 0.05, 0.05), new THREE.Vector3(BARREL_R + 0.1, BARREL_Y1 - 0.12, 0),
      new THREE.Vector3(BARREL_R - 0.08, BARREL_Y1 - 0.3, 0), new THREE.Vector3(BARREL_R - 0.08, 2.6, 0.05),
      new THREE.Vector3(BARREL_R - 0.1, 1.4, 0.08), new THREE.Vector3(0.1, 0.9, 0.12)], C_IN, { parent: flow, count: 34 });
    const outPts = [new THREE.Vector3(0, 1.0, 0), new THREE.Vector3(0, 0.62, 0), new THREE.Vector3(0.1, 0.4, 0.05),
      new THREE.Vector3(0.6, 0.36, 0.12), ...hoseCurve.getPoints(14).slice(1), stemEnd.clone(), vp.clone().addScaledVector(inward, -0.08),
      new THREE.Vector3(WHEEL.x + WHEEL.R * Math.cos(VALVE_ANG + 0.25), WHEEL.y + WHEEL.R * Math.sin(VALVE_ANG + 0.25), 0.1),
      new THREE.Vector3(WHEEL.x + WHEEL.R * Math.cos(VALVE_ANG + 0.55), WHEEL.y + WHEEL.R * Math.sin(VALVE_ANG + 0.55), 0.1)];
    const outStream = stream(outPts, C_PW, { parent: flow, count: 46 });
    let inFlow = 0, outFlow = 0;

    /* ---------- pose ---------- */
    let lastTheta = state.theta;
    const fill = () => clamp01(state.mech.tyre / 8);
    function pose(theta, dt, s) {
      const dTheta = theta - lastTheta;
      lastTheta = theta;
      const m = s.mech;
      const phi = s.phi[0];
      const hh = h(phi);
      moving.position.y = PB0 + STROKE * hh;

      // tyre fills only while the crank moves forward through the delivery phase
      const step = Math.abs(dTheta) < 180 ? dTheta : 0;
      const open = openAngle(m.tyre);
      if (step > 0 && !m.deflating) {
        const prevPhi = mod(phi - step, 360);
        const lo = Math.max(open, prevPhi < phi ? prevPhi : open), hi = phi;
        if (hi > lo && phi >= open) m.tyre += RATIO * (m.tyre + 1) * Math.max(0, h(lo) - h(hi));
        if (prevPhi > phi) m.strokes += 1;
      }
      if (m.deflating) { m.tyre = Math.max(TYRE_START, m.tyre - dt * 3.5); if (m.tyre <= TYRE_START) m.deflating = false; }

      // cup seal: lip folds in going up, flares out going down
      const flare = phi < 180 ? 1 - smooth(4, 18, phi) : smooth(180, 194, phi);
      cup.scale.set(0.84 + 0.16 * flare, 1, 0.84 + 0.16 * flare);

      // check valve: ball lifts while delivering
      const lift = phi >= open ? smooth(open, Math.min(open + 6, 359.9), phi) * (1 - smooth(354, 360, phi)) : 0;
      ball.position.y = 0.5 - 0.11 * lift;      // pushed down off its seat by the air from above
      ball.position.x = 0.05 * lift;

      // air column under the piston
      const pb = barrel(phi, m.tyre), pt = m.tyre + 1;
      gas.scale.y = Math.max(0.001, PB0 + STROKE * hh - BARREL_Y0);
      if (phi < 180) { gasMat.color.copy(C_IN); gasMat.opacity = 0.22; }
      else if (phi < open) { const k = clamp01((pb - 1) / Math.max(0.01, pt - 1)); gasMat.color.copy(tmpColor.copy(C_IN).lerp(C_CO, k)); gasMat.opacity = 0.25 + 0.4 * k; }
      else { gasMat.color.copy(C_PW); gasMat.opacity = 0.65; }

      // streams move with the handle, never with wall time
      inFlow += ((phi < 180 && phi > 12 ? 1 : 0) - inFlow) * Math.min(1, dt * 8);
      outFlow += ((phi >= open ? 1 : 0) - outFlow) * Math.min(1, dt * 8);
      inStream.advance(Math.max(0, step) * 0.0045);
      outStream.advance(Math.max(0, step) * 0.011);
      inStream.mat.opacity = inFlow * 0.95;
      outStream.mat.opacity = outFlow * 0.95;

      // tyre: a touch rounder and warmer as it fills; gauge needle
      const f = fill();
      tyre.scale.set(1, 1, 0.82 + 0.18 * f);
      tyreAirMat.opacity = 0.08 + 0.32 * f;
      tyreAirMat.color.copy(tmpColor.copy(C_IN).lerp(C_PW, f));
      needle.rotation.y = (-225 + 270 * clamp01(m.tyre / 10)) * D2R;
    }

    const valveState = () => {
      const phi = state.phi[0];
      return phi >= openAngle(state.mech.tyre) ? { text: 'open', cls: 'on' } : 'shut';
    };
    return {
      root,
      pose,
      setLayer(key, on) {
        if (key === 'barrel') { barrelGroup.visible = on; baseGroup.visible = on; }
        if (key === 'flow') { flow.visible = on; gas.visible = on; tyreAir.visible = on; }
      },
      callouts: [
        { n: 1, name: 'Handle', at: (v) => v.set(-0.78, moving.position.y + handleY, 0) },
        { n: 2, name: 'Piston rod', at: (v) => v.set(0, moving.position.y + 0.28 + ROD_LEN * 0.28, 0) },
        { n: 3, name: 'Barrel', at: (v) => v.set(-BARREL_R, 2.4, 0.1) },
        { n: 4, name: 'Cup seal', at: (v) => v.set(-(BARREL_R - 0.05), moving.position.y + 0.08, 0.1) },
        { n: 5, name: 'Air inlet', at: (v) => v.set(BARREL_R + 0.06, BARREL_Y1 - 0.12, 0) },
        { n: 6, name: 'Check valve', at: (v) => ball.getWorldPosition(v) },
        { n: 7, name: 'Hose', at: (v) => hoseCurve.getPointAt(0.45, v) },
        { n: 8, name: 'Pressure gauge', at: (v) => gauge.localToWorld(v.set(0, 0.06, 0)) },
        { n: 9, name: 'Presta valve', at: (v) => v.copy(stemEnd) },
        { n: 10, name: 'Tyre', at: (v) => v.set(WHEEL.x + WHEEL.R * 0.71, WHEEL.y + WHEEL.R * 0.71, WHEEL.tube) },
        { n: 11, name: 'Foot plate', at: (v) => v.set(-1.1, 0.14, 0.4) },
      ],
      readouts: [
        { label: 'Handle', value: ({ phi }) => `${Math.round(h(phi) * 100)}% up, ${phi < 180 ? 'rising' : 'falling'}` },
        { label: 'Cup seal', value: ({ phi }) => (phi < 180 ? 'lip folded, air passes' : { text: 'sealed', cls: 'on' }) },
        { label: 'Check valve', value: valveState },
        { label: 'Barrel pressure', value: ({ phi, s }) => `${(barrel(phi, s.mech.tyre) - 1).toFixed(1)} bar` },
        { label: 'Tyre pressure', value: ({ s }) => ({ text: `${s.mech.tyre.toFixed(1)} bar`, cls: s.mech.tyre >= 8 ? 'hot' : '' }) },
      ],
    };
  },
};
