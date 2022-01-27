// ysoftman
// sort 테스트
package main

import (
	"fmt"
	"sort"
)

func main() {
	// 간단한 int sort
	mynumlist := []int{2, 3, 6, 45, 6, 246, 1, 12}
	fmt.Println("before sort:", mynumlist)
	sort.Ints(mynumlist)
	fmt.Println("after sort:", mynumlist)
	sort.Sort(sort.Reverse(sort.IntSlice(mynumlist)))
	fmt.Println("reverse sort:", mynumlist)

	// 간단한 string sort
	mystrlist := []string{"lemon", "orange", "lemonjuice", "apple"}
	fmt.Println("before sort:", mystrlist)
	sort.Strings(mystrlist)
	fmt.Println("after sort:", mystrlist)
	sort.Sort(sort.Reverse(sort.StringSlice(mystrlist)))
	fmt.Println("reverse sort:", mystrlist)

	// sort 인터페이스 사용
	myarr := DataList{{1}, {3}, {6}, {4}, {1}, {6}}
	fmt.Println("before sort:", myarr)
	sort.Sort(myarr)
	fmt.Println("after sort:", myarr)

	// Slice 를 사용하면 less 함수만 구현하면 된다.
	// 2D 데이터의 경우, 두번째 원소 기준으로 오름 차순 정렬하는 경우
	myarr2 := Data2DInt{{1, 99}, {3, 2}, {6, 5}, {4, 0}, {1, 9}, {6, 7}}
	fmt.Println("before sort:", myarr2)
	sort.Slice(myarr2, func(i, j int) bool {
		return myarr2[i][1] < myarr2[j][1]
	})
	fmt.Println("after sort:", myarr2)

	// sort map
	mymap := map[string]string{
		"aaa": "orang",
		"bbb": "lemon",
		"ccc": "apple",
		"ddd": "banana",
	}
	fmt.Println(mymap)
	// mymap 과 같은 key, value 타입의 데이터 구조에 넣는다.
	myCustomMap := make(MyMapList, len(mymap))
	cnt := 0
	for k, v := range mymap {
		myCustomMap[cnt] = MyMap{k, v}
		cnt++
	}
	// myCustomMap 으로 정렬
	sort.Sort(myCustomMap)
	fmt.Println(myCustomMap)
	sort.Sort(sort.Reverse(myCustomMap))
	fmt.Println(myCustomMap)
}

type Data2DInt [][]int

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
