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
curl -X GET "http://localhost:8080/file"

# 업로드할 파일 생성
dd if=/dev/urandom bs=1000000 count=100 > ysoftman_100MB.tmp
# multipart/form-data 타입으로 파일 업로드
curl -F 'upload=@ysoftman_100MB.tmp;filename=ysoftman_dst' "http://localhost:8080/file?dstfilename=ysoftman_dst.tmp"
```
