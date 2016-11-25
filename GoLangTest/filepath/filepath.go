// ysoftman
// filepath 패키지 테스트
package main

import (
	"fmt"
	"os"
	"path/filepath"
)

func main() {
	fmt.Println("filepath test")
	fmt.Println("os.Args[0]=" + os.Args[0])

	// filepath 함수 사용해보기
	// 절대 경로
	abspath, _ := filepath.Abs(os.Args[0])
	fmt.Println("abspath=" + abspath)
	// 디렉토리 경로
	dir := filepath.Dir(os.Args[0])
	fmt.Println("dir=" + dir)
	// dir, file 구분
	splitdir, splitfile := filepath.Split(os.Args[0])
	fmt.Println("splitdir=" + splitdir)
	fmt.Println("splitfile=" + splitfile)
}
