// ysoftman
// list 컨테이너 테스트

package main

import (
	"container/list"
	"fmt"
)

func main() {
	mylist := list.New()
	mylist.PushBack("aaa")
	mylist.PushBack(111)
	el := mylist.PushFront(123)
	mylist.InsertBefore(222, el)
	// fmt.Println(mylist)
	for iter := mylist.Front(); iter != nil; iter = iter.Next() {
		fmt.Println(iter.Value)
	}
}
