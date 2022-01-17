// ysoftman
// range 와 for ++ 차이
package main

import "fmt"

func main() {
	myarr := []int{1, 2, 3, 4, 5}
	myarr2 := make([]int, 5)
	copy(myarr2, myarr)
	idx := 0
	// idx 가 인덱스 범위까지 증가된다.
	for idx = range myarr {
	}
	fmt.Println("for range:", idx)
	// idx 가 인덱스 범위+1까지 증가된다.
	for idx = 0; idx < len(myarr); idx++ {
	}
	fmt.Println("for ++:", idx)

	fmt.Println("-----")
	for idx, v := range myarr {
		fmt.Println(len(myarr), myarr, idx, v)
		// panic: runtime error: slice bounds out of range [2:1]
		// myarr = myarr[2:]
		// 매번 myarr 가 바뀌지만 i, v 는 맨처음에 myarr 값을 복사한것을 사용한다.
		// 5 [1 2 3 4 5] 0 1
		// 4 [1 2 3 4] 1 2
		// 3 [1 2 3] 2 3
		// 2 [1 2] 3 4
		// 1 [1] 4 5
		myarr = myarr[:len(myarr)-1]
	}

	fmt.Println("-----")
	for idx := 0; idx < len(myarr2); idx++ {
		fmt.Println(len(myarr2), myarr2, idx, myarr2[idx])
		// panic: runtime error: index out of range [0] with length 0
		// myarr2 = myarr2[2:]
		// 매번 len(myarr2) 이 다시 계산 되기 때문에 부터 줄이면 처리된다.
		// 하지만 idx는 계속 증가중이기 때문에 다음과 idx=2일때 까지만 처리된다.
		// 5 [1 2 3 4 5] 0 1
		// 4 [1 2 3 4] 1 2
		// 3 [1 2 3] 2 3
		myarr2 = myarr2[:len(myarr2)-1]
	}
}
