// go test -bench=.
package main

import (
	"testing"
)

// const MAX = 100
const MAX = 1000

var s []int

func BenchmarkPrepareSlice(*testing.B) {
	s = make([]int, 0)
	for i := 0; i < MAX; i++ {
		s = append(s, i)
	}
}

func BenchmarkSlice(*testing.B) {
	for target := 0; target < MAX; target++ {
		for i := 0; i < MAX; i++ {
			if s[i] == target {
				// fmt.Println("[slice] found ", i)
			}
		}
	}
}

func BenchmarkMap(*testing.B) {
	// 데이터 개수가 작으면 slice -> map 변경하는 시간때문에 비효율적이다.
	m := make(map[int]int)
	for k, v := range s {
		m[k] = v
	}
	for i := 0; i < MAX; i++ {
		if _, ok := m[i]; ok {
			// fmt.Println("[map] found ", i)
		}
	}
}
