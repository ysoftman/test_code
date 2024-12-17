// author : ysoftman
// encoding : utf-8
// title : 파일 삭제(rm)
package main

import (
	"log"
	"os"
	"fmt"
)

func main() {
	nArgs := len(os.Args)
	//	log.Println("len(os.Args[])= ", nArgs)
	// 삭제 대상이 지정되지 않으면 끝내기
	if nArgs != 2 {
		fmt.Println("삭제 대상이 지정되지 않았습니다.")
		os.Exit(1)
	}
	targetpath := os.Args[1]
	//	log.Println("exefile= ", os.Args[0])
	//	log.Println("targetpath= ", targetpath)
	fmt.Printf("erase target = %v\n", targetpath)

	// 대상 경로의 파일(디렉토리) 삭제
	err := os.RemoveAll(targetpath)
	if err != nil {
		log.Println(err.Error())
	}
}
