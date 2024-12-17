// ysoftman
// strlen 구현해보기
package main

import "fmt"

func main() {
	str := "my nickname is ysoftman"

	fmt.Printf("len(%s)=%d\n", str, len(str))
	fmt.Printf("strlen(%s)=%d\n", str, strlen(str))
}

func strlen(str string) int {
	// fmt.Println("strlen()")
	cnt := 0
	// for i := range str {
	for i := 0; i < len(str); i++ {
		// fmt.Println(str[i])
		cnt++
	}

	return cnt
}
