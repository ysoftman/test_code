// author : ysoftman
// encoding : utf-8
// title : go interface test
// desc : go interface test
package main

import (
	"fmt"
	"reflect"
)

// struct 는 데이터 필드들의 집합
// interface 는 구현해야 하는 메소드들의 집합

// Calc 인터페이스 정의,Calc 인터페이스는 calculate() 구현한것이라면 모든 될 수 있다.
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
	f3 := foo3{1, 2}

	// 각 타입에 맞는 함수(인터페이스 구현)를 수행
	fmt.Println("foo1 calculate result:", doCal(f1))
	fmt.Println("foo2 calculate result:", doCal(f2))

	// foo3 는 calute() int 를 구현하고 있지 않아 doCal 을 사용할 수 없다.
	// fmt.Println("foo2 calculate result:", doCal(f3))

	f4 := &f3
	fmt.Printf("f4: %p %v %v %v %v %v\n", f4, f4, *f4, &f4, *(&f4), *(*(&f4)))

	// interface{} 파라미터는 어떤 타입의 값이던 전달 할 수 있다.
	interfaceParameter(1, 'a', "abc", f1, f2, f3, f4, &f4)
}

// 빈인터페이스는 0개의 메소드 구현이 필요한것으로 볼 수 있다.
// 따라서 모든 타입의 값을 파라미터로 받을 수 있다. C/C++ 에서의 void* 와 같음
// ... variadic 으로 여러개의 타입 값들을 받을 수 있다.
func interfaceParameter(x ...interface{}) {
	fmt.Println("interface parameter test.")
	fmt.Println(x)

	for _, v := range x {
		fmt.Println(v)
		r := reflect.ValueOf(v)
		if r.Kind() == reflect.Ptr {
			fmt.Println("-r.CanAddr():", r.CanAddr())
			fmt.Println("-value that the interface v contains:", r.Elem())
		}
	}
}
