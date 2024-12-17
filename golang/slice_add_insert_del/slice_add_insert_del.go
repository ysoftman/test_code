package main

import "fmt"

func main() {
	func() {
		sliceTest := []int{1, 2, 3, 4, 5}
		fmt.Println("sliceTest:", sliceTest)

		// pop
		value, sliceTest := sliceTest[0], sliceTest[1:]
		fmt.Println("pop value:", value, " sliceTest:", sliceTest)

		// pop-back
		value, sliceTest = sliceTest[len(sliceTest)-1], sliceTest[:len(sliceTest)-1]
		fmt.Println("pop-back value:", value, " sliceTest:", sliceTest)

		// push(add)
		value = 5
		sliceTest = append(sliceTest, value)
		fmt.Println("push value:", value, " sliceTest:", sliceTest)

		// push-front
		value = 1
		sliceTest = append([]int{value}, sliceTest...)
		fmt.Println("push-front value:", value, " sliceTest:", sliceTest)

		// delete
		// append 에서 ... 는 해당 타입의 모든(0 이상) 원소들을 의미
		// 3번째 값만 삭제
		idx := 3
		fmt.Printf("slice:%v ", sliceTest)
		if len(sliceTest) >= idx {
			if len(sliceTest) > idx+1 {
				sliceTest = append(sliceTest[:idx], sliceTest[idx+1:]...)
			} else {
				sliceTest = append(sliceTest[:idx])
			}
			fmt.Println("delete idx:", idx, "sliceTest len:", len(sliceTest), "sliceTest cap:", cap(sliceTest), " sliceTest:", sliceTest)
		}
		// 한번더 3번째 값만 삭제
		fmt.Printf("slice:%v ", sliceTest)
		if len(sliceTest) >= idx {
			if len(sliceTest) > idx+1 {
				sliceTest = append(sliceTest[:idx], sliceTest[idx+1:]...)
			} else {
				sliceTest = append(sliceTest[:idx])
			}
			fmt.Println("delete idx:", idx, "sliceTest len:", len(sliceTest), "sliceTest cap:", cap(sliceTest), " sliceTest:", sliceTest)
		}

		// addSlice, deleteSlice 로 결과를 리턴 받지 않으면
		// 이곳의 sliceTest 는 len 이 갱신되지 않아 유효하지 않는 인덱스를 액세스할 위험이 있다.
		fmt.Println("")
		fmt.Println("sliceTest:", sliceTest)
		for i := 0; i < 3; i++ {
			sliceTest = addSlice(i, sliceTest)
		}
		fmt.Println("")

		sliceTest = insertSlice(77, 5, sliceTest)
		sliceTest = insertSlice(88, 5, sliceTest)

		fmt.Println("")
		for i := 0; i < 3; i++ {
			sliceTest = deleteSlice(0, sliceTest)
		}
		fmt.Println("")
	}()
}

func addSlice(v int, slice []int) []int {
	fmt.Printf("slice:%v ", slice)
	slice = append(slice, v)
	fmt.Println("add v:", v, "slice len:", len(slice), "slice cap:", cap(slice), " slice:", slice)
	return slice
}

func insertSlice(v, idx int, slice []int) []int {
	fmt.Printf("slice:%v ", slice)
	fmt.Println("\nbefore insert v:", v, "slice len:", len(slice), "slice cap:", cap(slice), " slice:", slice)
	// https://github.com/golang/go/wiki/SliceTricks#insert
	// slice = append(slice[:idx+1], slice[idx:]...)
	slice = append(slice, 0)
	copy(slice[idx+1:], slice[idx:])
	fmt.Println("after insert v:", v, "slice len:", len(slice), "slice cap:", cap(slice), " slice:", slice)
	slice[idx] = v
	fmt.Println("insert v:", v, "slice len:", len(slice), "slice cap:", cap(slice), " slice:", slice)

	return slice
}

func deleteSlice(idx int, slice []int) []int {
	fmt.Printf("slice:%v ", slice)
	if len(slice) >= idx {
		if len(slice) > idx+1 {
			slice = append(slice[:idx], slice[idx+1:]...)
		} else {
			slice = append(slice[:idx])
		}
		fmt.Println("delete idx:", idx, "slice len:", len(slice), "slice cap:", cap(slice), " slice:", slice)
	}
	return slice
}
