package main

import "fmt"

func main() {
	sliceTest1 := []int{10, 20, 30}
	fmt.Println("sliceTest1 len:", len(sliceTest1), "sliceTest1 cap:", cap(sliceTest1), "sliceTest1:", sliceTest1)
	// for 로 해보기
	for i := 0; i < len(sliceTest1); i++ {
		fmt.Println("sliceTest1 loop1[", i, "]:", sliceTest1[i])
	}
	// range 로 해보기
	for key, value := range sliceTest1 {
		fmt.Println("sliceTest1 loop2[", key, "]:", value)
	}
	fmt.Println("sliceTest1[1:3]", sliceTest1[1:3])
	fmt.Println("sliceTest1[2:]", sliceTest1[2:])

	// 슬라이스 내부 배열의 일정 부분을 가져와 슬라이스 형태로 참조
	// sliceTest2 는  값은 30, len=1, cap=1 로 생성된다.
	sliceTest2 := sliceTest1[2:]
	fmt.Println("sliceTest2 len:", len(sliceTest2), "sliceTest2 cap:", cap(sliceTest2), "sliceTest2:", sliceTest2)
	// append 를 사용하면 내부배열 참조가 아닌 복사가 된다.
	sliceTest3 := append(sliceTest1, 60, 70)
	fmt.Println("sliceTest3 len:", len(sliceTest3), "sliceTest3 cap:", cap(sliceTest3), "sliceTest3:", sliceTest3)
	// copy 를 사용하면 내부배열 참조가 아닌 복사가 된다.
	// sliceTest2 의 cap 만큼 복사된다.
	sliceTest4 := make([]int, 10, 10)
	copiedCnt := copy(sliceTest4, sliceTest1)
	fmt.Println("copiedCnt:", copiedCnt)
	fmt.Println("sliceTest4 len:", len(sliceTest4), "sliceTest4 cap:", cap(sliceTest4), "sliceTest4:", sliceTest4)

	sliceTest1[2] = -1

	// 참조하고 있는 슬라이스의 배열값이 변경되면 같이 변경된다
	fmt.Println("sliceTest2 len:", len(sliceTest2), "sliceTest2 cap:", cap(sliceTest2), "sliceTest2:", sliceTest2)
	// 복사되어 변경되지 않는다.
	fmt.Println("sliceTest3 len:", len(sliceTest3), "sliceTest3 cap:", cap(sliceTest3), "sliceTest3:", sliceTest3)
	// 복사되어 변경되지 않는다.
	fmt.Println("sliceTest4 len:", len(sliceTest4), "sliceTest4 cap:", cap(sliceTest4), "sliceTest4:", sliceTest4)
}
