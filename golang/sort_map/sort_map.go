// ysoftman
// sort 테스트
package main

import (
	"fmt"
	"sort"
)

type MyMap struct {
	Key   string
	Value string
}

type MyMapList []MyMap

// Value 기준으로 정렬
func (mml MyMapList) Less(a, b int) bool {
	if mml[a].Value < mml[b].Value {
		return true
	}
	return false
}

func (mml MyMapList) Len() int {
	return len(mml)
}

func (mml MyMapList) Swap(a, b int) {
	mml[a], mml[b] = mml[b], mml[a]
}

func main() {
	// sort map
	mymap := map[string]string{
		"aaa": "orang",
		"bbb": "lemon",
		"ccc": "apple",
		"ddd": "banana",
	}
	fmt.Println("MyMapList, before sort:", mymap)
	// mymap 과 같은 key, value 타입의 데이터 구조에 넣는다.
	myCustomMap := make(MyMapList, len(mymap))
	cnt := 0
	for k, v := range mymap {
		myCustomMap[cnt] = MyMap{k, v}
		cnt++
	}
	// myCustomMap 으로 정렬
	sort.Sort(myCustomMap)
	fmt.Println("MyMapList, after sort:", myCustomMap)
	sort.Sort(sort.Reverse(myCustomMap))
	fmt.Println("MyMapList, after revere sort:", myCustomMap)
}
