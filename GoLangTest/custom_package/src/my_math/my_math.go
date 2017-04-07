// 패키지 설치 방법

// GOPATH 설명 --> http://golang.org/doc/code.html#GOPATH
// 현재 디렉토리를 GOPATH 로 설정한다면
// set GOPATH=%CD% (윈도우 경우)
// export GOPATH=$PWD (리눅스 경우)

// 현재 디렉토리 안에 src/my_math 디렉토리 생성
// mkdir src
// cd src
// mkdir my_math
// cd my_math

// 패키지 빌드 및 설치
// go build my_math.go
// go install my_math

// 설치가 성공했다으면 (윈도우64 기준으로)
// 현재디렉토리/pkg/windows_amd64/my_math.a 가 생성된다.

// author : ysoftman
// encoding : utf-8
// title : my_math 패키지
package my_math

import "fmt"

// 소문자로 시작하는 함수는 외부 패키지에서 접근할 수 없다.
func add(x int, y int) (result int) {
	fmt.Println("add() called.")
	return x + y
}

// 대문자로 시작하는 함수는 외부 패키지에서 접근할 수 있다.
func Add(x int, y int) (result int) {
	fmt.Println("Add() called.")
	return x + y
}
