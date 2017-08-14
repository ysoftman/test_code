// author : ysoftman
// encoding : utf-8
// title : color 테스트
// go get 으로 gopath 에 설치(다운로드)
// go get github.com/fatih/color

package main

import (
	"fmt"
	"strconv"

	"github.com/fatih/color"
)

func main() {
	fmt.Println("color test")

	for i := 0; i < 12; i++ {
		fmt.Println(getNextColorString(i, strconv.Itoa(i)+" ysoftman"))
	}
}

func getNextColorString(i int, str string) string {
	n := i % 6
	switch n {
	case 0:
		red := color.New(color.FgRed).SprintFunc()
		return red(str)
	case 1:
		green := color.New(color.FgGreen).SprintFunc()
		return green(str)
	case 2:
		yellow := color.New(color.FgYellow).SprintFunc()
		return yellow(str)
	case 3:
		blue := color.New(color.FgBlue).SprintFunc()
		return blue(str)
	case 4:
		magenta := color.New(color.FgMagenta).SprintFunc()
		return magenta(str)
	case 5:
		cyan := color.New(color.FgCyan).SprintFunc()
		return cyan(str)
	default:
		white := color.New(color.FgWhite).SprintFunc()
		return white(str)
	}

}
