import logo from './logo.svg';
import React, { useState } from 'react';
import './App.css';


// Create Component, (컴포넌트는 대문자로 시작해야 한다.)
function Create(props) {
  return <article>
    <h2>Create</h2>
    <form onSubmit={event => {
      event.preventDefault() // reload 방지
      const name = event.target.name.value // target(form)의 태그(name)의 값(value)
      const cost = event.target.cost.value // target(form)의 태그(name)의 값(value)
      props.onCreate(name, cost)
    }}>
      <p><input type="text" name="name" placeholder='title'></input></p>
      <p><textarea name="cost" placeholder='body'></textarea></p>
      <p><input type="submit" value="Create"></input></p>
    </form>
  </article>
}

// MyHeader Component, (컴포넌트는 대문자로 시작해야 한다.)
function MYHeader(props) {
  return <header>
    <h1><a href='/' onClick={(event) => {
      event.preventDefault() // reload 방지
      props.onChangeMode111()
    }}>aaaa</a></h1>
    <h1><a href='/'>{props.title123}</a></h1>
  </header >
}

// MyContents Component, (컴포넌트는 대문자로 시작해야 한다.)
function MyContents(props) {
  const mylist = []
  for (let i = 0; i < props.items.length; i++) {
    let l = props.items[i]
    // console.log("l:", l)
    mylist.push(<li key={l.id}>
      <a name={l.name} href="/" onClick={(event) => {
        event.preventDefault()
        props.onChangeMode222(event.target.name) // target=>여기선 a 태그
      }}>{l.name} - {l.cost}</a>
    </li>)
  }
  return <article>
    <h2>contents</h2>
    bla bla~
    <ol>
      {mylist}
    </ol>
  </article>
}

function App() {
  // 초기값 lemon 을 갖는 state 생성
  // state 는 2길이의 0번째는 값, 1번째는 설정함수를 가진다.
  const [mode, setMode] = useState("lemon")
  const [click_name, setId] = useState(null)
  const [mylist, setMylist] = useState([
    { id: 1, name: 'lemon', cost: 100 },
    { id: 2, name: 'apple', cost: 200 },
    { id: 3, name: 'orange', cost: 300 },
  ])
  const [nextId, setNextId] = useState(4);

  let message = null
  if (mode === "lemon") {
    message = "mode:lemon Yellow, click_id:" + click_name
  } else if (mode === "apple") {
    message = "mode:apple, RED, click_id:" + click_name
  } else if (mode === "orange") {
    message = "mode:orange, Orange, click_id:" + click_name
  } else if (mode === "create") {
    message = <Create onCreate={(_name, _cost) => {
      // 신규 아이템
      const newItem = { id: nextId, name: _name, cost: _cost }
      // 기존 mylist 복제
      const newList = [...mylist]
      // 신규 아이템 추가
      newList.push(newItem)
      // mylist state 변경
      setMylist(newList)
      setNextId(nextId + 1)
    }}></Create> // create 컴포넌트 사용
  }

  // return default_App()
  return <div >
    <MYHeader title123="my title" onChangeMode111={() => {
      alert("test")
    }}> </MYHeader>
    <MyContents items={mylist} onChangeMode222={(val) => {
      alert("val:" + val)
      setMode(val) // App() 컴포넌트를 다시 실행한다.
      setId(val)
    }}></MyContents>
    {message}
    <br></br>
    <a href="/" onClick={(event) => {
      event.preventDefault()
      setMode("create")
    }}>create</a>
  </div>

}

function default_App(param) {
  return <div className="App">
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
}

export default App;
