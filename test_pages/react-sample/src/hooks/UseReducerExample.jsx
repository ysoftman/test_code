import { useReducer } from "react";

const initialState = { count: 0, step: 1 };

function reducer(state, action) {
  switch (action.type) {
    case "increment":
      return { ...state, count: state.count + state.step };
    case "decrement":
      return { ...state, count: state.count - state.step };
    case "setStep":
      return { ...state, step: Number(action.step) };
    case "reset":
      return initialState;
    default:
      throw new Error(`unknown action: ${action.type}`);
  }
}

function UseReducerExample() {
  const [state, dispatch] = useReducer(reducer, initialState);

  return (
    <section className="card">
      <h2>useReducer</h2>
      <p>count: {state.count}</p>
      <label>
        step
        <input
          type="number"
          min="1"
          value={state.step}
          onChange={(event) => dispatch({ type: "setStep", step: event.target.value })}
        />
      </label>
      <div className="row">
        <button type="button" onClick={() => dispatch({ type: "increment" })}>
          +
        </button>
        <button type="button" onClick={() => dispatch({ type: "decrement" })}>
          -
        </button>
        <button type="button" className="ghost" onClick={() => dispatch({ type: "reset" })}>
          reset
        </button>
      </div>
    </section>
  );
}

export default UseReducerExample;
