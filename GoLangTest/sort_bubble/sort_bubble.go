// author : ysoftman
// encoding : utf-8
// title : 버블 정렬
package main

import "fmt"

func main() {
	array := []int{5, 3, 8, 2, 4, 1, 6, 9, 2, 5}

	fmt.Println("array before =", array)
	bubble_sort(&array)
	fmt.Println("array after  =", array)
}

func bubble_sort(input *[]int) {

	arr := *input

	for i := 0; i < len(arr); i++ {
		temp := 0
		for j := 0; j < len(arr)-1; j++ {
			if arr[j] > arr[j+1] {
				temp = arr[j+1]
				arr[j+1] = arr[j]
				arr[j] = temp
			}
		}
	}
}
