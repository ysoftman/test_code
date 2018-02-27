// author : ysoftman
// encoding : utf-8
// title : interface 와 error 테스트
package main

import "fmt"

// 파라미터 타입만 변경하여 overloading 함수를 구현 할 수 없고,
// 메소드 리시버의 타입을 주어 overloading 과 비슷하게 사용할 수 있다.
// 컴파일시 중복 함수 구현에러 발생
//func plus(a float32, b float32) float32{
//	return a + b
//}

type myParam interface{}

// 파라미터를 interface 로 받아서 overloading 흉내
func plus(p1 myParam, p2 myParam) myParam {
	switch p1.(type) {
	case int:
		return plus1(p1.(int), p2.(int))
	case float32:
		return plus2(p1.(float32), p2.(float32))
	}
	return 0
}

func plus1(a int, b int) int {
	fmt.Println("plus1()")
	return a + b
}

func plus2(a float32, b float32) float32 {
	fmt.Println("plus2()")
	return a + b
}

// Adder 인터페이스 선언
type Adder interface {
	add(x, y int) int
}

type myType1 int
type myType2 struct {
	x int
	y int
}

// myType1 형 add() 함수
// 메소드 리시버 (a myType1) 명시
func (a myType1) add(x, y int) int {
	return x + y
}

// myType2 형 add() 함수
// 메소드 리시버 (a myType2) 명시
func (a myType2) add(x, y int) int {
	return (a.x + a.y)
}

// Go 에 내장된 Error interface
//type error interface {
//	Error() string
//}

type myError int

// error 인터페이스의 Error() 함수 구현
func (myerr myError) Error() string {
	if myerr == 0 {
		return "ysoftman's ok"
	}
	return "ysoftman's error"
}

// error 값 구현한 myError 를 수행
func run() error {
	return myError(0)
}

func main() {
	// 함수를 직접 호출하는 overloading 방법은 쓸 수 없고, interface 로 흉내낼 수 는 있다.
	a := 1
	b := 2
	fmt.Printf("%v + %v = %v\n", a, b, plus(a, b))
	var c float32 = 1.1
	var d float32 = 2.3
	fmt.Printf("%v + %v = %v\n", c, d, plus(c, d))

	fmt.Println("interface test...")

	var adder Adder
	// adder 에 myType1 형 할당하여 myType1 의 add 함수를 사용하도록 함
	adder = myType1(1)
	fmt.Println("adder.add() = ", adder.add(1, 1))

	// adder 에 myType2 형 할당하여 myType2 의 add 함수를 사용하도록 함
	adder = myType2{5, 7}
	fmt.Println("adder.add() = ", adder.add(1, 1))

	// 에러 인터페이스 구현 테스트
	fmt.Println(run())
}
