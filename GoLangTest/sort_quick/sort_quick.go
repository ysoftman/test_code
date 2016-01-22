// author : ysoftman
// encoding : utf-8
// title : 퀵 정렬
package main

import "fmt"

func main() {
	array := []int{5, 3, 8, 2, 4, 1, 6, 9, 2, 5}
	//	array := []int{7, 3, 8, 2, 4, 1, 6, 9, 0, 5}
	//	array := []int{5, 3, 7, 6, 2, 1, 4}

	fmt.Println("array before =", array)
	quick_sort(&array, 0, len(array)-1, 1)
	fmt.Println("array after  =", array)
}

func quick_sort(input *[]int, left int, right int, depth int) {

	arr := *input

	// 왼쪽 인덱스가 오른쪽 인덱스 보다 커지는 순간 그만둔다.
	if left >= right {
		return
	}

	// 가장 왼쪽 값을 피벗으로 선택한다.
	pivot := arr[left]

	i := left + 1
	j := right

	fmt.Println("array trace  =", arr,
		"depth=", depth, "pivot=", pivot, "left=", left, "right=", right, "i=", i, "j=", j)

	// 피벗 위치는 제외하고
	// 피벗을 기준으로 왼쪽으로는 작은 값을, 오른쪽으로는 큰 값을 위치하도록 한다.
	for {
		// 왼쪽 부분에서 현재 피벗보다 크거나 같은 원소를 찾는다.
		for arr[i] < pivot && i < len(arr)-1 {
			i++
		}

		// 오른쪽 부분에서 현재 피벗보다 작거나 같은 원소를 찾는다.
		for arr[j] > pivot && j > 0 {
			j--
		}

		// 왼쪽 인덱스가 오른쪽 인덱스 보다 커지는 순간 그만둔다.
		if i >= j {
			break
		}

		// for trace
		fmt.Println("array trace  =", arr,
			"depth=", depth, "pivot=", pivot, "left=", left, "right=", right, "i=", i, "j=", j)

		// 스왑
		if arr[i] != arr[j] {
			temp := arr[i]
			arr[i] = arr[j]
			arr[j] = temp
		}
	}

	fmt.Println("array trace  =", arr, "depth=", depth, "swap pivot and j=", j)

	// j가 i보다 작아진 상태에서 피벗 원소와 스왑
	// 현재 j번째 위치는 정렬 완료됨
	temp := arr[left]
	arr[left] = arr[j]
	arr[j] = temp

	// 위 과정이 끝나면 j 값을 기준으로 왼쪽, 오른쪽부분으로 구분
	// 왼쪽부분 퀵정렬 수행
	quick_sort(&arr, left, j-1, depth+1)
	// 오른쪽부분 퀵정렬 수행
	quick_sort(&arr, j+1, right, depth+1)

}
