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
		copy(dummy2.strlist, dummy1.strlist)
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
		// 5길이를 가진 배열 생성
		arrayTest := [5]int{11, 22, 33, 44, 55}
		fmt.Println("arrayTest len:", len(arrayTest), "arrayTest cap:", cap(arrayTest), "arrayTest:", arrayTest)
		// 배열은 추가할 수 없다.
		// arrayTest = append(arrayTest, 9)
		// fmt.Println("append", arrayTest)
	}()

	func() {
		// variadic 으로 배열 생성
		// ... 파라미터는 variadic 으로, 0 이상의 파라미터가 올수 있다는 의미
		// https://golang.org/ref/spec#Function_types
		// [...] 로 구체적 원소개수를 명시하지 않아도 된다.
		arrayTest := [...]int{11, 22, 33, 44, 55}
		// 슬라이스 크기가 고정되어 있어 자기 자신에게 append 사용할 수 없다.
		// arrayTest = append(arrayTest, 6, 7)
		fmt.Println("arrayTest len:", len(arrayTest), "arrayTest cap:", cap(arrayTest), "arrayTest:", arrayTest)
		// 배열은 추가할 수 없다.
		// arrayTest = append(arrayTest, 9)
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

	func() {
		// string 은 변경불가능하기때문에 byte 슬라이스로 변환해서 변경하도록한다.
		str := "ysoftman"
		fmt.Printf("str: %s\n", str)
		//	str[0]:"a" --> 스트링은 변경 불가능하기 때문에 컴파일 에러 발생
		strslice := []byte(str)
		fmt.Println("strslice:", strslice, "len:", len(strslice))
		fmt.Printf("strslice = %s\n", strslice)
		strslice[0] = 'Y'
		strslice[len(strslice)-1] = 'N'
		fmt.Println("strslice[0]: 'Y'")
		fmt.Println("strslice[len(strslice)-1]: 'N'")
		fmt.Printf("strslice: %s\n", strslice)
		str = string(strslice)
		fmt.Printf("str: string(strslice), str: %s\n", str)
	}()

	func() {
		aaa := []int{99, 100}
		// reference 으로 넘긴 slice 파라미터 결과로 받기
		fmt.Printf("addInt1 aaa(%p) cap(aaa)%v : %v\n", &aaa, cap(aaa), aaa)
		aaa = addInt1(aaa)
		fmt.Printf("addInt1 aaa(%p) cap(aaa)%v : %v\n", &aaa, cap(aaa), aaa)
		// reference 으로 넘긴 slice 파라미터 결과로 받기
		fmt.Printf("addInt2 aaa(%p) cap(aaa)%v : %v\n", &aaa, cap(aaa), aaa)
		addInt2(&aaa)
		fmt.Printf("addInt2 aaa(%p) cap(aaa)%v : %v\n", &aaa, cap(aaa), aaa)
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

// slice 구조체(포인터,len,cap)값을 받는다.
func addInt1(s []int) []int {
	for i := 0; i < 10; i++ {
		fmt.Printf("s(%p) cap(s)%v : %v\n", &s, cap(s), s)
		// append() returns updated slice
		s = append(s, i)
	}
	// 업데이트된 slice 를 리턴해야 한다.
	return s
}

// * 로 &(reference) 값을 받으면 역참조로 바로 업데이트 한다.
func addInt2(s *[]int) {
	for i := 0; i < 10; i++ {
		// slice 가 reference 인경우
		// append 를 쓰려면 역참조로 slice 타입을 가리키도록 해야 한다.
		fmt.Printf("s(%p) cap(s)%v : %v\n", s, cap(*s), s)
		*s = append(*s, i)
	}
}
