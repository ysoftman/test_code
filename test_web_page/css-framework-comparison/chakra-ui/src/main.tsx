import React from "react";
import ReactDOM from "react-dom/client";
import {
  ChakraProvider,
  createSystem,
  defaultConfig,
  defineConfig,
} from "@chakra-ui/react";
import { ColorModeProvider } from "./color-mode";
import App from "./App";

// 다른 프레임워크와 동일한 시스템 폰트로 통일
const FONT =
  '-apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif';
const system = createSystem(
  defaultConfig,
  defineConfig({
    theme: {
      tokens: {
        fonts: {
          heading: { value: FONT },
          body: { value: FONT },
        },
      },
    },
  }),
);

ReactDOM.createRoot(document.getElementById("root")!).render(
  <React.StrictMode>
    <ChakraProvider value={system}>
      <ColorModeProvider>
        <App />
      </ColorModeProvider>
    </ChakraProvider>
  </React.StrictMode>,
);

// 로딩 속도(FCP) 측정값을 비교 페이지(부모)로 보고
try {
  new PerformanceObserver((list, obs) => {
    const fcp = list
      .getEntries()
      .find((e) => e.name === "first-contentful-paint");
    if (fcp) {
      window.parent.postMessage(
        { type: "perf", name: "Chakra UI", fcp: Math.round(fcp.startTime) },
        "*",
      );
      obs.disconnect();
    }
  }).observe({ type: "paint", buffered: true });
} catch {
  /* PerformanceObserver 미지원 무시 */
}
