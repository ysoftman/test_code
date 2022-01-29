// heap (최대 or 최소를 root 로 위치시키는 와전 이진트리 구조) 사용 테스트
// https://pkg.go.dev/container/heap#example-package-PriorityQueue
package main

import (
	"container/heap"
	"fmt"
)

type IntHeap []int

// Len, Less, Swap, Push, Pop 함수들을 구현해야 된다.
func (ih IntHeap) Len() int {
	return len(ih)
}

func (ih IntHeap) Less(i, j int) bool {
	return ih[i] < ih[j]
}

func (ih IntHeap) Swap(i, j int) {
	ih[i], ih[j] = ih[j], ih[i]
}

// slice 변경이 발생하기 때문에 포인터 receiver 를 사용한다.
func (ih *IntHeap) Push(ele interface{}) {
	*ih = append(*ih, ele.(int))
}

// slice 변경이 발생하기 때문에 포인터 receiver 를 사용한다.
func (ih *IntHeap) Pop() interface{} {
	old := *ih
	n := len(old)
	ele := old[n-1]
	*ih = old[0 : n-1]
	return ele
}

func main() {
	// ih := &IntHeap{2, 1, 5}
	ih := &IntHeap{5, 2, 3, 1, 8, 6, 4}
	// 1이 root 가 되도록 힙 상태 초기화
	heap.Init(ih)
	fmt.Println(*ih)
	// root 1 를 가져오기(제거) O(logN)
	fmt.Println("pop:", heap.Pop(ih))
	fmt.Println(*ih)
	// 1이 마지막 leaf 노느에 추가되고 부모노드와 자리르 바뀌면서 root 노드가 된다. O(logN)
	heap.Push(ih, 1)
	fmt.Println(*ih)
}
