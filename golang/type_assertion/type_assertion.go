// ysoftman
// type assertion  테스트
package main

import (
	"fmt"
)

// x 는 int 형인 동적타입으로 선언되었고 99 값을 가지고 있다.
var x interface{} = 99

func main() {

	// x는 nil 이 아니며 int 타입인것을 assert(단정) 한다는 의미
	// x가 nil 이거나 int 가 아니면 런타임 에러 panic 발생
	// panic: interface conversion: interface {} is int, not float32
	// illegal := x.(float32)
	// fmt.Println(illegal)

	// x가 nil 도 아니고 int 타입이라면 int 형의  x 값을 리턴
	ok := x.(int)
	fmt.Println(ok)
}
