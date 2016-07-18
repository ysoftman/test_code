// ysoftman
// flag 사용 테스트
package main

import (
	"flag"
	"fmt"
)

func main() {
	fmt.Println("flag test...")

	// 문자열을 옵션 -a 설정, 디폴트값, 사용예시
	a := flag.String("a", "abc", "-a zzz")
	// 정수형 옵션 -b 설정, 디폴트값, 사용예시
	b := flag.Int("b", 1, "-b 999")

	// flag 에 설정된 값들 파싱하기
	flag.Parse()

	fmt.Printf("a=%s\n", *a)
	fmt.Printf("b=%d\n", *b)

	// 플래스(옵션)명이 틀리거나하면 usage 문구와
	// 각 옵션별 사용예시문구(디폴트값)가 출력된다.
}
