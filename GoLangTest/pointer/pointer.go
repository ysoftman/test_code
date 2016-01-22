// author : ysoftman
// encoding : utf-8
// title : pointer test
package main

import "fmt"

func main() {
	var1 := 123
	fmt.Println("var1 = ", var1)

	var2 := var1
	fmt.Println("var1 = ", var1)
	fmt.Println("var2 = ", var2)

	var2 = 456
	fmt.Println("var1 = ", var1)
	fmt.Println("var2 = ", var2)

	// Go에서는 포인터 연산은 할 수 없지만 C 와 같이 *, & 로 포인터처럼 사용할 수 있다.
	// var1 의 주소값을 사용(참조)하는 var3 포인터 변수
	var3 := &var1
	fmt.Println("var1 = ", var1)
	fmt.Println("var2 = ", var2)
	fmt.Println("var3 = ", *var3)

	// var3 포인터의 값을 변경하면 var1의 값도 변경된다.
	*var3 = 789
	fmt.Println("var1 = ", var1)
	fmt.Println("var2 = ", var2)
	fmt.Println("var3 = ", *var3)
}
