package main

import "fmt"

func main() {

	// create array
	arrayStr := [3]string{"2", "3"}
	// array(배열)은 길이가 고정되어 추가 삭제를 할 수 없다.
	// arrayStr = append(arrayStr, "aaa")
	fmt.Println("arrayStr:", arrayStr)

	// slice(슬라이스) 는
	// 내부 배열, underlying array (beginning at the element referred to by the slice pointer)을 가리키는 포인터
	// 슬라이의 길이,
	// 슬라이스 용량(내부배열의 크기가 변경을 용이하기 위해서 미리 용량만큰 할당),
	// 으로 구성된 데이터 구조다.
	// create slice
	var sliceStr []string
	sliceStr = append(sliceStr, "aaa")
	sliceStr = append(sliceStr, "bbb")
	sliceStr = append(sliceStr, "ccc")
	fmt.Println("sliceStr:", sliceStr)

	// [] 리터털을 사용한 일반적인 슬라이스 선언
	// 슬라이스 생성시 2번째는 7값, 4번째는 99값을 넣는다.
	// 이때 설정 안된 곳은 0값으로 채워지고 마지막으로 설정된 n번째가 배열의 크기가 된다.
	sliceTest1 := []int{2: 7, 4: 99}
	sliceTest1 = append(sliceTest1, 9)
	fmt.Println("sliceTest1-append", sliceTest1)
	fmt.Printf("sliceTest1 type: %T len: %v sliceTest1 cap: %v sliceTest1: %v\n", sliceTest1, len(sliceTest1), cap(sliceTest1), sliceTest1)

	sliceTest2 := []int{2: 7, 4: 99}
	sliceTest2 = append(sliceTest2, 9)
	fmt.Println("sliceTest2-append", sliceTest1)
	fmt.Printf("sliceTest2 type: %T len: %v sliceTest2 cap: %v sliceTest2: %v\n", sliceTest1, len(sliceTest2), cap(sliceTest2), sliceTest2)

	// 슬라이스끼리는 비교할 수 없다. 단 nil 과는 비교할 수 있다. (slice can only be compared to nil)
	// fmt.Printf("sliceTest == sliceTest2 ==> %v\n", sliceTest == sliceTest2)
}
