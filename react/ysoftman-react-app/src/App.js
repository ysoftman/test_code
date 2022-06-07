import logo from './logo.svg';
import './App.css';

function MyHeader(props) {
  return <header>
    <h1><a href='/'>aaaa</a></h1>
    <h1><a href='/'>{props.title123}</a></h1>
  </header >
}

function Contents(props) {
  const mylist = []
  for (let i = 0; i < props.items.length; i++) {
    let l = props.items[i]
    // console.log("l:", l)
    mylist.push(<li key={l.id}>{l.name} - {l.cost}</li>)
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

  return (
    // <div className="App">
    //   <header className="App-header">
    //     <img src={logo} className="App-logo" alt="logo" />
    //     <p>
    //       Edit <code>src/App.js</code> and save to reload.
    //     </p>
    //     <a
    //       className="App-link"
    //       href="https://reactjs.org"
    //       target="_blank"
    //       rel="noopener noreferrer"
    //     >
    //       Learn React
    //     </a>
    //   </header>
    // </div>
    <div>
      <MyHeader title123="my title"> </MyHeader>
      <Contents items={mylist}></Contents>
    </div>
  );
}

export default App;
