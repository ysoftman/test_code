# javascript(js) testcode

- runtime 별 debugging...

```bash
# run by node
node hello_world.js


# install deno
curl -fsSL https://deno.land/x/install/install.sh | sh
~/.zshrc 추가
if [ -d "${HOME}/.deno" ]; then
    export DENO_INSTALL="${HOME}/.deno"
    export PATH="$DENO_INSTALL/bin:$PATH"
fi
# run by deno
deno run hello_world.js


# install bun 후 쉘 재시작(요게 가장 빠름)
curl -fsSL https://bun.sh/install | bash
# run by bun(요게 가장 빠름)
bun hello_world.js
bun run hello_world.js
```
