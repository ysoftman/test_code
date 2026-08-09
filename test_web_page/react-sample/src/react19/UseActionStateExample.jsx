import { useActionState } from "react";

async function saveName(_prevState, formData) {
  // 서버 요청 시뮬레이션
  await new Promise((resolve) => setTimeout(resolve, 1000));
  const name = String(formData.get("name") ?? "").trim();
  if (!name) {
    return { error: "name is required", value: "" };
  }
  return { message: `saved: ${name}`, value: name };
}

function UseActionStateExample() {
  const [state, formAction, isPending] = useActionState(saveName, { message: null, error: null, value: "" });

  return (
    <section className="card">
      <h2>useActionState (form action)</h2>
      <p>form action 으로 비동기 제출, isPending 으로 진행 상태를 받는다.</p>
      <form action={formAction}>
        <input type="text" name="name" defaultValue={state.value} placeholder="name" />
        <button type="submit" disabled={isPending}>
          {isPending ? "saving..." : "save"}
        </button>
      </form>
      {state.error && <p className="error">{state.error}</p>}
      {state.message && <p className="ok">{state.message}</p>}
    </section>
  );
}

export default UseActionStateExample;
