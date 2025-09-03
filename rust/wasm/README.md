# wasm test

## 빌드 & 실행

```bash
# wasm runtime 설치
brew install wasmtime

# wasm 빌드
rustup target add wasm32-wasip2
cargo build --target wasm32-wasip2

# 실행
wasmtime target/wasm32-wasip2/debug/wasm.wasm
```
