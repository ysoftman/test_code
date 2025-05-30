# gin web framework test

- build and test

```bash
# install cli tools
go install github.com/rakyll/gotest@latest
go install golang.org/x/tools/gopls@latest
go install honnef.co/go/tools/cmd/staticcheck@latest

# clean
make clean

# test
make test

# test coverage
make coverage

# lint tidy
make lint tidy

# generate swag doc
# http://localhost:8080/swagger/docs/index.html
make swag

# build
make build

# generate doc
make doc

# run
make run

# 유닛테스트 작성시 TDT(https://go.dev/wiki/TableDrivenTests) 방식을 지향
# _test.go 는 https://github.com/cweill/gotests 커맨드를 사용해 생성
# goland, vim, vscode 등 IDE 플러그인 기능으로 생성할 수도 있다.
# vim 사용시 .go 파일 열고 :GoTestsAll 로 생성
# nvim 사용시 .go 파일 열고 :GoAddTest 로 생성

# 특정 함수만 테스트
go test -run ".*TestGINResponse$" ./... -v
```
