import logo from "./logo.svg";
import React, { useEffect, useState } from "react";
import "./App.css";
import MyComp1 from "./mycomp1";

// Create Component, (컴포넌트는 대문자로 시작해야 한다.)
function Create(props) {
  return (
    <article>
      <h2>Create</h2>
      <form
        onSubmit={(event) => {
          event.preventDefault(); // reload 방지
          const name = event.target.name.value; // target(form)의 태그(name)의 값(value)
          const cost = event.target.cost.value; // target(form)의 태그(name)의 값(value)
          props.onCreate(name, cost);
        }}
      >
        <p>
          <input type="text" name="name" placeholder="title"></input>
        </p>
        <p>
          <textarea name="cost" placeholder="cost"></textarea>
        </p>
        <p>
          <input type="submit" value="Create"></input>
        </p>
      </form>
    </article>
  );
}

// Update Component, (컴포넌트는 대문자로 시작해야 한다.)
function Update(props) {
  const [name, setName] = useState(props.name);
  const [cost, setCost] = useState(props.cost);
  return (
    <article>
      <h2>Update</h2>
      <form
        onSubmit={(event) => {
          event.preventDefault(); // reload 방지
          const name = event.target.name.value; // target(form)의 태그(name)의 값(value)
          const cost = event.target.cost.value; // target(form)의 태그(name)의 값(value)
          props.onUpdate(name, cost);
        }}
      >
        <p>
          <input
            type="text"
            name="name"
            placeholder="name"
            value={name}
            onChange={(event) => {
              // console.log("event:", event.target.value)
              setName(event.target.value);
            }}
          ></input>
        </p>
        <p>
          <textarea
            name="cost"
            placeholder="cost"
            value={cost}
            onChange={(event) => {
              // console.log("event:", event.target.value)
              setCost(event.target.value);
            }}
          ></textarea>
        </p>

        <p>
          <input type="submit" value="Update"></input>
        </p>
      </form>
    </article>
  );
}
// MyHeader Component, (컴포넌트는 대문자로 시작해야 한다.)
function MYHeader(props) {
  return (
    <header>
      <h1>
        <a
          href="/"
          onClick={(event) => {
            event.preventDefault(); // reload 방지
            props.onChangeMode111();
          }}
        >
          aaaa
        </a>
      </h1>
      <h1>
        <a href="/">{props.title123}</a>
      </h1>
    </header>
  );
}

