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

	// Scanf 로 입력된 내용 스캔
	bufstring := ""
	fmt.Scanf("%s", &bufstring)
	fmt.Println("fmt.Scan(buf):", bufstring)

	// Scan() 사용 후 Buffer 사용하면 panic 발생하니 Scan 사용전 Buffer() 설정하자
	// Scan() 의 기본 버퍼는 MaxScanTokenSize = 64 * 1024 = 65535
	// MaxScanTokenSize 이상 사용하려면 Buffer 로 버퍼 크기를 설정하자
	buf := []byte{}
	scanner.Buffer(buf, 100000)

	// 단어(스페이스로 구분) 단위로 분리하여 스캔되는 모드로 변경
	scanner.Split(bufio.ScanWords)

	// stdin 으로 입력된 내용 스캔
	scanner.Scan()
	// MaxScanTokenSize = 64 * 1024 가 기본
	// scanner.Scan()
	// fmt.Println("scanner.Text():", scanner.Text())

	// 현재 스캐너에 들어온 내용 확인
	fmt.Println("scanner.Text() = ", scanner.Text())

	// stdin 으로 입력된 내용 스캔
	for scanner.Scan() {
		// 현재 스캐너에 들어온 내용 확인
		fmt.Println("scanner.Text() = ", scanner.Text())
	}
}
