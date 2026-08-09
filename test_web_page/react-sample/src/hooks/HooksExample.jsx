import UseCallbackExample from "./UseCallbackExample.jsx";
import UseLocalStorageExample from "./UseLocalStorageExample.jsx";
import UseMemoExample from "./UseMemoExample.jsx";
import UseReducerExample from "./UseReducerExample.jsx";
import UseRefExample from "./UseRefExample.jsx";

function HooksExample() {
  return (
    <div className="section-grid">
      <UseRefExample />
      <UseMemoExample />
      <UseCallbackExample />
      <UseReducerExample />
      <UseLocalStorageExample />
    </div>
  );
}

export default HooksExample;
