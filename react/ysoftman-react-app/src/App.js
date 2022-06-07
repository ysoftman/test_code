import logo from './logo.svg';
import './App.css';

function MyHeader(props) {
  return <header>
    <h1><a href='/' onClick={(event) => {
      event.preventDefault() // reload 방지
      props.onChangeMode111()
    }}>aaaa</a></h1>
    <h1><a href='/'>{props.title123}</a></h1>
  </header >
}

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
  const mylist = [
    { id: 1, name: 'lemon', cost: 100 },
    { id: 2, name: 'apple', cost: 200 },
    { id: 3, name: 'orange', cost: 300 },
  ]
  // return default_App()
  return <div >
    <MyHeader title123="my title" onChangeMode111={() => {
      alert("test")
    }}> </MyHeader>
    <MyContents items={mylist} onChangeMode222={(val) => {
      alert("val:" + val)
    }}></MyContents>
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
