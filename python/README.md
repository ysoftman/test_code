# python test

- lint, formatting

```bash
# install packages
uv pip install --system pylint black ruff

# pylint check(lint)
pylint --disable="all" --enable="W0611" *.py

# black formatting
black *.py

# ruff check and formatting
ruff check *.py
ruff format *.py
```
