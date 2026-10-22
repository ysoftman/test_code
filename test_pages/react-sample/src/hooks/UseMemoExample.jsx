import { useMemo, useState } from "react";

const fib = (n) => (n <= 1 ? n : fib(n - 1) + fib(n - 2));

function UseMemoExample() {
  const [n, setN] = useState(30);
  const [tick, setTick] = useState(0);

  // n 이 바뀔 때만 재계산되고, 그 외 리렌더링(tick)에서는 캐시된 값 사용
  const result = useMemo(() => fib(n), [n]);

  return (
    <section className="card">
      <h2>useMemo</h2>
      <p>
        fib({n}) = {result}
      </p>
      <input type="range" min="0" max="38" value={n} onChange={(event) => setN(Number(event.target.value))} />
      <button type="button" onClick={() => setTick(tick + 1)}>
        불필요한 리렌더링 (tick {tick})
      </button>
    </section>
  );
}

export default UseMemoExample;
