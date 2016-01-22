// author : ysoftman
// encoding : utf-8
// title : os 패키지 테스트
package main

import (
	"fmt"
	"os"
)

func main() {
	// 현재 워킹 디렉토리
	cur_dir, _ := os.Getwd()
	fmt.Println("current directory =", cur_dir)

	// 워킹 디렉토리 변경
	err := os.Chdir("../")
	if err != nil {
		fmt.Println(err.Error())
	}
	cur_dir, _ = os.Getwd()
	fmt.Println("current directory =", cur_dir)

	// 인자 정보
	fmt.Println("Args =", len(os.Args))
	for i := 0; i < len(os.Args); i++ {
		fmt.Printf("Arg[%v] = %v", i, os.Args[i])
	}

	fmt.Println()
	// 0 > 경우 비정상 종료로 처리
	//	os.Exit(-1)
	// 정상종료로 처리
	os.Exit(0)

}
