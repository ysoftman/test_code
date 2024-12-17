/*
# GOPATH 설정되어 있지 않다면 설정
set gopath=D:\ysoftman\Project\ysoftmancode\gopath;

# GOPATH 설정되어 있지 않다면 설정(윈도우 영구 설정)
setx gopath D:\ysoftman\Project\ysoftmancode\gopath; /m

# go get 으로 gopath 에 설치(다운로드)
go get github.com/mitchellh/colorstring
*/

// author : ysoftman
// encoding : utf-8
// title : colorstring 테스트
package main

import (
	"fmt"
	"github.com/mitchellh/colorstring"
)

func main() {
	fmt.Println("colorstring test")
	// 윈도우에서는 동작하지 않음, 리눅스에서는 동작함
	fmt.Println(colorstring.Color("[blue]ysoftman [red]color string test..."))
}
