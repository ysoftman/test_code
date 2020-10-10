package main

import (
	"fmt"
	"strings"
)

func main() {
	s := "menu-menu-apple-menu-juice-ordered-ordered"
	// 앞에서 부터 첫번째 menu- 전체 일치 되는 부분만 삭제
	fmt.Println(strings.TrimPrefix(s, "menu-"))

	// 앞에서 부터 menu- 문자들중 일치되는 부분까지 삭제
	fmt.Println(strings.TrimLeft(s, "menu-"))

	// 뒤에서 부터 첫번째 -ordered 일치 되는 부분만 삭제
	fmt.Println(strings.TrimSuffix(s, "-ordered"))

	// 뒤에서부터 -ordered 문자들중 일치되는 부분까지 삭제
	fmt.Println(strings.TrimRight(s, "-ordered"))

	// index 를 찾아 apple-muenu-juice 내용만 가져오기
	first := strings.Index(s, "menu-menu-")
	last := strings.LastIndex(s, "-ordered-ordered")
	fmt.Println(s[first+len("menu-menu-") : last])
}
