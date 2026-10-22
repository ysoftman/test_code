import PropTypes from "prop-types";

ItemDetail.propTypes = {
  item: PropTypes.shape({
    id: PropTypes.number.isRequired,
    name: PropTypes.string.isRequired,
    cost: PropTypes.number.isRequired,
  }).isRequired,
  onEdit: PropTypes.func.isRequired,
  onDelete: PropTypes.func.isRequired,
  onBack: PropTypes.func.isRequired,
};

function ItemDetail({ item, onEdit, onDelete, onBack }) {
  return (
    <section className="card">
      <h2>{item.name}</h2>
      <p>id: {item.id}</p>
      <p>cost: {item.cost.toLocaleString()}₩</p>
      <div className="row">
        <button type="button" onClick={onEdit}>
          update
        </button>
        <button type="button" className="danger" onClick={onDelete}>
          delete
        </button>
        <button type="button" className="ghost" onClick={onBack}>
          back
        </button>
      </div>
    </section>
  );
}

export default ItemDetail;
