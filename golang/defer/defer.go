// author : ysoftman
// encoding : utf-8
// title : defer 테스트
package main

import (
	"fmt"
)

func main() {

	// defer (지연시키기)를 사용하면 처리(함수콜)을 예약하고
	// 현재 함수가 리턴되기전 실행된다.
	for i := 0; i < 10; i++ {
		// defer 는 LIFO 방식으로 처리되기때문에 9, 8, ... 1, 0 으로 출력된다.
		defer fmt.Println("main()", i)
	}
	fmt.Println("--------------")

	// 위 print 문은 defer 로 처리되기때문에 이곳의 print 가 먼저 실행된다.
	for i := 0; i < 10; i++ {
		fmt.Println("main()", i)
	}

	fmt.Println("--------------")
	fmt.Println(aaa())
	fmt.Println("-----end-----")
}

func aaa() (result string) {
	// 여러개의 defer 를 사용 할 수 있다.(하지만 트레이싱이 어려워 지양해야 한다.)
	// defer 는 LIFO 로 c -> b -> a 순으로 출력된다.
	defer fmt.Println("aaa() a")
	defer fmt.Println("aaa() b")

	// defer 에서 변수 할당을 위해서 함수로 구현해 호출해야 한다.
	defer func() {
		fmt.Println("aaa() c")
		result = "lemon"
	}()
	// apple 리턴 후 result = "lemon" 이 수행되 최종적으로 lemon 이 리턴된다.
	return "appple"
}
