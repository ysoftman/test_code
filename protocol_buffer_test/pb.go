// author : ysoftman
// encoding : utf-8
// title : protocol buffer for golang test
// desc : protocol buffer 는 현재 c++. java, python2 만 현재 공식 지원
// 		  Go 언어용 -> https://github.com/golang/protobuf

/*
# github.com 오픈 소스 사용하기(윈도우 환경 기준)
# GOPATH 에 현재 작업디렉토리 경로 추가
set gopath=%cd%;

# go get 으로 github 다운받기
go get -u github.com/golang/protobuf/proto
go get -u github.com/golang/protobuf/protoc-gen-go

# liteide 사용시 GOPATH 에 현재 작업 디렉토리 경로 추가
View -> Manage GOPATH -> Custom Directories -> Add Directory
*/

/*
protocol buffer 컴파일러 사용하기
1. protocol buffer 컴파일러(protoc.exe) 다운로드
https://developers.google.com/protocol-buffers/docs/downloads

2. protoc.exe 와 같은 위치에 protoc-gen-go.exe 복사
copy -v bin\protoc-gen-go.exe .\

3. go 용 프로토콜 생성
protoc.exe --go_out=. *.proto

4. 생성된 프로토콜 xxx.go 파일 src/xxx/xxx.go 로 이동
*/

package main

import "fmt"
import "log"
import "pb_test"
import "github.com/golang/protobuf/proto"

func main() {
	fmt.Println("golang protocol buffer test")

	// 메시지 설정
	userinfo1 := &pb_test.UserInfo{
		Aaa: proto.String("ysoftman"),
		Bbb: proto.Int32(123),
	}
	log.Printf("userinfo1.Aaa = %v", userinfo1.GetAaa())
	log.Printf("userinfo1.Bbb = %v", userinfo1.GetBbb())

	// 마샬링
	data, err := proto.Marshal(userinfo1)
	if err != nil {
		log.Fatal("proto.Marshal error: ", err)
	}
	userinfo2 := &pb_test.UserInfo{}
	// 언마샬링
	err = proto.Unmarshal(data, userinfo2)
	if err != nil {
		log.Fatal("proto.Unmarshal error: ", err)
	}

	log.Printf("userinfo2.Aaa = %v", userinfo2.GetAaa())
	log.Printf("userinfo2.Bbb = %v", userinfo2.GetBbb())
}
