// author : ysoftman
// encoding : utf-8
// title : 피보나치(0 1 1 2 3 5 8 13 21 34 55 89 ...) 테스트
package main

import "fmt"

func main() {

	// 일반적인 피보나치 계산
	result := 0
	temp1 := 1
	temp2 := 1
	fmt.Printf("fibonacci1 = %d ", result)
	fmt.Printf("%d ", temp1)
	fmt.Printf("%d ", temp2)
	for i := 0; i < 10; i++ {
		result = temp1 + temp2
		temp1 = temp2
		temp2 = result
		fmt.Printf("%d ", result)
	}

	fmt.Println("")
	
	// 함수 클로저(closure) 성질을 사용하여 피보나치 계산
	f := fibonacci()
	for i := 0; i < 10; i++ {
		f()
	}
	
	fmt.Println("")
}

// 함수내안에 함수형식
func fibonacci() func() int {
	result := 0
	temp1 := 1
	temp2 := 1	
	fmt.Printf("fibonacci2 = %d ", result)
	fmt.Printf("%d ", temp1)
	fmt.Printf("%d ", temp2)
	// 내부함수
	// 클로저는 성질은 내부함수안에서 외부 함수의 변수에 접근할 수 있는것을 말한다.
	// fibonacci() 함수가 return 으로 종료되었지만 fibonacci() 의 resutl, temp1, temp2 는 내부함수에서 계속 사용가능
	return func() int {
		// 피보나치 계산
		result = temp1 + temp2
		temp1 = temp2
		temp2 = result
		fmt.Printf("%d ", result)
		return result
	}
}
