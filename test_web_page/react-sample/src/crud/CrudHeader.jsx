import PropTypes from "prop-types";

CrudHeader.propTypes = {
  title: PropTypes.string.isRequired,
  count: PropTypes.number.isRequired,
  onHome: PropTypes.func.isRequired,
};

function CrudHeader({ title, count, onHome }) {
  return (
    <header className="crud-header">
      <button type="button" className="link" onClick={onHome}>
        {title}
      </button>
      <span className="badge">{count} items</span>
    </header>
  );
}

export default CrudHeader;
