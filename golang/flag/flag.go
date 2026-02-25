// ysoftman
// flag 사용 테스트
package main

import (
	"flag"
	"fmt"
)

func main() {
	fmt.Println("flag test...")
	// 플래스(옵션)명이 틀리거나하면 usage 문구와
	// 각 옵션별 사용예시문구(디폴트값)가 출력된다.
	// 문자열을 옵션 -a 설정, 디폴트값, 사용예시
	a := flag.String("a", "abc", "-a abc")
	// 정수형 옵션 -b 설정, 디폴트값, 사용예시
	b := flag.Int("b", 999, "-b 999")
	// time.Duration(int64, nanosecond) 옵션 -c 설정
	c := flag.Duration("c", 100, "-c 100")
	d := flag.Bool("d", false, "false|true")
	// flag 에 설정된 값들 파싱하기
	flag.Parse()

	fmt.Printf("a=%s\n", *a)
	fmt.Printf("b=%d\n", *b)
	fmt.Println("c=", *c)
	fmt.Println("d=", *d)

	getFlag()
}

func getFlag() {
	fmt.Println("getFlag a:", flag.Lookup("a").Value.String())
	fmt.Println("getFlag b:", flag.Lookup("b").Value.String())
	fmt.Println("getFlag c:", flag.Lookup("c").Value.String())
	fmt.Println("getFlag d:", flag.Lookup("d").Value.String())
}
