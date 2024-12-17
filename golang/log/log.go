// author : ysoftman
// encoding : utf-8
// title : log 테스트
package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"log"
	"os"
)

func main() {
	// fmt 를 이용한 출력
	fmt.Println("Println()")
	fmt.Fprintln(os.Stdout, "Fprintln()")

	// log 를 이용한 출력
	// var std = New(os.Stderr, "", LstdFlags)
	// stderr 만 확인해보자
	// go run log.go > /dev/null
	log.Println("로그 디폴트는 stderr 로 출력된다.")
	// 표준 출력 로거 생성
	stdoutWriter := os.Stdout
	mylogger1 := log.New(stdoutWriter, "[mylogger1]", log.Lshortfile|log.Ldate|log.Ltime)
	mylogger1.Println("표준출력 로그 테스트1", 123, "기록")
	mylogger1.Println("표준출력 로그 테스트2", 123, "기록")
	mylogger1.Println("표준출력 로그 테스트3", 123, "기록")

	// 버퍼 로거 생성
	var bufferWriter bytes.Buffer
	mylogger2 := log.New(&bufferWriter, "[mylogger2]", log.Ldate|log.Ltime|log.Lshortfile)
	// 버퍼에 로그 출력
	mylogger2.Printf("버퍼 로그 테스트1 %d", 1234)
	// 버퍼내용 화면에 출력
	fmt.Printf("%s", bufferWriter.String())

	// 버퍼 리셋
	bufferWriter.Reset()

	// 버퍼에 로그 출력
	mylogger2.Printf("버퍼 로그 테스트2 %d", 1234)
	// 버퍼내용 화면에 출력
	fmt.Printf("%s", bufferWriter.Bytes())

	// 파일에 로그 출력하기
	// 대상 파일 열기, 없으면 생성
	f, err := os.OpenFile("test.log", os.O_CREATE, 0o666)
	if err != nil {
		log.Println(err.Error())
	}
	defer f.Close()

	// 대상 파일로 로그 출력 설정
	log.SetOutput(f)
	log.Println("파일에 로그기록.")

	// Fatal 을 사용하면 os.Exit(1) 로 종료 된다
	// mylogger2.Fatalln("aaa")
	// mylogger2.Fatal("aaa")/
	// Panic 발생 exit status 2
	// mylogger2.Panic("---aaa---")

	// stdout 로 로그 출력
	log.SetOutput(os.Stdout)
	log.Println("aaa")

	// stderr 로 로그 출력
	log.SetOutput(os.Stderr)
	log.Println("bbb")

	// 로그 출력 않하기
	log.SetOutput(ioutil.Discard)
	log.Println("xxx")
}
