# gin web framework test

- build

```
# generate swag doc and run
swagg init && go run .
```

- test

```
# 전체 테스트
go test ./... -v

# 특정 함수만 테스트
go test -run ".*TestGINResponse$" ./... -v
```
