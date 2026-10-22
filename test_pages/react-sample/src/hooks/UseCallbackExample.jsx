import { memo, useCallback, useRef, useState } from "react";

const Child = memo(function Child({ label, onClick }) {
  const renders = useRef(0);
  renders.current += 1;
  return (
    <button type="button" onClick={onClick}>
      {label} (renders: {renders.current})
    </button>
  );
});

function UseCallbackExample() {
  const [count, setCount] = useState(0);
  const [other, setOther] = useState(0);

  // useCallback 으로 함수 참조를 고정 → memo 자식이 다른 상태 변경으로 재렌더되지 않음
  const stableCallback = useCallback(() => setCount((value) => value + 1), []);

  // 렌더마다 새 함수 → memo 자식도 함께 재렌더됨
  const unstableCallback = () => setCount((value) => value + 1);

  return (
    <section className="card">
      <h2>useCallback + memo</h2>
      <p>
        count: {count} / other: {other}
      </p>
      <div className="row">
        <Child label="stable callback" onClick={stableCallback} />
        <Child label="inline callback" onClick={unstableCallback} />
      </div>
      <button type="button" onClick={() => setOther(other + 1)}>
        other +1 (부모 리렌더 유발)
      </button>
    </section>
  );
}

export default UseCallbackExample;
