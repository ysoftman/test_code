/*
author : ysoftman
encoding : utf-8
title : protocol buffer for golang test
desc : protocol buffer 는 현재 c++. java, python 만 현재 공식 지원

Go 용 protocol buffer 패키지 설치
GOPATH 설정되어 있어야함
go get 으로 github 다운받기

go get -u github.com/golang/protobuf/proto
go get -u github.com/golang/protobuf/protoc-gen-go

$GOPATH/bin/protoc-gen-go 바이너리가 생성된다.


protocol buffer 컴파일러 설치(osx 기준)

wget https://github.com/google/protobuf/releases/download/v3.2.0/protoc-3.2.0-osx-x86_64.zip

tar zxvf protoc-3.2.0-osx-x86_64.zip

.go 파일 생성
protoc 는 $GOPATH/bin/protoc-gen-go 를 사용한다.
따라서 $GOPATH/bin/ 가 path 로 잡혀 있어야 한다.
또는 $GOPATH/bin/protoc-gen-go 파일을 현재 위치에 복사 한다.


mkdir -p $GOPATH/src/pb_test
./bin/protoc --go_out=$GOPATH/src/pb_test *.proto

pb_test.proto  -> src/pb_test/pb_test.pb.go 파일을 생성한다.

go build
*/

// pb.go - go 로 테스트
package main

import "fmt"
import "log"
import "pb_test" // protocol buffer 로 생성된 pb_test.pb.go 의 패키지
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
