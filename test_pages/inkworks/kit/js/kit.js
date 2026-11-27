/* =========================================================================
   Inkworks: 3D rendering kit
   Ink-outlined toon parts, hidden-line ghosts, flow particles and helpers.
   Mechanism files get all of this as `kit` in build(kit).
   ========================================================================= */
import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';

export { THREE };

export const D2R = Math.PI / 180;
export const mod = (a, n) => ((a % n) + n) % n;
export const clamp01 = (x) => Math.min(1, Math.max(0, x));
export const smooth = (a, b, x) => { const t = clamp01((x - a) / (b - a)); return t * t * (3 - 2 * t); };

export const INK_HEX = '#161b26';
export const PAPER_HEX = '#f8f9fb';
/** The four phase hues. Re-map their meaning per mechanism, keep the hues. */
export const HUES = { blue: '#2f7de1', ochre: '#d98e04', red: '#e5482f', grey: '#7b8494' };

export function makeKit(canvas) {
  const INK = new THREE.Color(INK_HEX);

  const renderer = new THREE.WebGLRenderer({ canvas, antialias: true, alpha: true, preserveDrawingBuffer: false });
  renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
  renderer.setClearColor(0x000000, 0);          // transparent: the CSS grid paper shows through
  renderer.outputColorSpace = THREE.SRGBColorSpace;

  const scene = new THREE.Scene();
  const camera = new THREE.PerspectiveCamera(30, 1, 0.1, 200);
  const controls = new OrbitControls(camera, canvas);
  controls.enableDamping = true;
  controls.dampingFactor = 0.08;
  controls.enablePan = false;
  controls.autoRotateSpeed = 0.6;

  scene.add(new THREE.HemisphereLight(0xffffff, 0x8a96aa, 1.5));
  const sun = new THREE.DirectionalLight(0xffffff, 2.2);
  sun.position.set(4, 8, 6);
  scene.add(sun);

  // three-step toon ramp: flat "hand-coloured drawing" shading
  const ramp = new THREE.DataTexture(new Uint8Array([150, 150, 150, 255, 205, 205, 205, 255, 255, 255, 255, 255]), 3, 1);
  ramp.minFilter = ramp.magFilter = THREE.NearestFilter;
  ramp.needsUpdate = true;

  const toon = (hex, extra = {}) => new THREE.MeshToonMaterial({
    color: hex, gradientMap: ramp, polygonOffset: true, polygonOffsetFactor: 1, polygonOffsetUnits: 1, ...extra,
  });
  /** Shared materials. glass = translucent tinted volume (manifolds, barrels, fluids). */
  const M = {
    steel: toon('#c3ccd8'),
    alloy: toon('#eef1f5'),
    dark: toon('#a4afbe'),
    valve: toon('#dde3ec'),
    ceramic: toon('#ffffff'),
    rubber: toon('#8f98a7'),
    copper: toon('#d39a63'),
    glass: toon('#8dbcf2', { transparent: true, opacity: 0.26, depthWrite: false, polygonOffset: false }),
  };
  const lineMat = new THREE.LineBasicMaterial({ color: INK, transparent: true, opacity: 0.85 });
  const ghostLine = new THREE.LineDashedMaterial({ color: INK, transparent: true, opacity: 0.45, dashSize: 0.09, gapSize: 0.07 });
  const ghostFill = new THREE.MeshBasicMaterial({ color: 0x6b8ab0, transparent: true, opacity: 0.035, depthWrite: false, side: THREE.DoubleSide });

  // silhouette: inverted hull pushed out by a constant number of screen pixels (uPx set by the layout)
  const outlineMat = new THREE.ShaderMaterial({
    uniforms: { uColor: { value: INK.clone() }, uPx: { value: 0.002 } },
    vertexShader: /* glsl */`
      uniform float uPx;
      void main() {
        vec4 mv = modelViewMatrix * vec4(position, 1.0);
        vec3 n = normalize(normalMatrix * normal);
        mv.xyz += n * uPx * max(-mv.z, 0.1);
        gl_Position = projectionMatrix * mv;
      }`,
    fragmentShader: /* glsl */`
      uniform vec3 uColor;
      void main() { gl_FragColor = vec4(uColor, 1.0); }`,
    side: THREE.BackSide,
  });

  /** A solid part: toon mesh + ink feature edges + silhouette outline. */
  function part(geo, mat, { edges = 30, outline = true } = {}) {
    const g = new THREE.Group();
    g.add(new THREE.Mesh(geo, mat));
    if (edges) g.add(new THREE.LineSegments(new THREE.EdgesGeometry(geo, edges), lineMat));
    if (outline) g.add(new THREE.Mesh(geo, outlineMat));
    return g;
  }
  /** Hidden-line ghost: barely-there fill + dashed ink edges. Use for casings and housings. */
  function ghost(geo, threshold = 30) {
    const g = new THREE.Group();
    g.add(new THREE.Mesh(geo, ghostFill));
    const l = new THREE.LineSegments(new THREE.EdgesGeometry(geo, threshold), ghostLine);
    l.computeLineDistances();
    g.add(l);
    return g;
  }
  /** Dashed rings along a tube curve, so a translucent pipe still reads as a pipe. */
  function ghostRings(curve, r, count = 5) {
    const g = new THREE.Group();
    const frames = curve.computeFrenetFrames(24, false);
    for (let i = 0; i < count; i++) {
      const k = Math.round(i / (count - 1) * 24);
      const c = curve.getPointAt(k / 24), n = frames.normals[k], b = frames.binormals[k];
      const ring = [];
      for (let j = 0; j <= 24; j++) { const a = j / 24 * Math.PI * 2; ring.push(c.clone().addScaledVector(n, Math.cos(a) * r).addScaledVector(b, Math.sin(a) * r)); }
      const l = new THREE.Line(new THREE.BufferGeometry().setFromPoints(ring), ghostLine);
      l.computeLineDistances();
      g.add(l);
    }
    return g;
  }
  /** A short red line: timing marks that make rotation visible. */
  function markLine(len, r0, color = 0xe5482f) {
    const g = new THREE.BufferGeometry().setFromPoints([new THREE.Vector3(0, r0, 0), new THREE.Vector3(0, r0 + len, 0)]);
    return new THREE.Line(g, new THREE.LineBasicMaterial({ color }));
  }
  /** Ink ring (LineLoop) in the XZ plane. */
  function inkRing(r, y = 0, mat = lineMat, seg = 48) {
    return new THREE.LineLoop(new THREE.BufferGeometry().setFromPoints(
      Array.from({ length: seg }, (_, k) => new THREE.Vector3(Math.cos(k / seg * Math.PI * 2) * r, y, Math.sin(k / seg * Math.PI * 2) * r))), mat);
  }

  // ---------- geometry helpers ----------
  /** Cylinder whose axis runs along X. */
  const xCyl = (r, len, seg = 32, open = false) => new THREE.CylinderGeometry(r, r, len, seg, 1, open).rotateZ(Math.PI / 2);
  /** rotation.x that points a "-Z feature" at direction (dy, dz). */
  const aimX = (dy, dz) => Math.atan2(dy, -dz);
  /** Spur gear outline extruded along X. */
  function gearGeometry(r, teeth, depth, hole = 0.18, toothH = 0.05) {
    const s = new THREE.Shape();
    for (let k = 0; k <= teeth * 4; k++) {
      const a = (k / (teeth * 4)) * Math.PI * 2;
      const rr = (k % 4 < 2) ? r : r - toothH;
      k === 0 ? s.moveTo(rr * Math.cos(a), rr * Math.sin(a)) : s.lineTo(rr * Math.cos(a), rr * Math.sin(a));
    }
    if (hole) { const h = new THREE.Path(); h.absarc(0, 0, hole, 0, Math.PI * 2, true); s.holes.push(h); }
    const g = new THREE.ExtrudeGeometry(s, { depth, bevelEnabled: false, curveSegments: 16 });
    g.rotateY(Math.PI / 2);
    g.translate(-depth / 2, 0, 0);
    return g;
  }
  /** Coil spring of unit height along +Y (scale.y to compress it). */
  function springGeometry(r = 0.07, turns = 6, wire = 0.009) {
    const pts = [];
    const N = turns * 20;
    for (let k = 0; k <= N; k++) {
      const a = (k / N) * turns * Math.PI * 2;
      pts.push(new THREE.Vector3(Math.cos(a) * r, k / N, Math.sin(a) * r));
    }
    return new THREE.TubeGeometry(new THREE.CatmullRomCurve3(pts), N * 2, wire, 5);
  }
  /** 2D convex hull of [x, y] points (belts, chains). */
  function hull(pts) {
    pts = pts.slice().sort((a, b) => a[0] - b[0] || a[1] - b[1]);
    const cross = (o, a, b) => (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0]);
    const lo = [], up = [];
    for (const p of pts) { while (lo.length >= 2 && cross(lo[lo.length - 2], lo[lo.length - 1], p) <= 0) lo.pop(); lo.push(p); }
    for (let k = pts.length - 1; k >= 0; k--) { const p = pts[k]; while (up.length >= 2 && cross(up[up.length - 2], up[up.length - 1], p) <= 0) up.pop(); up.push(p); }
    up.pop(); lo.pop();
    return lo.concat(up);
  }

  // ---------- flashes and flow ----------
  let flashTex = null;
  /** Radial yellow-to-red burst with rays (sparks, impacts). Normal blending: additive vanishes on white. */
  function flashTexture() {
    if (flashTex) return flashTex;
    const cv = document.createElement('canvas'); cv.width = cv.height = 128;
    const x = cv.getContext('2d');
    const g = x.createRadialGradient(64, 64, 0, 64, 64, 64);
    g.addColorStop(0, 'rgba(255,252,235,1)'); g.addColorStop(0.22, 'rgba(255,201,58,.95)'); g.addColorStop(0.6, 'rgba(229,72,47,.35)'); g.addColorStop(1, 'rgba(229,72,47,0)');
    x.fillStyle = g; x.fillRect(0, 0, 128, 128);
    x.strokeStyle = 'rgba(229,72,47,.95)'; x.lineWidth = 3.5;
    for (let k = 0; k < 8; k++) {
      const a = k * Math.PI / 4, r = k % 2 ? 34 : 60;
      x.beginPath(); x.moveTo(64, 64); x.lineTo(64 + Math.cos(a) * r, 64 + Math.sin(a) * r); x.stroke();
    }
    flashTex = new THREE.CanvasTexture(cv);
    flashTex.colorSpace = THREE.SRGBColorSpace;
    return flashTex;
  }
  function flash(size = 0.001) {
    const sp = new THREE.Sprite(new THREE.SpriteMaterial({ map: flashTexture(), color: 0xffffff, transparent: true, depthWrite: false, depthTest: false }));
    sp.scale.setScalar(size);
    sp.renderOrder = 5;
    return sp;
  }

  const dotTex = (() => {
    const cv = document.createElement('canvas'); cv.width = cv.height = 32;
    const x = cv.getContext('2d');
    x.fillStyle = '#fff'; x.beginPath(); x.arc(16, 16, 13, 0, Math.PI * 2); x.fill();
    return new THREE.CanvasTexture(cv);
  })();
  const tmp = new THREE.Vector3();
  /**
   * A stream of dots along a path. Move it with advance(dt) where dt is the fraction of the path
   * travelled this frame: tie it to how far the driver variable moved, never to wall time,
   * so scrubbing and slow motion stay in sync.
   */
  function stream(points, color, { count = 30, size = 6, parent = null } = {}) {
    const curve = new THREE.CatmullRomCurve3(points, false, 'centripetal');
    const geo = new THREE.BufferGeometry().setAttribute('position', new THREE.Float32BufferAttribute(new Float32Array(count * 3), 3));
    const mat = new THREE.PointsMaterial({ color, size, sizeAttenuation: false, map: dotTex, alphaTest: 0.01, transparent: true, opacity: 0, depthWrite: false });
    const pts = new THREE.Points(geo, mat);
    pts.renderOrder = 3;
    if (parent) parent.add(pts);
    const t = Array.from({ length: count }, (_, k) => (k + Math.random() * 0.6) / count);
    const s = {
      points: pts, curve, mat, t,
      advance(dt) {
        const pos = geo.attributes.position;
        for (let k = 0; k < count; k++) {
          t[k] = mod(t[k] + dt, 1);
          curve.getPointAt(t[k], tmp);
          pos.setXYZ(k, tmp.x, tmp.y, tmp.z);
        }
        pos.needsUpdate = true;
      },
    };
    s.advance(0);
    return s;
  }

  return {
    THREE, renderer, scene, camera, controls, INK,
    toon, M, lineMat, ghostLine, ghostFill, outlineMat,
    part, ghost, ghostRings, markLine, inkRing,
    xCyl, aimX, gearGeometry, springGeometry, hull,
    flash, flashTexture, stream,
    D2R, mod, clamp01, smooth, HUES,
  };
}
