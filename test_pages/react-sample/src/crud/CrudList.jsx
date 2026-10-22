import PropTypes from "prop-types";

const itemShape = PropTypes.shape({
  id: PropTypes.number.isRequired,
  name: PropTypes.string.isRequired,
  cost: PropTypes.number.isRequired,
});

CrudList.propTypes = {
  items: PropTypes.arrayOf(itemShape).isRequired,
  onSelect: PropTypes.func.isRequired,
  onShowCreate: PropTypes.func.isRequired,
};

function CrudList({ items, onSelect, onShowCreate }) {
  return (
    <section>
      <div className="row-between">
        <h2>List</h2>
        <button type="button" onClick={onShowCreate}>
          + create
        </button>
      </div>
      {items.length === 0 ? (
        <p className="empty">no items. create one!</p>
      ) : (
        <ul className="item-list">
          {items.map((item) => (
            <li key={item.id}>
              <button type="button" className="item-card" onClick={() => onSelect(item.id)}>
                <span className="item-name">{item.name}</span>
                <span className="item-cost">{item.cost.toLocaleString()}₩</span>
              </button>
            </li>
          ))}
        </ul>
      )}
    </section>
  );
}

export default CrudList;
