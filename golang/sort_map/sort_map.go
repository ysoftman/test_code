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
	fmt.Println("MyMapList, before sort by map-value:", mymap)

	// 방법1 - Less, Len, Swap 모두 구현해서 사용
	// map value 기준으로 정렬
	myCustomMap := make(MyMapList, len(mymap))
	cnt := 0
	for k, v := range mymap {
		myCustomMap[cnt] = MyMap{k, v}
		cnt++
	}
	// myCustomMap 으로 정렬
	sort.Sort(myCustomMap)
	fmt.Println("MyMapList, after sort by map-value:", myCustomMap)
	sort.Sort(sort.Reverse(myCustomMap))
	fmt.Println("MyMapList, after revere sort by map-value:", myCustomMap)

	// 방법2 - 키들을 slice 로 정렬하고 정렬순서대로 map 에서 찾아 결과에 넣기
	keys := []string{}
	for k := range mymap {
		keys = append(keys, k)
	}
	// key 로, keys 를 정렬한다.
	sort.Slice(keys, func(a, b int) bool {
		return keys[a] < keys[b]
	})
	fmt.Println("mymap, after sort by map-key")
	for i := range keys {
		fmt.Println(keys[i], mymap[keys[i]])
	}

	// key 에 해당하는 value 로, keys 를 정렬한다.
	sort.Slice(keys, func(a, b int) bool {
		return mymap[keys[a]] < mymap[keys[b]]
	})
	fmt.Println("mymap, after sort by map-value")
	for i := range keys {
		fmt.Println(keys[i], mymap[keys[i]])
	}

	// key 에 해당하는 value 로, keys 를 내림차순 정렬한다.
	sort.Slice(keys, func(a, b int) bool {
		return mymap[keys[a]] > mymap[keys[b]]
	})
	fmt.Println("mymap, after reverse sort by map-value")
	for i := range keys {
		fmt.Println(keys[i], mymap[keys[i]])
	}
}
