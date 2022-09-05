// author : ysoftman
// encoding : utf-8
// title :
package main

import "fmt"

func main() {
	nums := []int{1, 5, 2, 356, 2, 4, 52, 14, 23, 56, 32, 2, 34, 5, 1}
	fmt.Println("nums before =", nums)
	nums = bucket_sort(nums)
	fmt.Println("nums after  =", nums)
}

func bucket_sort(nums []int) []int {
	maxNum := 0
	for i := 0; i < len(nums); i++ {
		if maxNum < nums[i] {
			maxNum = nums[i]
		}
	}
	// 0~maxNum 의 공간을 만든다. 같은 값이 있을 수 있기 때문에
	// 각 공간은 n개 값을 저장할 수 있도록 한다.
	buckets := make([][]int, maxNum+1)
	for i := 0; i < len(nums); i++ {
		buckets[nums[i]] = append(buckets[nums[i]], nums[i])
	}
	fmt.Println("buckets:", buckets)

	r := []int{}
	for i := 0; i < len(buckets); i++ {
		// 0이 면 값이 없는것이라 스킵
		if len(buckets[i]) > 0 {
			r = append(r, buckets[i]...)
		}
	}
	return r
}
