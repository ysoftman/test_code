// heap (최대 or 최소를 root 로 위치시키는 완전 이진트리 구조) 사용 테스트
// https://pkg.go.dev/container/heap#example-package-PriorityQueue
package main

import (
	"container/heap"
	"fmt"
	"math/rand"
)

type MinHeap []int

// Len, Less, Swap, Push, Pop 함수들을 구현해야 된다.
func (h MinHeap) Len() int {
	return len(h)
}

func (h MinHeap) Less(i, j int) bool {
	// return h[i] > h[j]  이면 최대힙
	return h[i] < h[j]
}

func (h MinHeap) Swap(i, j int) {
	h[i], h[j] = h[j], h[i]
}

// slice 변경이 발생하기 때문에 포인터 receiver 를 사용한다.
func (h *MinHeap) Push(ele interface{}) {
	*h = append(*h, ele.(int))
}

// slice 변경이 발생하기 때문에 포인터 receiver 를 사용한다.
func (h *MinHeap) Pop() interface{} {
	// Pop() 은 다음 과정을 거친후 호출된다.(container/heap/heap.go Pop interface 참고)
	// 1. 단순히 배열의 첫 번째 요소를 제거하면 나머지 모든 요소를 한 칸씩 앞으로 당겨야 하는 O(n)의 비용이 발생하기 때문에, 힙의 효율성을 유지하기 위해 Swap(0, n-1) 한다.
	// 2. Down/Fix(0, n-1)로 힙을 재정렬한다.
	// fmt.Println("heap: ", *h)
	old := *h
	n := len(old)
	ele := old[n-1]
	*h = old[0 : n-1]
	return ele
}

func main() {
	h := &MinHeap{5, 2, 3, 1, 8, 6, 4}
	// 1이 root 가 되도록 힙 상태 초기화
	heap.Init(h)
	fmt.Println(*h)
	// root 1 를 가져오기(제거) O(logN)
	for h.Len() > 0 {
		fmt.Println("pop:", heap.Pop(h))
		fmt.Println(*h)
	}
	for range 10 {
		n := rand.Intn(15)
		// 마지막 leaf 노느에 추가되고 부모노드와 자리를 바뀌면서 root 노드가 된다. O(logN)
		fmt.Println("push:", n)
		heap.Push(h, n)
		fmt.Println(*h)
	}
}
