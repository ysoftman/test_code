// ysoftman
// sort 테스트
package main

import (
	"fmt"
	"sort"
)

func main() {
	num := 10
	aaa := make([]int, num)
	for i := 0; i < 10; i++ {
		aaa[i] = i * 2
	}
	fmt.Println("aaa:", aaa)

	// 간단한 int sort
	mynumlist := []int{2, 3, 6, 45, 6, 246, 1, 12}
	fmt.Println("before sort:", mynumlist)
	sort.Ints(mynumlist)
	fmt.Println("after sort:", mynumlist)

	// sort 인터페이스 사용
	myarr := []MyData{{1}, {3}, {6}, {4}, {1}, {6}}
	fmt.Println("before sort:", myarr)
	sort.Sort(DataList(myarr))
	fmt.Println("after sort:", myarr)
}

// MyData 내용
type MyData struct {
	num int
}

// DataList 내용
type DataList []MyData

// Less sort Less 인터페이스 구현
func (receiver DataList) Less(a, b int) bool {
	if receiver[a].num < receiver[b].num {
		return true
	}
	return false
}

// Len sort Len 인터페이스 구현
func (receiver DataList) Len() int {
	return len(receiver)
}

// Swap sort Swap 인터페이스 구현
func (receiver DataList) Swap(a, b int) {
	receiver[a], receiver[b] = receiver[b], receiver[a]
}
