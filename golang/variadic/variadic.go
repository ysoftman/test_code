// ysoftman
// variadic 사용하기
package main

import "fmt"

// 파라미터의 개수가 고정되지 않고 다이나믹하게 받을 수 있는 variadic(...)
func sum(nums ...int) int {
	fmt.Print(nums, " -> ")
	sum := 0
	// index. value
	for _, value := range nums {
		sum += value
	}
	fmt.Println(sum)
	return sum
}

func main() {
	sum(1)
	sum(1, 2)
	sum(1, 2, 3)
	sum(1, 2, 3, 4)
	sum(1, 2, 3, 4, 5)
	sum(1, 2, 3, 4, 5, 6)
	sum(1, 2, 3, 4, 5, 6, 7)
	sum(1, 2, 3, 4, 5, 6, 7, 8)
	sum(1, 2, 3, 4, 5, 6, 7, 8, 9)
	sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)

	// 배열의 원소들을 모두 전달할 경우 다음 같이 배열변수명...으로 전달 하면 된다.
	numArray := []int{1, 2, 3, 4, 5}
	sum(numArray...)
}
