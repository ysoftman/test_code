package main

import (
	"fmt"
	"strings"
)

func main() {
	s := "menu-menu-apple-menu-juice-ordered-ordered"
	// 앞 부터 첫번째 menu- 일치 되는 부분만 한번 삭제
	fmt.Println(strings.TrimPrefix(s, "menu-"))

	// 앞 부터 menu- 일치되는 부분들 (일치 되지 않을때까지) 모두 삭제한 곳 이후의 슬라이스 리턴 s[i:]
	fmt.Println(strings.TrimLeft(s, "menu-"))

	// 뒤 부터 첫번째 -ordered 일치 되는 부분만 한번 삭제
	fmt.Println(strings.TrimSuffix(s, "-ordered"))

	// 뒤 부터 -ordered 일치되는 부분들 (일치 되지 않을때까지) 모두 삭제한 곳 까지의 슬라이스 리턴 s[:i]
	// s[:i] 로 i번째 문자가 포함되지 않으니 주의
	fmt.Println(strings.TrimRight(s, "-ordered"))

	// -or 뒤쪽은 모두 삭제
	fmt.Println(strings.Split(s, "-or")[0])

	// index 를 찾아 apple-muenu-juice 내용만 가져오기
	first := strings.Index(s, "menu-menu-")
	last := strings.LastIndex(s, "-ordered-ordered")
	fmt.Println(s[first+len("menu-menu-") : last])
}
