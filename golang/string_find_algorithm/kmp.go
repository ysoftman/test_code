// ysoftman
// kmp 알고리즘
package main

import (
	"fmt"
)

// KMP(Knuth–Morris–Pratt 세사람의 이름을딴 문자열 검색(패턴 찾기)) algorithm
// 시간 복잡도 : O(m+n)
// s[i] 와 w[j] 를 비교해가면서 다른 부분이 나오면
// 현재까지 비교한 w부분문자열에 해당하는 실패함수의 값으로 이동(점프)해서 불필요한 비교 루프를 줄인다.
func kmp(s, w string) (indexes []int, results []string) {
	sl := len(s)
	wl := len(w)
	failp := failFunction(w)
	fmt.Println("failFunction:", failp)
	// word 의 비교 위치
	j := 0
	for i := 0; i < sl; i++ {
		// 불일치하면 현재위치에 해당하는 w의 부분문자열에 해당하는 실패함수결과에 따라 j 이동(점프)
		for j > 0 && s[i] != w[j] {
			j = failp[j-1]
		}
		if s[i] == w[j] {
			if j == wl-1 {
				// word 가 모두 매칭되었다면
				// 현재 찾은것 저장하고 문장 또 나올 수 있으니 계속 찾기
				indexes = append(indexes, i-(wl-1))
				results = append(results, s[i-(wl-1):(i-(wl-1))+wl])
				j = failp[j]
				// 맨 처음 매칭된 문자열만 찾고 끝내기
				// return indexes, results
			} else {
				// word 매칭이 완료되지 않았으면 계속 매칭하기 위해서 j 하나 이동
				j++
			}
		}
	}
	return indexes, results
}

// 실패 함수 : kmp 에서 word 가 매칭되지 않는 지점에서 얼마만큼 이동해야하는지 표시
// 실패 함수 자체도 kmp 와 같은 방식으로 이미 작성된 실패함수로 부터 이동위치를 참고한다.
func failFunction(w string) (failp []int) {
	wl := len(w)
	failp = make([]int, wl, wl)
	// word 의 부분 문자열 마다 prefix == suffix 일때 가장 긴 길이
	// ex) abcabc 의 부분문자열의 각 prefix == suffix 최대 길이
	// a -> 0
	// ab -> 0
	// abc -> 0
	// abca -> 1
	// abcab -> 2
	// abcabc -> 3
	j := 0
	for i := 1; i < wl; i++ {
		fmt.Printf("w[%d]:%s, w[%d]:%s\n", i, w[:i+1], j, w[:j+1])
		// 불일치하면 현재위치에 해당하는 w의 부분문자열에 해당하는 실패함수결과에 따라 j 이동(점프)
		for j > 0 && w[i] != w[j] {
			j = failp[j-1]
		}
		if w[i] == w[j] {
			j++
			failp[i] = j
		}
	}
	return failp
}
