/*
# GOPATH 설정되어 있지 않다면 설정
set gopath=D:\ysoftman\Project\ysoftmancode\gopath;

# GOPATH 설정되어 있지 않다면 설정(윈도우 영구 설정)
setx gopath D:\ysoftman\Project\ysoftmancode\gopath; /m

# go get 으로 gopath 에 설치(다운로드)
go get github.com/shiena/ansicolor
*/

// author : ysoftman
// encoding : utf-8
// title : ansicolor 테스트
package main

import (
	"fmt"
	"os"
)
import "github.com/shiena/ansicolor"

func main() {
	fmt.Println("ansicolor test")
	// 리눅스,윈도에서만 모두 동작 확인
	w := ansicolor.NewAnsiColorWriter(os.Stdout)
	text := "%sforeground %sbold%s %sbackground%s\n"
	fmt.Fprintf(w, text, "\x1b[31m", "\x1b[1m", "\x1b[21m", "\x1b[41;32m", "\x1b[0m")
	fmt.Fprintf(w, text, "\x1b[32m", "\x1b[1m", "\x1b[21m", "\x1b[42;31m", "\x1b[0m")
	fmt.Fprintf(w, text, "\x1b[33m", "\x1b[1m", "\x1b[21m", "\x1b[43;34m", "\x1b[0m")
	fmt.Fprintf(w, text, "\x1b[34m", "\x1b[1m", "\x1b[21m", "\x1b[44;33m", "\x1b[0m")
	fmt.Fprintf(w, text, "\x1b[35m", "\x1b[1m", "\x1b[21m", "\x1b[45;36m", "\x1b[0m")
	fmt.Fprintf(w, text, "\x1b[36m", "\x1b[1m", "\x1b[21m", "\x1b[46;35m", "\x1b[0m")
	fmt.Fprintf(w, text, "\x1b[37m", "\x1b[1m", "\x1b[21m", "\x1b[47;30m", "\x1b[0m")
}
