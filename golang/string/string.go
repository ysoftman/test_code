// author : ysoftman
// encoding : utf-8
// title : string 테스트
package main

import (
	"fmt"
	"strings"
)

func main() {

	// string 은 변경불가능하기때문에 byte 슬라이스로 변환해서 변경하도록한다.
	str := "ysoftman ysoftman\tysoftman"
	//	str[0] = "a" --> 스트링은 변경 불가능하기 때문에 컴파일 에러 발생
	strslice := []byte(str)

	fmt.Println("strslice = ", strslice, "len = ", len(strslice))
	fmt.Printf("str = %s\n", str)
	fmt.Printf("strslice = %s\n", strslice)
	strslice[0] = 'Y'
	strslice[len(strslice)-1] = 'N'
	fmt.Printf("str = %s\n", str)
	fmt.Printf("strslice = %s\n", strslice)

	// 스트링 값 삭제
	strslice[3] = '_'
	// Replace 함수의 마지막 인자(n) 은 교체 횟수 제한을 뜻한다.
	// n 문자열의 앞에서부터 교체할 수 있는 회수를 정한다
	// n < 0 인경우 교체 회수에 제한을 두지 않는다.
	str2 := strings.Replace(string(strslice), "_", "", -1)
	fmt.Printf("strslice = %s\n", strslice)
	fmt.Printf("str2 = %s\n", str2)

	str2 = strings.Replace(str2, "\t", "", -1)
	fmt.Printf("str2 = %s\n", str2)
	str2 = strings.Replace(str2, " ", "", -1)
	fmt.Printf("str2 = %s\n", str2)

	// 스트링 복제(슬라이스는 기본 참조라서 같이 변경된다.)
	strcopy := strslice
	strcopy[1] = 'S'
	fmt.Printf("strslice = %s\n", strslice)
	fmt.Printf("strcopy = %s\n", strcopy)

	// 스트링 복제(make 로 공간을 생성한다음 copy 로 복사)
	strcopy = make([]byte, len(strslice))
	copy(strcopy, strslice)
	strcopy[1] = '!'
	fmt.Printf("strslice = %s\n", strslice)
	fmt.Printf("strcopy = %s\n", strcopy)

}
