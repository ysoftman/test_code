# gin web framework test

- build and test

```
# clean
make clean

# test
make test

# build
make build

# generate swag doc and run
# http://localhost:8080/swagger/docs/index.html
swag init && go run .

# 특정 함수만 테스트
go test -run ".*TestGINResponse$" ./... -v

# profiling - heap
curl 'http://localhost:8080/debug/pprof/heap?seconds=10' -o heap.out
go tool pprof -http=:9090 heap.out

# profiling - cpu
curl 'http://localhost:8080/debug/pprof/profile?seconds=10' -o profile.out
go tool pprof -http=:9090 profile.out
```
