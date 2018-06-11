// ysoftman
// 문자열 찾기 알고리즘 테스트
package main

// 그냥 쉽게 생각할 수 있는 naive 문자열 매칭
// 시간 복잡도 : O(mn)
func simpleFind(s, w string) (idx int, result string) {
	sl := len(s)
	wl := len(w)
	for i := 0; i < sl; i++ {
		bFind := true
		// 단순히 한칸씩 이동하면 맞는 스트링이 나올때까지 반복
		for j := 0; j < wl; j++ {
			if w[j] != s[i+j] {
				bFind = false
				break
			}
		}
		if bFind {
			return i, s[i : i+wl]
		}
	}
	return -1, ""
}
