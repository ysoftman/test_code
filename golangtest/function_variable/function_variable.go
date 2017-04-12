// author : ysoftman
// encoding : utf-8
// title : 함수 변수 및 기타 테스트

package main

import "fmt"
import "os"

// 함수 밖에서는 := 를 사용할 수 없다.
// non-declaration statement outside function body
//gVal1 := 1
var gVal1 int = 10

// 함수 밖에서는 선어 후에 = 를 사용할 수 없다.
// non-declaration statement outside function body
//gVal1 = 0

// func main must have no arguments and no return values
func main() {
	// 아규먼트 파악하기
	fmt.Println("len(os.Args) = ", len(os.Args), "\tos.Args = ", os.Args)
	for i := range os.Args {
		fmt.Println("os.Args[", i, "] = ", os.Args[i])
	}

	// 일반 함수 사용
	fmt.Println("add() = ", add(1, 2))

	// 가변 인자 함수 사용
	fmt.Println("add_variable_argument() = ", add_variable_argument(1, 2, 3, 4, 5, 6, 7, 8, 9, 10))

	// 멀티 리턴 함수 사용
	a, b := add_multi_return(1, 2)
	fmt.Println("add_multi_return() = ", a, b)

	// 함수 변수 사용
	adder_function := adder
	fmt.Println("adder_function() = ", adder_function(2, 2))

	// 익명 함수 변수 사용
	anonymous_function := func(x, y int) int {
		return x + y
	}
	fmt.Println("anonymous_function() = ", anonymous_function(1, 4))

}

// 사용자 함수를 main() 이전에 선언할 필요가 없다.
func add(x, y int) int {
	gVal1++
	fmt.Println("gVal1 = ", gVal1)
	return x + y
}

// 가변 인자 받기, 리턴 변수 미리 지정
func add_variable_argument(x ...int) (sum int) {
	gVal1++
	fmt.Println("gVal1 = ", gVal1)
	for k, v := range x {
		fmt.Printf("k=%v v=%v\n", k, v)
		sum += v
	}
	return
}

// 멀티 리턴
func add_multi_return(x int, y int) (a int, b int) {
	gVal1++
	fmt.Println("gVal1 = ", gVal1)
	return (x + y), (x * y)
}

func adder(x, y int) int {
	gVal1++
	fmt.Println("gVal1 = ", gVal1)
	return x + y
}
