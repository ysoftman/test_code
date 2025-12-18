import { useEffect, useState } from "react";
import PropTypes from "prop-types";
import "./App.css";
import MyComp1 from "./mycomp1.jsx";

Create.propTypes = {
  onCreate: PropTypes.func.isRequired,
};

function Create({ onCreate }) {
  const handleSubmit = (event) => {
    event.preventDefault();
    const name = event.target.name.value;
    const cost = event.target.cost.value;
    onCreate(name, cost);
  };

  return (
    <article>
      <h2>Create</h2>
      <form onSubmit={handleSubmit}>
        <p>
          <input type="text" name="name" placeholder="title" />
        </p>
        <p>
          <textarea name="cost" placeholder="cost" />
        </p>
        <p>
          <input type="submit" value="Create" />
        </p>
      </form>
    </article>
  );
}

Update.propTypes = {
  name: PropTypes.string.isRequired,
  cost: PropTypes.oneOfType([PropTypes.string, PropTypes.number]).isRequired,
  onUpdate: PropTypes.func.isRequired,
};

function Update({ name: initialName, cost: initialCost, onUpdate }) {
  const [name, setName] = useState(initialName);
  const [cost, setCost] = useState(initialCost);

  const handleSubmit = (event) => {
    event.preventDefault();
    onUpdate(name, cost);
  };

  return (
    <article>
      <h2>Update</h2>
      <form onSubmit={handleSubmit}>
        <p>
          <input
            type="text"
            name="name"
            placeholder="name"
            value={name}
            onChange={(event) => setName(event.target.value)}
          />
        </p>
        <p>
          <textarea name="cost" placeholder="cost" value={cost} onChange={(event) => setCost(event.target.value)} />
        </p>
        <p>
          <input type="submit" value="Update" />
        </p>
      </form>
    </article>
  );
}
MyHeader.propTypes = {
  title: PropTypes.string.isRequired,
  onChangeMode: PropTypes.func.isRequired,
};

function MyHeader({ title, onChangeMode }) {
  const handleClick = (event) => {
    event.preventDefault();
    onChangeMode();
  };

  return (
    <header>
      <h1>
        <a href="/" onClick={handleClick}>
          aaaa
        </a>
      </h1>
      <h1>
        <a href="/">{title}</a>
      </h1>
    </header>
  );
}

MyContents.propTypes = {
  items: PropTypes.arrayOf(
    PropTypes.shape({
      id: PropTypes.number.isRequired,
      name: PropTypes.string.isRequired,
      cost: PropTypes.oneOfType([PropTypes.string, PropTypes.number]).isRequired,
    }),
  ).isRequired,
  onChangeMode: PropTypes.func.isRequired,
};

function MyContents({ items, onChangeMode }) {
  const handleClick = (event) => {
    event.preventDefault();
    onChangeMode(event.target.id, event.target.name);
  };

  return (
    <article>
      <h2>contents</h2>
      bla bla~
      <ol>
        {items.map((item) => (
          <li key={item.id}>
            <a id={item.id} name={item.name} href="/" onClick={handleClick}>
              {item.name} - {item.cost}
            </a>
          </li>
        ))}
      </ol>
    </article>
  );
}
App.propTypes = {
  // Add prop types if App receives props in the future
};

function App() {
  const [mode, setMode] = useState("");
  const [clickId, setClickId] = useState(null);
  const [mylist, setMylist] = useState([
    { id: 1, name: "lemon", cost: 100 },
    { id: 2, name: "apple", cost: 200 },
    { id: 3, name: "orange", cost: 300 },
  ]);

  useEffect(() => {
    console.log(`useEffect: clickId=${clickId}, mode=${mode}`);
  }, [clickId, mode]);

  const [nextId, setNextId] = useState(4);

  const handleCreate = (name, cost) => {
    const newItem = { id: nextId, name, cost };
    setMylist([...mylist, newItem]);
    setNextId(nextId + 1);
  };

  const handleUpdate = (name, cost) => {
    const updatedItem = { id: Number(clickId), name, cost };
    setMylist(mylist.map((item) => (item.id === Number(clickId) ? updatedItem : item)));
    setMode("read");
  };

  const handleDelete = () => {
    setMylist(mylist.filter((item) => item.id !== Number(clickId)));
    setMode("read");
  };

  const handleContentClick = (id, name) => {
    setMode("read");
    setClickId(id);
  };

  const handleHeaderClick = () => {
    alert("test");
  };

  let updateDeleteComponent = null;
  let message = null;

  if (mode === "read") {
    message = `click_id: ${clickId}`;
    updateDeleteComponent = (
      <>
        <li>
          <a
            href={`/${clickId}`}
            onClick={(event) => {
              event.preventDefault();
              setMode("update");
            }}
          >
            update
          </a>
        </li>
        <li>
          <input type="button" value="delete" onClick={handleDelete} />
        </li>
      </>
    );
  } else if (mode === "create") {
    message = <Create onCreate={handleCreate} />;
  } else if (mode === "update") {
    const item = mylist.find((item) => item.id === Number(clickId));
    if (item) {
      message = <Update name={item.name} cost={item.cost} onUpdate={handleUpdate} />;
    }
  }

  return (
    <div>
      <MyHeader title="my title" onChangeMode={handleHeaderClick} />
      <MyContents items={mylist} onChangeMode={handleContentClick} />
      {message}
      {message && <MyComp1 param1={message} param2="ok" />}
      <br />
      <ul>
        <li>
          <a
            href="/"
            onClick={(event) => {
              event.preventDefault();
              setMode("create");
            }}
          >
            create
          </a>
        </li>
        {updateDeleteComponent}
      </ul>
    </div>
  );
}

export default App;
