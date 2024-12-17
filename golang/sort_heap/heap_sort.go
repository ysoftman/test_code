// author : ysoftman
// encoding : utf-8
// title : 힙 정렬(우선순위큐 priority_queue 를 이용한 정렬)
// quicksort 처럼 NlogN 이지만 상위 n개만 정렬할때 더 빠르게 정렬할 수 있다.

package main

import (
	"fmt"
	"math/rand"
	"sort"
	"time"
)

const MaxLimit = 1000

/*
오름차순은 min 부모로 하는 heap (여기선 min-heap 사용)
내림차순은 max 부모로 하는 heap
min-heap 은 다음과 같은 이진트리지만 값은 리스트(슬라이스)로 저장한다.
     1
  2     3
4  5   6  7
=> [1,2,3,4,5,6,7]
idx[0,1,2,3,4,5,6]

인덱스가 0부터 시작일 경우
부모 인덱스 = (자식인덱스-1)/2
왼쪽 자식 인덱스 = 부모인덱스*2+1
오른쪽 자식 인덱스 = 부모인덱스*2+1+1
*/

func insert(nums *[]int, n int) {
	// 마지막(노드)에 값 추가
	*nums = append(*nums, n)
	child := len(*nums) - 1
	parent := (child - 1) / 2
	// 부모값 보다 작으면 자식과 값변경, 루트까지 반복해 min-heap 을 유지한다.
	for parent >= 0 {
		if (*nums)[parent] > (*nums)[child] {
			(*nums)[parent], (*nums)[child] = (*nums)[child], (*nums)[parent]
			child = parent
			parent = (child - 1) / 2
		} else {
			break
		}
	}
	// fmt.Println(*nums)
}

func pop(nums *[]int) int {
	// 현재 root 노드값은 리턴하기 위해 저장해두고
	r := (*nums)[0]
	// 마지막 노드를 root 옮긴다.
	(*nums)[0] = (*nums)[len(*nums)-1]
	*nums = (*nums)[:len(*nums)-1]
	// 자식 노드보다 값이 크면 자식노드와 값 변경, 말단 노드까지 반복해 min-heap 을 유지한다.
	parent := 0
	leftchild := parent*2 + 1
	rightchild := leftchild + 1
	for leftchild < len(*nums) {
		// 왼쪽, 오른쪽 자식 노드 둘다 있다면 둘 중 작은쪽(max-heap이면 큰쪽)과 비교한다.
		child := leftchild
		if rightchild < len(*nums) && (*nums)[rightchild] < (*nums)[leftchild] {
			child = rightchild
		}

		if (*nums)[child] < (*nums)[parent] {
			(*nums)[child], (*nums)[parent] = (*nums)[parent], (*nums)[child]
			parent = child
			leftchild = parent*2 + 1
			rightchild = leftchild + 1
		} else {
			break
		}
	}
	// fmt.Println(*nums)
	return r
}

func heapSort(nums []int) []int {
	heap := []int{}
	// 값을 추가하면 min-heap 을 유지하고 root 에는 가장 작은값이 위치
	for i := 0; i < len(nums); i++ {
		insert(&heap, nums[i])
	}

	// root 값을 빼오는데로 결과에 넣으면 내림차순 정렬
	// 빈 root 자리는 마지막 노드를 가져와 다시 min-heap 을 유지
	result := []int{}
	for len(heap) > 0 {
		result = append(result, pop(&heap))
	}
	return result
}

func main() {
	// 테스트를 위한 랜덤 리스트(슬라이스)와 정답 생성
	nums := make([]int, MaxLimit)
	rand.Seed(time.Now().Unix())
	for i := 0; i < MaxLimit; i++ {
		nums[i] = rand.Intn(MaxLimit)
	}
	answer := make([]int, MaxLimit)
	copy(answer, nums)
	sort.Ints(answer)
	// fmt.Println(nums)
	// fmt.Println(answer)
	// heapsort
	heapsort := heapSort(nums)
	// fmt.Println(heapsort)

	// 정렬이 잘 됐는지 정답과 비교
	// fmt.Println("checkSortResult:", checkSortResult(answer, answer))
	fmt.Println("checkSortResult:", checkSortResult(answer, heapsort))
}

func checkSortResult(a, b []int) bool {
	for i := 0; i < len(a); i++ {
		if a[i] != b[i] {
			return false
		}
	}
	return true
}
