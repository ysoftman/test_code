// author : ysoftman
// encoding : utf-8
// title : go interface test
// desc : go interface test
package main

import "fmt"

// Calc 인터페이스 정의
type Calc interface {
	calculate() int
}

// Calc 인터페이스를 구현한 foo1, foo2 를 인자로 받을 수 있다.
func doCal(calc Calc) int {
	return calc.calculate()
}

type foo1 struct {
	a, b int
}

type foo2 struct {
	a, b int
}

type foo3 struct {
	a, b float32
}

// foo1 타입을 받는(메소드 리시버)형 함수를 만든다.
// calculate 구현
func (f foo1) calculate() int {
	f.a += f.b
	return f.a
}

// foo2 타입을 받는(메소드 리시버)형 함수를 만든다.
// calculate 구현
func (f foo2) calculate() int {
	f.a *= f.b
	return f.a
}

func (f foo3) calculate() float32 {
	f.a *= f.b
	return f.a
}

func main() {
	fmt.Println("go interface test.")
	f1 := foo1{1, 2}
	f2 := foo2{1, 2}

	// 각 타입에 맞는 함수(인터페이스 구현)를 수행
	fmt.Println("foo1 calculate result:", doCal(f1))
	fmt.Println("foo2 calculate result:", doCal(f2))

	// foo3 는 calute() int 를 구현하고 있지 않아 doCal 을 사용할 수 없다.
	// f3 := foo3{1, 2}
	// fmt.Println("foo2 calculate result:", doCal(f3))

}
