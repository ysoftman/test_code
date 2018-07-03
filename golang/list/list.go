// ysoftman
// list 컨테이너 테스트

package main

import (
	"container/list"
	"fmt"
)

func main() {
	mylist := list.New()
	// 리스트 끝에 추가
	mylist.PushBack("aaa")
	mylist.PushBack(111)
	// 리스트 처음에 추가
	el := mylist.PushFront(222)
	// el 앞에 추가
	mylist.InsertBefore(333, el)
	// fmt.Println(mylist)
	for iter := mylist.Front(); iter != nil; iter = iter.Next() {
		fmt.Println(iter.Value)
	}
}
