// ysoftman
// hash 테스트

package main

import (
	"crypto/md5"
	"crypto/sha1"
	"encoding/hex"
	"fmt"
)

func main() {
	// md5 해시값 만들기
	md5 := md5.New()
	data := []byte("ysoftman")
	fmt.Printf("%s\n", data)
	// 해시값을 만들 데이터 설정
	md5.Write(data)
	fmt.Printf("md5 sum = %x\n", md5.Sum(nil))
	// string 으로 변환
	fmt.Printf("md5 sum = %s\n", hex.EncodeToString(md5.Sum(nil)))

	// sha1 해시값 만들기
	sha1 := sha1.New()
	data = []byte("ysoftman")
	fmt.Printf("%s\n", data)
	// 해시값을 만들 데이터 설정
	sha1.Write(data)
	// 해시값을 출력
	// 추가 data 를 넣어주면 기존 데이터에 sum 하는 방식으로 해시값을 리턴
	// data 1개인 경우 sum(nil) 사용
	fmt.Printf("sha1 sum = %x\n", sha1.Sum(nil))
	// 데이터를  리셋
	sha1.Reset()
	data = []byte("yoonbyounghoon")
	fmt.Printf("%s\n", data)
	sha1.Write(data)
	fmt.Printf("sha1 sum = %x\n", sha1.Sum(nil))

}
