import React from "react";
import ReactDOM from "react-dom/client";
import App from "./App";

ReactDOM.createRoot(document.getElementById("root")!).render(
  <React.StrictMode>
    <App />
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
        {
          type: "perf",
          name: "vanilla-extract",
          fcp: Math.round(fcp.startTime),
        },
        "*",
      );
      obs.disconnect();
    }
  }).observe({ type: "paint", buffered: true });
} catch {
  /* PerformanceObserver 미지원 무시 */
}
