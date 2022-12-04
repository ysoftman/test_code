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
	fmt.Println("[]int, before sort:", mynumlist)
	sort.Ints(mynumlist)
	fmt.Println("[]int, after sort:", mynumlist)
	sort.Sort(sort.Reverse(sort.IntSlice(mynumlist)))
	fmt.Println("[]int, after reverse sort:", mynumlist)
	// Slice 를 사용하면 int slice 정렬 조건도 변경할 수 있다.
	// Slice 를 사용하면 less 함수만 구현하면 된다.
	sort.Slice(mynumlist, func(i, j int) bool {
		return mynumlist[i]%2 < mynumlist[j]%2
	})
	fmt.Println("[]int, after slice(custom less)sort:", mynumlist)

	// 간단한 string sort
	mystrlist := []string{"lemon", "orange", "lemonjuice", "apple"}
	fmt.Println("[]string, before sort:", mystrlist)
	sort.Strings(mystrlist)
	fmt.Println("[]string, after sort:", mystrlist)
	sort.Sort(sort.Reverse(sort.StringSlice(mystrlist)))
	fmt.Println("[]string, after reverse sort:", mystrlist)

	// Slice 를 사용하면 less 함수만 구현하면 된다.
	// 2D 데이터의 경우, 두번째 원소 기준으로 오름 차순 정렬하는 경우
	type Data2DInt [][]int
	myarr2 := Data2DInt{{1, 99}, {3, 2}, {6, 5}, {4, 0}, {1, 9}, {6, 7}}
	fmt.Println("Data2DInt, before sort:", myarr2)
	sort.Slice(myarr2, func(i, j int) bool {
		return myarr2[i][1] < myarr2[j][1]
	})
	fmt.Println("Data2DInt, after sort:", myarr2)
}
