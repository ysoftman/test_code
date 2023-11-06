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
dd if=/dev/urandom bs=1000000 count=100 > ysoftman_100MB1.tmp
dd if=/dev/urandom bs=1000000 count=100 > ysoftman_100MB2.tmp
dd if=/dev/urandom bs=1000000 count=100 > ysoftman_100MB3.tmp
# multipart/form-data 타입으로 파일 업로드
# dst 파일이름을 지정할 경우
# curl \
# -F 'upload=@ysoftman_100MB1.tmp;filename=ysoftman_dst1.tmp' \
# -F 'upload=@ysoftman_100MB2.tmp;filename=ysoftman_dst2.tmp' \
# -F 'upload=@ysoftman_100MB3.tmp;filename=ysoftman_dst3.tmp' \
# "http://localhost:8080/file"
curl \
-F 'upload=@ysoftman_100MB1.tmp' \
-F 'upload=@ysoftman_100MB2.tmp' \
-F 'upload=@ysoftman_100MB3.tmp' \
"http://localhost:8080/file"

# 큰 파일 올려보기
dd if=/dev/urandom bs=1000000 count=10000 > ysoftman_10GB.tmp
curl -F 'upload=@ysoftman_10GB.tmp' "http://localhost:8080/file"

# 테스트 끝나고 파일 지우자~
rm -fv *.tmp
```
