# go1.11 에 추가된 WebAssembly(abbreviated wasm) 테스트

- 참고 https://github.com/golang/go/wiki/WebAssembly

## 테스트

```bash
# wasm 로 동작할 코드 빌드
GOARCH=wasm GOOS=js go build -o test.wasm wasm.go

# test.wasm 실행을 위한 html, js 파일 복사
cp $(go env GOROOT)/misc/wasm/wasm_exec.{html,js} .

# test.wasm 실행을 위한 웹서버 실행
go run wasm_server.go

# test.wasm 실행
http://localhost:8080/wasm_exec.html  => run 클릭하면 브라우저 디버그 콘솔창에 메시지 출력~
```