// MyContents Component, (컴포넌트는 대문자로 시작해야 한다.)
function MyContents(props) {
  const mylist = [];
  for (let i = 0; i < props.items.length; i++) {
    let l = props.items[i];
    // console.log("l:", l)
    mylist.push(
      <li key={l.id}>
        <a
          id={l.id}
          name={l.name}
          href="/"
          onClick={(event) => {
            event.preventDefault();
            props.onChangeMode222(event.target.id, event.target.name); // target=>여기선 a 태그
          }}
        >
          {l.name} - {l.cost}
        </a>
      </li>,
    );
  }
  return (
    <article>
      <h2>contents</h2>
      bla bla~
      <ol>{mylist}</ol>
    </article>
  );
}
function App() {
  // react hook 주의 사항!!!
  // react hook (사용자 커스텀 훅도) 함수이름은 use로 시작한다.
  // hook 은 현재 함수 레벨에서만 호출해야한다.
  // func aa() { const [a, seta] = useState() }
  // if (true) { const [a, seta] = useState() }
  // for (let i=0;i<10;i++) { const [a, seta] = useState() }
  // 와 같이 호출 할 수 없도록되어 되어 있다.

  // 초기값 lemon 을 갖는 state 생성
  // state 는 2길이의 0번째는 값, 1번째는 설정함수를 가진다.
  const [mode, setMode] = useState("");
  const [click_id, setClickID] = useState(null);
  const [mylist, setMylist] = useState([
    { id: 1, name: "lemon", cost: 100 },
    { id: 2, name: "apple", cost: 200 },
    { id: 3, name: "orange", cost: 300 },
  ]);

  // 컴포넌트가 마운트될때와 렌더딩될때마다 호출
  // useEffect(() => {
  //   console.log("useEffect 마운트될때와 렌더딩될때마다 호출")
  // })
  // 컴포넌트가 마운트될때와
  // useEffect(() => {
  //   console.log("useEffect 마운트될때만 호출됨")
  // }, [])
  // 컴포넌트가 마운트될때와 [] 의 값이 변경됐을때만 호출
  useEffect(() => {
    console.log(
      "useEffect 컴포넌트가 마운트될때와 [click_id, mode] = %s %s의 값이 변경됐을때만 호출",
      click_id,
      mode,
    );
  }, [click_id, mode]);

  const [nextId, setNextId] = useState(4);
  let updateDeleteComponent = null;
  let message = null;
  if (mode === "read") {
    message = "click_id:" + click_id;
    // <> 빈태그를 사용하면 그룹핑 할 수 있다.
    updateDeleteComponent = (
      <>
        <li>
          <a
            href={"/" + click_id}
            onClick={(event) => {
              event.preventDefault();
              setMode("update");
            }}
          >
            update
          </a>
        </li>
        <li>
          <input
            type="button"
            value="delete"
            onClick={() => {
              // 삭제할 아이템 빼고 새로우 리스트 구성
              const newMylist = [];
              console.log("click_id:", click_id);
              for (let i = 0; i < mylist.length; i++) {
                if (mylist[i].id !== Number(click_id)) {
                  newMylist.push(mylist[i]);
                }
              }
              console.log("--->", newMylist);
              setMylist(newMylist);
              setMode("read");
            }}
          ></input>
        </li>
      </>
    );
  } else if (mode === "create") {
    message = (
      <Create
        onCreate={(_name, _cost) => {
          // 신규 아이템
          const newItem = { id: nextId, name: _name, cost: _cost };
          // 기존 mylist 복제
          const newList = [...mylist];
          // 신규 아이템 추가
          newList.push(newItem);
          // mylist state 변경
          setMylist(newList);

          // ID는 편의상 계속 증가하는 방식으로...
          setNextId(nextId + 1);
        }}
      ></Create>
    ); // create 컴포넌트 사용
  } else if (mode === "update") {
    let _name,
      _cost = null;
    for (let i = 0; i < mylist.length; i++) {
      if (mylist[i].id === Number(click_id)) {
        _name = mylist[i].name;
        _cost = mylist[i].cost;
      }
    }
    message = (
      <Update
        name={_name}
        cost={_cost}
        onUpdate={(_name, _cost) => {
          const updatedItem = {
            id: Number(click_id),
            name: _name,
            cost: _cost,
          };
          // 기존 mylist 복제
          const newList = [...mylist];
          // 기존 아이템을 업데이트된 아이템으로 변경
          for (let i = 0; i < mylist.length; i++) {
            if (mylist[i].id === Number(click_id)) {
              newList[i] = updatedItem;
              break;
            }
          }
          setMylist(newList);
          setMode("read");
        }}
      ></Update>
    ); // update 컴포넌트 사용
  }

  // return default_App()
  return (
    <div>
      <MYHeader
        title123="my title"
        onChangeMode111={() => {
          alert("test");
        }}
      >
        {" "}
      </MYHeader>
      <MyContents
        items={mylist}
        onChangeMode222={(id, name) => {
          // console.log("id:", id, "name:", name)
          setMode("read"); // App() 컴포넌트를 다시 실행한다.
          setClickID(id); // click_id 변경
        }}
      ></MyContents>
      {message}
      {/* message 가 있으면 없으면 MyComp1 보이기 */}
      {/* {message ? <MyComp1 param1={message} param2="ok" /> : null} */}
      {message && <MyComp1 param1={message} param2="ok" />}
      <br></br>
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

function default_App(param) {
  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Edit <code>src/App.js</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
        </a>
      </header>
    </div>
  );
}

export default App;
