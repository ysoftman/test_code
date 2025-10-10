# python test

- lint, formatting

```bash
# uv pip install --system pylint black

# pylint check(lint) -> ruff 로 대체
# pylint --disable="all" --enable="W0611" *.py

# black formatting -> ruff 로 대체
# black *.py

# ruff check and formatting
uv pip install --system ruff
ruff check *.py
ruff format *.py
```
