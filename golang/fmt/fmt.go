// ysoftman
// fmt 패키지 테스트

package main

import "fmt"

func main() {
	fmt.Println("aaaa")
	fmt.Printf("aaa %v\n", "value")
	err := fmt.Errorf("errof test %v", "value")
	fmt.Println(err)
}
