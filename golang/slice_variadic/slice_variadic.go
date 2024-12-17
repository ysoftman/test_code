package main

import "fmt"

func main() {
	func() {
		// variadic 으로 배열 생성
		// ... 파라미터는 variadic 으로, 0 이상의 파라미터가 올수 있다는 의미
		// https://golang.org/ref/spec#Function_types
		// [...] 로 구체적 원소개수를 명시하지 않아도 된다.
		arrayTest := [...]int{11, 22, 33, 44, 55}
		// 슬라이스 크기가 고정되어 있어 자기 자신에게 append 사용할 수 없다.
		// arrayTest = append(arrayTest, 6, 7)
		fmt.Println("arrayTest len:", len(arrayTest), "arrayTest cap:", cap(arrayTest), "arrayTest:", arrayTest)
		// 배열은 추가할 수 없다.
		// arrayTest = append(arrayTest, 9)
	}()
}
