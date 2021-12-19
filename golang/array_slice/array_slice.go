// author : ysoftman
// encoding : utf-8
// title : array slice 테스트
// array(배열)은 길이가 고정되어 추가 삭제를 할 수 없다.
// slice(슬라이스) 는
// 내부 배열, underlying array (beginning at the element referred to by the slice pointer)을 가리키는 포인터
// 슬라이의 길이,
// 슬라이스 용량(내부배열의 크기가 변경을 용이하기 위해서 미리 용량만큰 할당),
// 으로 구성된 데이터 구조다.

package main

import (
	"fmt"
)

type Dummy struct {
	strlist []string
}

func main() {

	func() {
		dummy1 := Dummy{
			strlist: []string{"lemon", "apple", "orange"},
		}
		dummy2 := Dummy{}
		dummy2 = dummy1
		// 참조 복사
		fmt.Printf("dummy1:%v, %p\n", dummy1, dummy1.strlist)
		fmt.Printf("dummy2:%v, %p\n", dummy2, dummy2.strlist)
		// deep copy
		dummy2.strlist = make([]string, len(dummy1.strlist))
		copiedCnt := copy(dummy2.strlist, dummy1.strlist)
		fmt.Println("copiedCnt:", copiedCnt)
		fmt.Printf("dummy1:%v, %p\n", dummy1, dummy1.strlist)
		fmt.Printf("dummy2:%v, %p\n", dummy2, dummy2.strlist)
		fmt.Printf("dummy2:%v, %v\n", dummy2, dummy2.strlist[0:])
		fmt.Printf("dummy2:%v, %v\n", dummy2, dummy2.strlist[1:])
		fmt.Printf("dummy2:%v, %v\n", dummy2, dummy2.strlist[2:])

		// https://golang.org/ref/spec#Slice_expressions
		// For arrays or strings, the indices are in range if 0 <= low <= high <= len(a), otherwise they are out of range.
		// [low:high] 에서 low,high 가 len(a)까지도 인덱싱 가능하다.
		// len(a)으로 인덱싱하면 zero-length slice인 [] 을 리턴한다.
		// len(a)+1 부터는 out of range 패닉 발생!
		fmt.Printf("dummy2:%v, len:%v, cap:%v, %v\n", dummy2, len(dummy2.strlist), cap(dummy2.strlist), dummy2.strlist[3:])
	}()

	func() {
		var sliceStr []string
		sliceStr = append(sliceStr, "aaa")
		sliceStr = append(sliceStr, "bbb")
		sliceStr = append(sliceStr, "ccc")
		fmt.Println(sliceStr)
	}()

	func() {
		// [] 리터털을 사용한 일반적인 슬라이스 선언
		// 슬라이스 생성시 2번째는 7값, 4번째는 99값을 넣는다.
		// 이때 설정안된 곳은 0값으로 채워지고 마지막으로 설정된 n번째가 배열의 크기가 된다.
		sliceTest := []int{2: 7, 4: 99}
		fmt.Println("sliceTest len:", len(sliceTest), "sliceTest cap:", cap(sliceTest), "sliceTest:", sliceTest)
		sliceTest = append(sliceTest, 9)
		fmt.Println("append", sliceTest)
	}()

	func() {
		sliceTest1 := []int{10, 20, 30}
		fmt.Println("sliceTest1 len:", len(sliceTest1), "sliceTest1 cap:", cap(sliceTest1), "sliceTest1:", sliceTest1)
		// for 로 해보기
		//	for i := 0; i < len(sliceTest1); i++ {
		//		fmt.Println("sliceTest1[", i, "]:", sliceTest1[i])
		//	}
		// range 로 해보기
		for key, value := range sliceTest1 {
			fmt.Println("sliceTest1[", key, "]:", value)
		}
		fmt.Println("sliceTest1[1:3]", sliceTest1[1:3])
		fmt.Println("sliceTest1[2:]", sliceTest1[2:])

		// 슬라이스 내부 배열의 일정 부분을 가져와 슬라이스 형태로 참조
		sliceTest2 := sliceTest1[2:]
		fmt.Println("sliceTest2 len:", len(sliceTest2), "sliceTest2 cap:", cap(sliceTest2), "sliceTest2:", sliceTest2)
		// append 를 사용하면 내부배열 참조가 아닌 복사가 된다.
		sliceTest3 := append(sliceTest1, 60, 70)
		fmt.Println("sliceTest3 len:", len(sliceTest3), "sliceTest3 cap:", cap(sliceTest3), "sliceTest3:", sliceTest3)
		// copy 를 사용하면 내부배열 참조가 아닌 복사가 된다.
		// sliceTest2 의 cap 만큼 복사된다.
		sliceTest4 := make([]int, 10, 10)
		copy(sliceTest4, sliceTest1)
		fmt.Println("sliceTest4 len:", len(sliceTest4), "sliceTest4 cap:", cap(sliceTest4), "sliceTest4:", sliceTest4)

		sliceTest1[2] = -1

		// 참조하고 있는 슬라이스의 배열값이 변경되면 같이 변경된다
		fmt.Println("sliceTest2 len:", len(sliceTest2), "sliceTest2 cap:", cap(sliceTest2), "sliceTest2:", sliceTest2)
		// 복사되어 변경되지 않는다.
		fmt.Println("sliceTest3 len:", len(sliceTest3), "sliceTest3 cap:", cap(sliceTest3), "sliceTest3:", sliceTest3)
		// 복사되어 변경되지 않는다.
		fmt.Println("sliceTest4 len:", len(sliceTest4), "sliceTest4 cap:", cap(sliceTest4), "sliceTest4:", sliceTest4)
	}()

}
