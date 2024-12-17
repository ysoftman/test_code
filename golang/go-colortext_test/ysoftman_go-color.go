/*
# GOPATH 설정되어 있지 않다면 설정
set gopath=D:\ysoftman\Project\ysoftmancode\gopath;

# GOPATH 설정되어 있지 않다면 설정(윈도우 영구 설정)
setx gopath D:\ysoftman\Project\ysoftmancode\gopath; /m

# go get 으로 gopath 에 설치(다운로드)
go get github.com/daviddengcn/go-colortext
*/

// author : ysoftman
// encoding : utf-8
// title : go-colortext 테스트
package main

import (
	"fmt"
	ct "github.com/daviddengcn/go-colortext"
)

func main() {
	fmt.Println("go-colortext test")
	// 리눅스,윈도에서만 모두 동작 확인
	ct.ChangeColor(ct.Red, true, ct.White, false)
	fmt.Println("color text")
	ct.ChangeColor(ct.Green, false, ct.None, false)
	fmt.Println("color text")
	ct.ResetColor()
}
