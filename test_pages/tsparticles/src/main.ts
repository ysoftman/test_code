import { loadAll } from "@tsparticles/all";
import { type Container, type ISourceOptions, tsParticles } from "@tsparticles/engine";
import type { EmitterContainer } from "@tsparticles/plugin-emitters";
import "./style.css";

// 프리셋: 키 = 버튼 이름, 값 = tsParticles 옵션 객체
const presets: Record<string, ISourceOptions> = {
  Links: {
    background: { color: "#0f1115" },
    fpsLimit: 60,
    particles: {
      number: { value: 80, density: { enable: true } },
      color: { value: "#6ea8fe" },
      links: { enable: true, color: "#6ea8fe", distance: 150, opacity: 0.4, width: 1 },
      move: { enable: true, speed: 1.5, outModes: { default: "bounce" } },
      size: { value: { min: 1, max: 3 } },
      opacity: { value: 0.6 },
    },
    interactivity: {
      events: {
        onHover: { enable: true, mode: "grab" },
        onClick: { enable: true, mode: "push" },
      },
      modes: {
        grab: { distance: 180, links: { opacity: 0.8 } },
        push: { quantity: 4 },
      },
    },
  },
  Stars: {
    background: { color: "#05060a" },
    particles: {
      number: { value: 160, density: { enable: true } },
      color: { value: ["#ffffff", "#ffe9a8", "#a8c8ff"] },
      shape: { type: "star" },
      move: { enable: true, speed: 0.3 },
      size: { value: { min: 0.5, max: 2.5 } },
      opacity: {
        value: { min: 0.2, max: 1 },
        animation: { enable: true, speed: 1, sync: false },
      },
      twinkle: { particles: { enable: true, frequency: 0.05, opacity: 1 } },
    },
    interactivity: {
      events: { onHover: { enable: true, mode: "bubble" } },
      modes: { bubble: { distance: 120, size: 5, duration: 2, opacity: 1 } },
    },
  },
  Snow: {
    background: { color: "#0a0e1a" },
    particles: {
      number: { value: 200, density: { enable: true } },
      color: { value: "#ffffff" },
      shape: { type: "circle" },
      move: {
        enable: true,
        direction: "bottom",
        speed: { min: 1, max: 3 },
        straight: false,
      },
      size: { value: { min: 1, max: 4 } },
      opacity: { value: { min: 0.3, max: 0.8 } },
      wobble: { enable: true, distance: 10, speed: { min: -5, max: 5 } },
    },
  },
  Bubbles: {
    background: { color: "#021018" },
    particles: {
      number: { value: 0 },
      color: { value: ["#6ea8fe", "#5ad1c9", "#b18cff"] },
      shape: { type: "circle" },
      move: {
        enable: true,
        direction: "top",
        speed: { min: 1, max: 4 },
        outModes: { default: "destroy" },
      },
      size: { value: { min: 4, max: 16 } },
      opacity: { value: { min: 0.2, max: 0.6 } },
      stroke: { width: 1, color: "#ffffff55" },
    },
    emitters: {
      direction: "top",
      position: { x: 50, y: 100 },
      rate: { delay: 0.15, quantity: 2 },
      size: { width: 100, height: 0 },
    },
  },
  Confetti: {
    background: { color: "#0f1115" },
    fpsLimit: 60,
    particles: {
      number: { value: 0 },
      // roll/tilt 가 켜진 파티클은 color 대신 paint.fill.color 를 칠한다 (color 만 주면 흰색)
      paint: {
        fill: {
          enable: true,
          color: {
            value: [
              "#ff3b3b",
              "#ff9f1c",
              "#ffd60a",
              "#8ac926",
              "#06d6a0",
              "#00f5d4",
              "#22c1e8",
              "#4361ee",
              "#7209b7",
              "#b5179e",
              "#f72585",
              "#ff70a6",
            ],
          },
        },
      },
      shape: { type: ["square", "circle"] },
      opacity: {
        value: { min: 0, max: 1 },
        animation: { enable: true, speed: 0.8, startValue: "max", destroy: "min" },
      },
      size: { value: { min: 3, max: 7 } },
      life: { duration: { sync: true, value: 7 }, count: 1 },
      move: {
        enable: true,
        gravity: { enable: true, acceleration: 8 },
        speed: { min: 8, max: 22 },
        decay: 0.08,
        direction: "none",
        outModes: { default: "destroy", top: "none" },
      },
      rotate: {
        value: { min: 0, max: 360 },
        direction: "random",
        animation: { enable: true, speed: 30 },
      },
      tilt: {
        direction: "random",
        enable: true,
        value: { min: 0, max: 360 },
        animation: { enable: true, speed: 30 },
      },
      wobble: { distance: 20, enable: true, speed: { min: -7, max: 7 } },
    },
    // 화면 중앙에서 주기적으로(0.5초마다) 폭죽이 자동으로 터진다 (life.count: 0 = 무한)
    emitters: {
      position: { x: 50, y: 50 },
      size: { width: 0, height: 0 },
      rate: { delay: 0.5, quantity: 30 },
      life: { duration: 0.15, count: 0 },
    },
  },
};

const btnWrap = document.getElementById("presetButtons") as HTMLElement;
const codepre = document.getElementById("codepre") as HTMLElement;
const host = document.getElementById("tsparticles") as HTMLElement;

let container: Container | undefined;
let currentName = "";

async function apply(name: string) {
  currentName = name;
  for (const b of btnWrap.children) {
    b.classList.toggle("active", (b as HTMLElement).dataset.name === name);
  }
  codepre.textContent = JSON.stringify(presets[name], null, 2);
  // fullScreen 끄고 #tsparticles 컨테이너에 렌더 (UI 가 위에 오도록)
  container = await tsParticles.load({
    id: "tsparticles",
    options: { fullScreen: { enable: false }, ...presets[name] },
  });
}

// Confetti 프리셋에서 클릭한 위치에 일회성 폭죽 emitter 를 추가한다
host.addEventListener("pointerdown", (e) => {
  if (currentName !== "Confetti") return;
  const rect = host.getBoundingClientRect();
  (container as EmitterContainer | undefined)?.addEmitter?.({
    startCount: 40,
    position: {
      x: ((e.clientX - rect.left) / rect.width) * 100,
      y: ((e.clientY - rect.top) / rect.height) * 100,
    },
    size: { width: 0, height: 0 },
    rate: { delay: 0, quantity: 0 },
    life: { duration: 0.1, count: 1 },
  });
});

await loadAll(tsParticles);

for (const name of Object.keys(presets)) {
  const b = document.createElement("button");
  b.type = "button";
  b.textContent = name;
  b.dataset.name = name;
  b.onclick = () => apply(name);
  btnWrap.appendChild(b);
}

(document.getElementById("codeBtn") as HTMLElement).onclick = () => {
  document.getElementById("codepanel")?.classList.toggle("show");
};

await apply("Links");
