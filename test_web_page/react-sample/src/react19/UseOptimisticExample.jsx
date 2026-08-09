import { useOptimistic, useRef, useState } from "react";

function UseOptimisticExample() {
  const [messages, setMessages] = useState([]);
  // 낙관적 업데이트: 서버 확인 전에 임시 목록에 바로 반영
  const [optimisticMessages, addOptimistic] = useOptimistic(messages, (current, newMessage) => [
    ...current,
    newMessage,
  ]);
  const inputRef = useRef(null);
  const idRef = useRef(0);

  const handleSubmit = async (event) => {
    event.preventDefault();
    const form = event.target;
    const message = String(new FormData(form).get("message") ?? "").trim();
    if (!message) return;
    form.reset();
    inputRef.current?.focus();

    const id = idRef.current++;
    addOptimistic({ id, text: message, pending: true });

    // 서버 저장 시뮬레이션
    await new Promise((resolve) => setTimeout(resolve, 1500));
    setMessages((prev) => [...prev, { id, text: message, pending: false }]);
  };

  return (
    <section className="card">
      <h2>useOptimistic</h2>
      <p>제출 즉시 낙관적으로 반영되고, 완료 시 최종 상태로 교체된다.</p>
      <form onSubmit={handleSubmit}>
        <input ref={inputRef} type="text" name="message" placeholder="message" />
        <button type="submit">send</button>
      </form>
      <ul>
        {optimisticMessages.map((msg) => (
          <li key={msg.id} className={msg.pending ? "pending" : ""}>
            {msg.text} {msg.pending ? "(전송 중...)" : "(전송 완료)"}
          </li>
        ))}
      </ul>
    </section>
  );
}

export default UseOptimisticExample;
