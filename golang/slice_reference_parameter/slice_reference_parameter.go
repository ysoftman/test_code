package main

import "fmt"

func main() {

	func() {

		aaa1 := []int{99, 100}
		fmt.Printf("aaa1(%p) cap(aaa1)%v : %v\n", &aaa1, cap(aaa1), aaa1)

		modifySliceVale(aaa1)
		// reference 으로 넘긴 slice 파라메터가 메모리 공간의 변화가 없다면 aaa1 의 메모리를 공유한다.
		fmt.Printf("aaa1(%p) cap(aaa1)%v : %v\n", &aaa1, cap(aaa1), aaa1)

		fmt.Println("-----")

		// reference 으로 넘긴 slice 파라메터가 새로운 메모리 공간으로 할당되면 aaa1 에는 영향이 없다.
		aaa2 := addSliceValue(aaa1)
		fmt.Printf("addSliceValue, aaa1(%p) cap(aaa1)%v : %v\n", &aaa1, cap(aaa1), aaa1)
		fmt.Printf("addSliceValue, aaa2(%p) cap(aaa2)%v : %v\n", &aaa2, cap(aaa2), aaa2)

		fmt.Println("-----")

		// reference 으로 넘긴 slice 파라메터 결과로 받기
		fmt.Printf("addSlicePointer aaa1(%p) cap(aaa1)%v : %v\n", &aaa1, cap(aaa1), aaa1)
		addSlicePointer(&aaa1)
		fmt.Printf("addSlicePointer aaa1(%p) cap(aaa1)%v : %v\n", &aaa1, cap(aaa1), aaa1)

		// map 크기가 변해도 최초 주소 공간이 변하지 않아 caller map과 같은 주소공간으로 유지(공유)된다.
		hashmap := map[int]int{0: 1}
		fmt.Printf("hashmap(%p) : %v\n", &hashmap, hashmap)
		modifyMapValue(hashmap)
		fmt.Printf("hashmap(%p) : %v\n", &hashmap, hashmap)
		addMapKeyValue(hashmap)
		fmt.Printf("hashmap(%p) : %v\n", &hashmap, hashmap)

	}()
}

func modifyMapValue(hm map[int]int) {
	hm[0] = 0
}
func addMapKeyValue(hm map[int]int) {
	hm[1] = 10
	for i := 0; i < 100; i++ {
		hm[i] = i
	}
}

// slice 파라메터는 구조체(포인터,len,cap)값을 받는다.
func modifySliceVale(s []int) {
	if len(s) >= 1 {
		// s 의 크기가 변경되지 않으면 파라메터 s 는 caller 의 메모리 공간을 그대로 사용(공유)한다.
		s[0] = 20
	}
	if len(s) >= 2 {
		s[1] = 30
	}
}

// slice 파라메터는 구조체(포인터,len,cap)값을 받는다.
func addSliceValue(s []int) []int {
	for i := 0; i < 10; i++ {
		fmt.Printf("s(%p) cap(s)%v : %v\n", &s, cap(s), s)
		// append() returns updated slice
		s = append(s, i)
	}
	// 이미 위서 append 새로운 메모리가 할당되어 파라메터일때의 s 와 다른 메모리 공간을 사용하여
	// 파라메터와 s 와 공유 되지 않는다.
	s[0] = 98
	// 업데이트된 slice 를 리턴해야 한다.
	return s
}

// * 로 &(reference) slice 파라메터를 받으면 역참조로 바로 업데이트 한다.
func addSlicePointer(s *[]int) {
	for i := 0; i < 10; i++ {
		// slice 가 reference 인경우
		// append 를 쓰려면 역참조로 slice 타입을 가리키도록 해야 한다.
		fmt.Printf("s(%p) cap(s)%v : %v\n", s, cap(*s), s)
		*s = append(*s, i)
	}
	(*s)[0] = 97
}
