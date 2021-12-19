package main

import (
	"fmt"
)

type Dummy struct {
	strlist []string
}

func main() {
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
}
