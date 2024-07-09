// ysoftman
// call by value test

package main

import "fmt"

func main() {
	a := 1
	// 참고로 golang 에는 다음과 같은 참조 변수가 없다.
	// var &b = a
	// &연산자로 주소값을 가지는 변수가 있지만 그 변수 자체가 별도의 주소를 가지고 있기 때문에 참조변수는 아니다
	// https://dave.cheney.net/2017/04/29/there-is-no-pass-by-reference-in-go

	intCallByValue(a)
	fmt.Printf("main, %p a: %#v\n", &a, a)
	intCallByReference(&a)
	fmt.Printf("main, %p a: %#v\n", &a, a)
}

func intCallByValue(a int) {
	a = 123
	fmt.Printf("intCallByValue, %p a: %#v\n", &a, a)
}

func intCallByReference(a *int) {
	*a = 55
	fmt.Printf("intCallByReference, %p a: %#v\n", a, *a)
}
