// ysoftman
// range 와 for ++ 차이
package main

import "fmt"

func main() {
	myarr := []int{1, 2, 3, 4, 5}
	idx := 0
	// idx 가 인덱스 범위까지 증가된다.
	for idx = range myarr {
	}
	fmt.Println("for range:", idx)
	// idx 가 인덱스 범위+1까지 증가된다.
	for idx = 0; idx < len(myarr); idx++ {
	}
	fmt.Println("for ++:", idx)
}
