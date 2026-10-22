import { useMemo, useState } from "react";
import CrudHeader from "./CrudHeader.jsx";
import CrudList from "./CrudList.jsx";
import ItemDetail from "./ItemDetail.jsx";
import ItemForm from "./ItemForm.jsx";

const INITIAL_ITEMS = [
  { id: 1, name: "lemon", cost: 100 },
  { id: 2, name: "apple", cost: 200 },
  { id: 3, name: "orange", cost: 300 },
];

function CrudApp() {
  const [items, setItems] = useState(INITIAL_ITEMS);
  // list | read | create | update
  const [mode, setMode] = useState("list");
  const [selectedId, setSelectedId] = useState(null);

  const selectedItem = useMemo(() => items.find((item) => item.id === selectedId) ?? null, [items, selectedId]);

  const nextId = items.length > 0 ? Math.max(...items.map((item) => item.id)) + 1 : 1;

  const handleCreate = (name, cost) => {
    setItems([...items, { id: nextId, name, cost }]);
    setMode("list");
  };

  const handleUpdate = (name, cost) => {
    setItems(items.map((item) => (item.id === selectedId ? { ...item, name, cost } : item)));
    setMode("read");
  };

  const handleDelete = () => {
    if (!window.confirm(`"${selectedItem?.name}" 항목을 삭제할까요?`)) return;
    setItems(items.filter((item) => item.id !== selectedId));
    setSelectedId(null);
    setMode("list");
  };

  const handleHome = () => {
    setSelectedId(null);
    setMode("list");
  };

  let content = null;
  if (mode === "create") {
    content = <ItemForm mode="create" onSubmit={handleCreate} onCancel={handleHome} />;
  } else if (mode === "update") {
    content = (
      <ItemForm
        mode="update"
        initialName={selectedItem?.name}
        initialCost={selectedItem?.cost}
        onSubmit={handleUpdate}
        onCancel={() => setMode("read")}
      />
    );
  } else if (mode === "read" && selectedItem) {
    content = (
      <ItemDetail item={selectedItem} onEdit={() => setMode("update")} onDelete={handleDelete} onBack={handleHome} />
    );
  } else {
    content = <CrudList items={items} onSelect={setSelectedId} onShowCreate={() => setMode("create")} />;
  }

  return (
    <div className="crud-app">
      <CrudHeader title="fruits & cost" count={items.length} onHome={handleHome} />
      {content}
    </div>
  );
}

export default CrudApp;
