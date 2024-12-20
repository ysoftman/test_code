# gin web framework test

- build and test

```
# clean
make clean

# test
make test

# lint tidy
make lint tidy

# build
make build

# generate swag doc and run
# http://localhost:8080/swagger/docs/index.html
swag init && go run .

# 유닛테스트 작성시 TDT(https://go.dev/wiki/TableDrivenTests) 방식을 지향
# _test.go 는 https://github.com/cweill/gotests 커맨드를 사용해 생성
# goland, vim, vscode 등 IDE 플러그인 기능으로 생성할 수도 있다.
# vim 사용시 .go 파일 열고 :GoTestsAll 로 생성

# 특정 함수만 테스트
go test -run ".*TestGINResponse$" ./... -v

# profiling - heap
curl 'http://localhost:8080/debug/pprof/heap?seconds=10' -o heap.out
go tool pprof -http=:9090 heap.out

# profiling - cpu
curl 'http://localhost:8080/debug/pprof/profile?seconds=10' -o profile.out
go tool pprof -http=:9090 profile.out
```
