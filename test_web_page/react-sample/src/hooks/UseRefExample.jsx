import { useRef, useState } from "react";

function UseRefExample() {
  const [count, setCount] = useState(0);
  const countRef = useRef(0);
  const inputRef = useRef(null);

  const incrementRef = () => {
    countRef.current += 1;
    // ref.current 변경은 리렌더링을 유발하지 않는다. 콘솔로 확인.
    console.log(`ref count: ${countRef.current}`);
  };

  return (
    <section className="card">
      <h2>useRef</h2>
      <p>state: {count} (setState 로 변경 시 리렌더링)</p>
      <p>ref: {countRef.current} (ref 변경은 리렌더링 없음, 콘솔 확인)</p>
      <div className="row">
        <button type="button" onClick={() => setCount(count + 1)}>
          state +1
        </button>
        <button type="button" onClick={incrementRef}>
          ref +1
        </button>
      </div>
      <div className="row">
        <input ref={inputRef} placeholder="focus me" />
        <button type="button" onClick={() => inputRef.current?.focus()}>
          focus input
        </button>
      </div>
    </section>
  );
}

export default UseRefExample;
