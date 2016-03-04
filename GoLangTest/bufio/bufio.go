// author : ysoftman
// encoding : utf-8
// title : bufio 패키지 테스트
package main

import "fmt"
import "bufio"
import "os"

func main() {
	// stdin 버퍼를 사용하는 스캐너 생성
	scanner := bufio.NewScanner(os.Stdin)

	// stdin 으로 입력된 내용 스캔
	scanner.Scan()
	// 현재 스캐너에 들어온 내용 확인
	fmt.Println("scanner.Text() = ", scanner.Text())

	// 단어(스페이스로 구분) 단위로 분리하여 스캔되는 모드로 변경
	scanner.Split(bufio.ScanWords)

	// stdin 으로 입력된 내용 스캔
	for scanner.Scan() {
		// 현재 스캐너에 들어온 내용 확인
		fmt.Println("scanner.Text() = ", scanner.Text())
	}
}
