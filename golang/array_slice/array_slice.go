// author : ysoftman
// encoding : utf-8
// title : array slice 테스트
package main

import "fmt"

func main() {
	// 배열
	arTest0 := [5]int{11, 22, 33, 44, 55}
	fmt.Println("arTest0 len = ", len(arTest0), "arTest1 cap = ", cap(arTest0), "arTest1 = ", arTest0)

	// ... 파라미터는 variadic 으로 부고, 0 이상의 파라미터가 올수 있다는 의미
	// https://golang.org/ref/spec#Function_types
	// [...] 로 구체적 원소개수를 명시하지 않아도 된다.
	arTest1 := [...]int{11, 22, 33, 44, 55}
	arTest2 := []int{10, 20, 30}

	fmt.Println("arTest1 len = ", len(arTest1), "arTest1 cap = ", cap(arTest1), "arTest1 = ", arTest1)
	fmt.Println("arTest2 len = ", len(arTest2), "arTest2 cap = ", cap(arTest2), "arTest2 = ", arTest2)
	// for 로 해보기
	//	for i := 0; i < len(arTest1); i++ {
	//		fmt.Println("arTest1[", i, "] = ", arTest1[i])
	//	}
	// range 로 해보기
	for key, value := range arTest1 {
		fmt.Println("arTest1[", key, "] = ", value)
	}

	fmt.Println("arTest1[3:5]", arTest1[3:5])
	fmt.Println("arTest1[2:]", arTest1[2:])

	// 배열의 일정 부분을 가져와 슬라이스 형태로 참조
	arTest3 := arTest1[2:]

	fmt.Println("arTest3 len = ", len(arTest3), "arTest3 cap = ", cap(arTest3), "arTest3 = ", arTest3)

	// make 로 슬라이스 만들기
	// make 의 두번째 인자는 len, 세번째 인자는 cap 설정
	arTest4 := make([]int, 3, 5)
	fmt.Println("arTest4 len = ", len(arTest4), "arTest4 cap = ", cap(arTest4), "arTest4 = ", arTest4)

	// append 로 슬라이스에 추가하기
	arTest4 = append(arTest4, 1, 2, 3, 4, 5, 6, 7, 8, 9)
	fmt.Println("arTest4 len = ", len(arTest4), "arTest4 cap = ", cap(arTest4), "arTest4 = ", arTest4)

	// append 로 element 삭제하기
	// append 에서 ... 는 해당 타입의 모든(0 이상) 원소들을 의미
	arTest4 = append(arTest4[:3], arTest4[4:]...)
	fmt.Println("arTest4 len = ", len(arTest4), "arTest4 cap = ", cap(arTest4), "arTest4 = ", arTest4)

	// 슬라이스 참조
	arTest5 := arTest3
	fmt.Println("arTest5 len = ", len(arTest5), "arTest5 cap = ", cap(arTest5), "arTest4 = ", arTest5)
	// 참조하고 있는 슬라이스가 변경되면 같이 변경된다
	arTest4[0] = -1
	fmt.Println("arTest5 len = ", len(arTest5), "arTest5 cap = ", cap(arTest5), "arTest4 = ", arTest5)

	// 슬라이스 복사하기
	arTest6 := make([]int, 10, 10)
	// arTest6 의 cap 만큼 복사된다.
	copy(arTest6, arTest4)
	fmt.Println("arTest6 len = ", len(arTest6), "arTest6 cap = ", cap(arTest6), "arTest6 = ", arTest6)
	// 슬라이스 복사(독립된 메모리공간)로 영향이 없다
	arTest4[0] = -2
	fmt.Println("arTest4 len = ", len(arTest4), "arTest4 cap = ", cap(arTest4), "arTest4 = ", arTest4)
	fmt.Println("arTest6 len = ", len(arTest6), "arTest6 cap = ", cap(arTest6), "arTest6 = ", arTest6)

	fmt.Println("")
	// string 은 변경불가능하기때문에 byte 슬라이스로 변환해서 변경하도록한다.
	str := "ysoftman"
	//	str[0] = "a" --> 스트링은 변경 불가능하기 때문에 컴파일 에러 발생
	strslice := []byte(str)
	fmt.Println("strslice = ", strslice, "len = ", len(strslice))
	fmt.Printf("str = %s\n", str)
	fmt.Printf("strslice = %s\n", strslice)
	fmt.Println("strslice[0] = 'Y'")
	strslice[0] = 'Y'
	fmt.Println("strslice[len(strslice)-1] = 'N'")
	strslice[len(strslice)-1] = 'N'
	fmt.Printf("str = %s\n", str)
	fmt.Printf("strslice = %s\n", strslice)

	fmt.Printf("")
	arTest10 := []int{1, 2, 3, 4, 5}
	fmt.Println("arTest10 =", arTest10)

	// pop
	value, arTest10 := arTest10[0], arTest10[1:]
	fmt.Println("pop value =", value, " arTest10 =", arTest10)

	// pop-back
	value, arTest10 = arTest10[len(arTest10)-1], arTest10[:len(arTest10)-1]
	fmt.Println("pop-back value =", value, " arTest10 =", arTest10)

	// push
	value = 5
	arTest10 = append(arTest10, value)
	fmt.Println("push value =", value, " arTest10 =", arTest10)

	// push-front
	value = 1
	arTest10 = append([]int{value}, arTest10...)
	fmt.Println("push-front value =", value, " arTest10 =", arTest10)
}
