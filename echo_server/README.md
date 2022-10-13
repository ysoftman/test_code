# echo web framework test

## build and run

```bash
go get -u ./...
go run ./main.go

# 또는 air(reload tool) 사용
air init
air
```

## curl example

```bash
# 파일 조회
curl -X GET "http://localhost:8080/file

```
