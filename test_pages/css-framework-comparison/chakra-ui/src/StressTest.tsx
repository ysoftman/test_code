// 렌더링 성능 테스트 (모든 프레임워크 앱 공통 · 프레임워크 비의존)
//
// 부모 비교 페이지가 { type: "stressRender", count } 메시지를 보내면
// count 개의 "프레임워크-네이티브" 아이템을 한 번에 렌더하고
//   1) 마운트 시간(metric: "mount")  2) 전체 리렌더 시간(metric: "update")
// 을 측정해 { type: "perf", name, metric, count, ms } 로 부모에 보고한다.
//
// 측정 방식: flushSync 로 React 렌더+커밋을 "동기적으로" 강제하고 그 앞뒤로
// performance.now() 차이를 잰다. CSS-in-JS(Emotion·styled-components)는 커밋
// 시점에 동기적으로 스타일을 생성·주입하므로 이 비용이 그대로 측정에 잡힌다.
// (브라우저 페인트는 제외 → 프레임 경계로 양자화되지 않아 프레임워크 간 차이가
//  깨끗하게 드러난다. rAF 기반으로 재면 vsync 에 동기화돼 값이 뭉친다.)
//
// 각 앱은 renderItem(i, tick) 으로 자기 프레임워크의 컴포넌트를 그린다.
// hue 를 index/tick 으로 바꿔, CSS-in-JS 의 런타임 스타일 생성 비용을 노출한다.
// (zero-runtime 계열은 동적 색을 inline style 로 주는 게 자연스러운 방식이라 그대로 둠)
import { Fragment, useEffect, useState, type ReactNode } from "react";
import { flushSync } from "react-dom";

export function StressTest({
  name,
  renderItem,
}: {
  name: string;
  renderItem: (i: number, tick: number) => ReactNode;
}) {
  const [count, setCount] = useState(0);
  const [tick, setTick] = useState(0);

  useEffect(() => {
    const report = (metric: "mount" | "update", c: number, ms: number) =>
      window.parent.postMessage(
        { type: "perf", name, metric, count: c, ms: Math.round(ms * 10) / 10 },
        "*",
      );

    const onMsg = (e: MessageEvent) => {
      // 부모의 폰트 선택 적용 (프레임워크 무관 전역 override)
      if (e.data?.type === "setFont") {
        const font: string = e.data.font || "";
        let el = document.getElementById("__demoFont");
        if (!font) {
          if (el) el.remove();
        } else {
          if (!el) {
            el = document.createElement("style");
            el.id = "__demoFont";
            document.head.appendChild(el);
          }
          el.textContent = `*{font-family:${font} !important}`;
        }
        return;
      }
      // 부모의 폰트 크기 선택 → 루트 font-size 변경 (rem 기반 텍스트가 위계 유지하며 스케일)
      if (e.data?.type === "setFontSize") {
        document.documentElement.style.fontSize = e.data.size || "";
        return;
      }
      // 부모의 일괄 닫기 요청 → 생성된 컴포넌트 제거
      if (e.data?.type === "stressClose") {
        setTick(0);
        setCount(0);
        return;
      }
      if (e.data?.type !== "stressRender") return;
      const c = Math.max(1, e.data.count | 0);

      // 깨끗한 측정을 위해 초기화 (이전 결과 제거)
      flushSync(() => {
        setTick(0);
        setCount(0);
      });

      // 1) 마운트: c 개를 동기 렌더+커밋 (스타일 생성 포함, 브라우저 페인트 제외)
      const t0 = performance.now();
      flushSync(() => setCount(c));
      report("mount", c, performance.now() - t0);

      // 2) 리렌더: tick 을 바꿔 마운트된 전체 아이템을 동기 재렌더
      const t1 = performance.now();
      flushSync(() => setTick((t) => t + 1));
      report("update", c, performance.now() - t1);
    };

    window.addEventListener("message", onMsg);
    return () => window.removeEventListener("message", onMsg);
  }, [name]);

  if (count <= 0) return null;

  const items: ReactNode[] = [];
  for (let i = 0; i < count; i++) {
    items.push(<Fragment key={i}>{renderItem(i, tick)}</Fragment>);
  }

  return (
    <div
      style={{
        position: "fixed",
        inset: 0,
        zIndex: 99999,
        background: "rgba(0,0,0,0.55)",
        display: "flex",
        flexDirection: "column",
      }}
    >
      <div
        style={{
          display: "flex",
          alignItems: "center",
          gap: 12,
          padding: "10px 16px",
          background: "#111",
          color: "#fff",
          fontSize: 13,
          fontFamily:
            '-apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif',
        }}
      >
        <span>
          렌더 테스트 · {name} · {count.toLocaleString()}개
        </span>
        <button
          type="button"
          onClick={() => {
            setCount(0);
            setTick(0);
          }}
          style={{
            marginLeft: "auto",
            cursor: "pointer",
            border: "1px solid #444",
            background: "#222",
            color: "#fff",
            borderRadius: 6,
            padding: "4px 10px",
            fontSize: 13,
          }}
        >
          닫기 ✕
        </button>
      </div>
      <div
        style={{
          flex: 1,
          overflow: "auto",
          padding: 12,
          display: "grid",
          gridTemplateColumns: "repeat(auto-fill, minmax(150px, 1fr))",
          // 박스 높이 통일. rem 이라 글자 크기 조절 시 콘텐츠와 함께 스케일돼
          // Chakra 처럼 버튼이 큰 프레임워크도 Go 가 잘리지 않게 여유를 둠.
          gridAutoRows: "4.75rem",
          alignItems: "stretch",
          gap: 8,
          background: "#fff",
        }}
      >
        {items}
      </div>
    </div>
  );
}
