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
swag init && go run .

# 특정 함수만 테스트
go test -run ".*TestGINResponse$" ./... -v
```

