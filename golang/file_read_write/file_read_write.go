// author : ysoftman
// encoding : utf-8
// title : file read write 테스트
package main

import (
	"fmt"
	"os"
)

func main() {
	fmt.Println("파일 읽기 쓰기 테스트")

	// 파일 쓰기 방법1
	// 파일 생성(os.FILE , error 리턴)
	fp, err := os.Create("./test1.txt")
	if err != nil {
		fmt.Println("fail to create file")
		os.Exit(1)
	}
	// 파일에 내용 쓰기
	fp.WriteString("os.File.WriteString() 사용해서 쓰기")
	fp.Close()

	// 파일 쓰기 방법2
	// 파일 생성 시 내용 기록하기
	buffer := []byte("os.WriteFile() 사용해서 쓰기")
	os.WriteFile("./test2.txt", buffer, 0644)

	// 파일 읽기 방법1
	// 파일 읽기(os.FILE , error 리턴)
	fp2, err := os.Open("./test1.txt")
	if err != nil {
		fmt.Println("fail to open file")
		os.Exit(1)
	}
	// 파일 내용 읽기
	buffer = make([]byte, 100)

	nBytes, err := fp2.Read(buffer)
	if err != nil {
		fmt.Println("fail to read file")
		os.Exit(1)
	}
	fmt.Println("파일 읽기1 ", nBytes, "bytes, 내용 = ", string(buffer))
	buffer = make([]byte, 100)
	// 파일 포인터 변경
	fmt.Println("파일 읽기1 seek(5,0)")
	fp2.Seek(5, 0)
	nBytes2, err := fp2.Read(buffer)
	if err != nil {
		fmt.Println("fail to read file")
		os.Exit(1)
	}
	fmt.Println("파일 읽기1 ", nBytes2, "bytes, 내용 = ", string(buffer))

	fp2.Close()

	// 파일 읽기 방법2
	// 파일 읽기([]bytes, error 리턴)
	buffer2, err := os.ReadFile("./test2.txt")
	if err != nil {
		fmt.Println("fail to read file")
		os.Exit(1)
	}
	fmt.Println("파일 읽기2 ", len(buffer2), "bytes, 내용 = ", string(buffer2))

	// O_RDONLY  open the file read-only.
	// O_WRONLY  open the file write-only.
	// O_RDWR    open the file read-write.
	// O_APPEND  append data to the file when writing.
	// O_CREATE  create a new file if none exists.
	// O_EXCL    used with O_CREATE, file must not exist
	// O_SYNC    open for synchronous I/O.
	// O_TRUNC   if possible, truncate file when opened.
	fp3, err := os.OpenFile("test3.txt", os.O_RDWR|os.O_APPEND|os.O_CREATE|os.O_SYNC, 0644)
	if err != nil {
		fmt.Println("fail to open file")
	}
	defer fp3.Close()
	buffer3 := []byte("os.OpenFile 로 열기, 없으면 생성된 파일")
	fp3.Write(buffer3)
}
