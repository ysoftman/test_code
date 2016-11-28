// ysoftman
// println space test

package main

import "fmt"

func main() {
	fruits := [...]string{"apple", "fineapple", "banana", "mango", "lemon"}
	// 배열, 슬라이스 출력시 대괄호와 공백이 들어간다.
	fmt.Println(fruits)
	fmt.Println(fruits[1:2])
	// , 를 사용하면 인자 사이에 공백이 들어간다.
	fmt.Println(fruits[0], fruits[1], fruits[2], fruits[3], fruits[4])
	// + 를 사용하면 인자 사이 공백엇이 출력된다.
	fmt.Println(fruits[0] + fruits[1] + fruits[2] + fruits[3] + fruits[4])
}
