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
		defer fmt.Println(i)
	}
	fmt.Println("--------------")

	// 위 print 문은 defer 로 처리되기때문에 이곳의 print 가 먼저 실행된다.
	for i := 0; i < 10; i++ {
		fmt.Println(i)
	}

	fmt.Println("--------------")

}
