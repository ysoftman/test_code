// author : ysoftman
// encoding : utf-8
// title : 패키지 테스트
package main

import (
	"fmt"
	"my_math"
)

func main() {
	// 같은 패키지 않의 함수 호출 가능
	innerFunc1(1)

	// 다른 패키지의 소문자로 시작하는 함수 호출 불가능
	// 컴파일 에러발생 --> cannot refer to unexported name my_math.add
	//result := my_math.add(1,2)

	// 다른 패키지의 대문자로 시작하는 함수 호출 가능
	fmt.Println("call my_math.Add(1,2)")
	result := my_math.Add(1, 2)
	fmt.Println("result = ", result)
}

func innerFunc1(x int) {
	fmt.Println("innerFunc1(", x, ")")
}
