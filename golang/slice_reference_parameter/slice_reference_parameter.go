package main

import "fmt"

func main() {

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
