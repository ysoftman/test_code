import { useEffect, useState } from "react";

function useLocalStorage(key, initialValue) {
  const [value, setValue] = useState(() => {
    try {
      const stored = window.localStorage.getItem(key);
      return stored != null ? JSON.parse(stored) : initialValue;
    } catch {
      return initialValue;
    }
  });

  useEffect(() => {
    try {
      window.localStorage.setItem(key, JSON.stringify(value));
    } catch {
      // storage 접근 불가 시 무시
    }
  }, [key, value]);

  return [value, setValue];
}

function UseLocalStorageExample() {
  const [name, setName] = useLocalStorage("react-sample-name", "");

  return (
    <section className="card">
      <h2>custom hook (useLocalStorage)</h2>
      <p>입력값이 localStorage 에 저장되어 새로고침해도 유지된다.</p>
      <input type="text" value={name} onChange={(event) => setName(event.target.value)} placeholder="name" />
    </section>
  );
}

export default UseLocalStorageExample;
