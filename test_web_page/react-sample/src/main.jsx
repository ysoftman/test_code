import React from "react";
import ReactDOM from "react-dom/client";
import "./index.css";
import App from "./App.jsx";

const root = ReactDOM.createRoot(document.getElementById("root"));
root.render(
  // React.StrictMode 에 감싸져 있다면 2번씩 렌더링 된다.
  // <React.StrictMode>
  <App />,
  // </React.StrictMode>
);
