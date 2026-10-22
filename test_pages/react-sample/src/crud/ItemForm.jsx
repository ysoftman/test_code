import { useState } from "react";
import PropTypes from "prop-types";

ItemForm.propTypes = {
  mode: PropTypes.oneOf(["create", "update"]).isRequired,
  initialName: PropTypes.string,
  initialCost: PropTypes.oneOfType([PropTypes.string, PropTypes.number]),
  onSubmit: PropTypes.func.isRequired,
  onCancel: PropTypes.func.isRequired,
};

function ItemForm({ mode, initialName = "", initialCost = "", onSubmit, onCancel }) {
  const [name, setName] = useState(initialName);
  const [cost, setCost] = useState(initialCost);

  const handleSubmit = (event) => {
    event.preventDefault();
    const trimmedName = name.trim();
    const parsedCost = Number(cost);
    if (!trimmedName || Number.isNaN(parsedCost) || parsedCost < 0) {
      window.alert("name 과 0 이상의 cost 가 필요합니다.");
      return;
    }
    onSubmit(trimmedName, parsedCost);
  };

  return (
    <form className="card" onSubmit={handleSubmit}>
      <h2>{mode === "create" ? "Create" : "Update"}</h2>
      <label>
        name
        <input type="text" value={name} onChange={(event) => setName(event.target.value)} placeholder="title" />
      </label>
      <label>
        cost
        <input
          type="number"
          min="0"
          value={cost}
          onChange={(event) => setCost(event.target.value)}
          placeholder="cost"
        />
      </label>
      <div className="row">
        <button type="submit">{mode === "create" ? "create" : "update"}</button>
        <button type="button" className="ghost" onClick={onCancel}>
          cancel
        </button>
      </div>
    </form>
  );
}

export default ItemForm;
