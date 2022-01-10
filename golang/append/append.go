// ysoftman
// append test

package main

import "fmt"

func main() {
	func() {
		arr := [3]int{1, 2, 3}  // array
		slice := []int{1, 2, 3} // sliceƒ
		r := []int{}            // slice

		// append(slice []Type, elems ...Type) []Type
		// array 는 다음과 같은 방법으로 slice 에 바로 붙일수 없다.
		// r = append(r, arr...)
		// array 는 다음과 같이 스라이싱 하면 slice 에 바로 붙일수 있다.
		r = append(r, arr[0:]...)
		r = append(r, arr[0], arr[1], arr[2])
		// slice 는 바로 붙일 수 있다.
		r = append(r, slice...)
		r = append(r, slice[:1]...)
		fmt.Println("r:", r)
	}()

	func() {
		twoD := [][]int{}
		nums := []int{1, 2, 3}

		// nums 를 변경하면 twoD 도 변경된다.
		// twoD = append(twoD, nums)
		// num을 복사한 nums2 를 사용한다.
		nums2 := make([]int, len(nums))
		copy(nums2, nums)
		twoD = append(twoD, nums2)
		fmt.Println("twoD:", twoD)
		nums[1] = 88
		fmt.Println("twoD:", twoD)
	}()

	func() {
		twoD := &[][]int{}
		nums := []int{1, 2, 3}
		// nums 를 변경하면 twoD 도 변경된다.
		// *twoD = append(*twoD, nums)
		// num을 복사한 nums2 를 사용한다.
		nums2 := make([]int, len(nums))
		copy(nums2, nums)
		*twoD = append(*twoD, nums2)
		fmt.Println("twoD:", *twoD)
		nums[1] = 99
		fmt.Println("twoD:", *twoD)
	}()
}
