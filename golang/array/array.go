package main

import "fmt"

func main() {
	func() {
		// 5길이를 가진 배열 생성
		arrayTest := [5]int{11, 22, 33, 44, 55}
		fmt.Println("arrayTest len:", len(arrayTest), "arrayTest cap:", cap(arrayTest), "arrayTest:", arrayTest)
		// 배열은 추가할 수 없다.
		// arrayTest = append(arrayTest, 9)
		// fmt.Println("append", arrayTest)
	}()
}
