// author : ysoftman
// encoding : utf-8
// title : array slice 테스트
package main

import "fmt"

func main() {

	func() {
		// slice(슬라이스) 는
		// 내부 배열을 가리키는 포인터,
		// 슬라이의 길이,
		// 슬라이스 용량(내부배열의 크기가 변경을 용이하기 위해서 미리 용량만큰 할당),
		// 으로 구성된 데이터 구조다.
		// 리터털을 사용한 일반적인 슬라이스 선언
		sliceTest := [5]int{11, 22, 33, 44, 55}
		fmt.Println("sliceTest len = ", len(sliceTest), "sliceTest cap = ", cap(sliceTest), "sliceTest = ", sliceTest)
	}()

	func() {
		// 슬라이스 생성시 2번째는 7값, 5번째는 99값을 넣는다.
		// 이때 설정안된 곳은 0값으로 채워지고 마지막으로 설정된 n번째가 배열의 크기가 된다.
		sliceTest := []int{2: 7, 5: 99}
		fmt.Println("sliceTest len = ", len(sliceTest), "sliceTest cap = ", cap(sliceTest), "sliceTest = ", sliceTest)
		sliceTest = append(sliceTest, 5)
	}()

	func() {
		// ... 파라미터는 variadic 으로, 0 이상의 파라미터가 올수 있다는 의미
		// https://golang.org/ref/spec#Function_types
		// [...] 로 구체적 원소개수를 명시하지 않아도 된다.
		sliceTest := [...]int{11, 22, 33, 44, 55}
		// 슬라이스 크기가 고정되어 있어 자기 자신에게 append 사용할 수 없다.
		// sliceTest = append(sliceTest, 6, 7)
		fmt.Println("sliceTest len = ", len(sliceTest), "sliceTest cap = ", cap(sliceTest), "sliceTest = ", sliceTest)
	}()

	func() {
		sliceTest1 := []int{10, 20, 30}
		fmt.Println("sliceTest1 len = ", len(sliceTest1), "sliceTest1 cap = ", cap(sliceTest1), "sliceTest1 = ", sliceTest1)
		// for 로 해보기
		//	for i := 0; i < len(sliceTest1); i++ {
		//		fmt.Println("sliceTest1[", i, "] = ", sliceTest1[i])
		//	}
		// range 로 해보기
		for key, value := range sliceTest1 {
			fmt.Println("sliceTest1[", key, "] = ", value)
		}
		fmt.Println("sliceTest1[1:3]", sliceTest1[1:3])
		fmt.Println("sliceTest1[2:]", sliceTest1[2:])

		// 슬라이스 내부 배열의 일정 부분을 가져와 슬라이스 형태로 참조
		sliceTest2 := sliceTest1[2:]
		fmt.Println("sliceTest2 len = ", len(sliceTest2), "sliceTest2 cap = ", cap(sliceTest2), "sliceTest2 = ", sliceTest2)
		// append 를 사용하면 내부배열 참조가 아닌 복사가 된다.
		sliceTest3 := append(sliceTest1, 60, 70)
		fmt.Println("sliceTest3 len = ", len(sliceTest3), "sliceTest3 cap = ", cap(sliceTest3), "sliceTest3 = ", sliceTest3)
		// copy 를 사용하면 내부배열 참조가 아닌 복사가 된다.
		// sliceTest2 의 cap 만큼 복사된다.
		sliceTest4 := make([]int, 10, 10)
		copy(sliceTest4, sliceTest1)
		fmt.Println("sliceTest4 len = ", len(sliceTest4), "sliceTest4 cap = ", cap(sliceTest4), "sliceTest4 = ", sliceTest4)

		sliceTest1[2] = -1

		// 참조하고 있는 슬라이스의 배열값이 변경되면 같이 변경된다
		fmt.Println("sliceTest2 len = ", len(sliceTest2), "sliceTest2 cap = ", cap(sliceTest2), "sliceTest2 = ", sliceTest2)
		// 복사되어 변경되지 않는다.
		fmt.Println("sliceTest3 len = ", len(sliceTest3), "sliceTest3 cap = ", cap(sliceTest3), "sliceTest3 = ", sliceTest3)
		// 복사되어 변경되지 않는다.
		fmt.Println("sliceTest4 len = ", len(sliceTest4), "sliceTest4 cap = ", cap(sliceTest4), "sliceTest4 = ", sliceTest4)
	}()

	func() {
		sliceTest := []int{1, 2, 3, 4, 5}
		fmt.Println("sliceTest =", sliceTest)

		// pop
		value, sliceTest := sliceTest[0], sliceTest[1:]
		fmt.Println("pop value =", value, " sliceTest =", sliceTest)

		// pop-back
		value, sliceTest = sliceTest[len(sliceTest)-1], sliceTest[:len(sliceTest)-1]
		fmt.Println("pop-back value =", value, " sliceTest =", sliceTest)

		// push(add)
		value = 5
		sliceTest = append(sliceTest, value)
		fmt.Println("push value =", value, " sliceTest =", sliceTest)

		// push-front
		value = 1
		sliceTest = append([]int{value}, sliceTest...)
		fmt.Println("push-front value =", value, " sliceTest =", sliceTest)

		// delete
		// append 에서 ... 는 해당 타입의 모든(0 이상) 원소들을 의미
		// 3번째 값만 삭제 효과
		sliceTest = append(sliceTest[:3], sliceTest[4:]...)
		fmt.Println("delete idx=3 sliceTest =", sliceTest)
	}()

	func() {
		// string 은 변경불가능하기때문에 byte 슬라이스로 변환해서 변경하도록한다.
		str := "ysoftman"
		fmt.Printf("str = %s\n", str)
		//	str[0] = "a" --> 스트링은 변경 불가능하기 때문에 컴파일 에러 발생
		strslice := []byte(str)
		fmt.Println("strslice = ", strslice, "len = ", len(strslice))
		fmt.Printf("strslice = %s\n", strslice)
		strslice[0] = 'Y'
		strslice[len(strslice)-1] = 'N'
		fmt.Println("strslice[0] = 'Y'")
		fmt.Println("strslice[len(strslice)-1] = 'N'")
		fmt.Printf("strslice = %s\n", strslice)
		str = string(strslice)
		fmt.Printf("str = string(strslice), str = %s\n", str)
	}()
}
