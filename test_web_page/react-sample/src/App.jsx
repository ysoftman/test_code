import { useState } from "react";
import "./App.css";
import CrudApp from "./crud/CrudApp.jsx";
import HooksExample from "./hooks/HooksExample.jsx";
import React19Example from "./react19/React19Example.jsx";

const TABS = [
  { id: "crud", label: "CRUD", component: CrudApp },
  { id: "hooks", label: "Hooks", component: HooksExample },
  { id: "react19", label: "React 19", component: React19Example },
];

function App() {
  const [activeTab, setActiveTab] = useState(TABS[0].id);
  const ActiveComponent = TABS.find((tab) => tab.id === activeTab).component;

  return (
    <div className="app">
      <header className="app-header">
        <h1>React 19 + Vite sample</h1>
        <nav className="tabs">
          {TABS.map((tab) => (
            <button
              key={tab.id}
              type="button"
              className={activeTab === tab.id ? "tab active" : "tab"}
              onClick={() => setActiveTab(tab.id)}
            >
              {tab.label}
            </button>
          ))}
        </nav>
      </header>
      <main className="app-main">
        <ActiveComponent />
      </main>
    </div>
  );
}

export default App;
