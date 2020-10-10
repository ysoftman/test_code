package main

import "fmt"

// ysoftman
// goto 테스트
func main() {
	// 선언된 변수를 사용하지 않고 goto 로 점프하면 에러
	// 이후 go 버전에서는 사용가능하도록 할 예정같음?
	str := "ysoftman"
	goto label1
	fmt.Println(str)
label1:
	str = "lemon"
	fmt.Println(str)
}
