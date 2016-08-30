// ysoftman
// string to int test

package main

import (
	"fmt"
	"strconv"
)

func main() {
	// 문자열 -> int 변환
	number := "123456789"
	out, _ := strconv.Atoi(number)
	fmt.Println("number:", out)
	out, _ = strconv.Atoi(string(number[0]))
	fmt.Println("number[0]:", out)
}
