// author : ysoftman
// encoding : utf-8
// title : go interface test
// desc : go interface test
package main

import "fmt"

type foo1 struct {
}

type foo2 struct {
}

// 인터페이스 정의
type Calc interface {
	calculate(a, b int) int
}

// foo1 타입을 받는(메소드 리시버)형 함수를 만든다.
// calculate 구현
func (f foo1) calculate(a, b int) int {
	a += b
	return a
}

// foo2 타입을 받는(메소드 리시버)형 함수를 만든다.
// calculate 구현
func (f foo2) calculate(a, b int) int {
	a *= b
	return a
}

func main() {
	fmt.Println("go interface test.")
	var f1 Calc
	var f2 Calc

	f1 = foo1{}
	f2 = foo2{}

	// 각 타입에 맞는 함수(인터페이스 구현)를 수행
	fmt.Println("foo1 calculate result:", f1.calculate(2, 3))
	fmt.Println("foo2 calculate result:", f2.calculate(2, 3))

}
