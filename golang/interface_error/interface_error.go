// author : ysoftman
// encoding : utf-8
// title : interface 와 error 테스트
package main

import "fmt"

func not_work_add(a int, b int) int {
	return a + b
}

// 파라미터 타입만 변경하여 overloading 함수를 구현 할 수 없다.
// 컴파일시 중복 함수 구현에러 발생
//func not_work_add(a float32, b float32) float32{
//	return a + b
//}
func not_work_add2(a float32, b float32) float32 {
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
	} else {
		return "ysoftman's error"
	}

}

// error 값 구현한 myError 를 수행
func run() error {
	return myError(0)
}

func main() {

	// 함수를 직접 호출하는 overloading 방법은 쓸 수 없다.
	var a int = 1
	var b int = 2
	fmt.Printf("%v + %v = %v\n", a, b, not_work_add(a, b))
	var c float32 = 1.1
	var d float32 = 2.3
	fmt.Printf("%v + %v = %v\n", c, d, not_work_add2(c, d))

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