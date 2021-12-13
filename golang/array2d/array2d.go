// ysoftman
// 2차원 배열 테스트
package main

import "fmt"

func main() {
	fmt.Println("2D array test.")
	arr0 := [][]int{{0, 1}, {1, 2}, {3, 4}}
	arr0 = append(arr0, []int{})
	arr0[3] = []int{9, 9}
	fmt.Println(arr0)

	width := 3
	height := 3
	var arr [][]int
	arr = make([][]int, height)
	for i := 0; i < height; i++ {
		arr[i] = make([]int, width)
	}
	cnt := 0
	for i := 0; i < height; i++ {
		for j := 0; j < width; j++ {
			arr[i][j] = cnt
			cnt++
		}
	}
	fmt.Println(arr)

	arrstr := [][]string{}
	for i := 0; i < 3; i++ {
		temp := []string{}
		for j := 0; j < 2; j++ {
			temp = append(temp, fmt.Sprintf("%v_col", j))
		}
		arrstr = append(arrstr, temp)
	}
	fmt.Println(arrstr)
}
