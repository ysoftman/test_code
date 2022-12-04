// ysoftman
// sort 테스트
package main

import (
	"fmt"
	"sort"
)

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

func main() {
	// sort 인터페이스 사용
	myarr := DataList{{1}, {3}, {6}, {4}, {1}, {6}}
	fmt.Println("DataList, before sort:", myarr)
	sort.Sort(myarr)
	fmt.Println("DataList, after sort:", myarr)
}
