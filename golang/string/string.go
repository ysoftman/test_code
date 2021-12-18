// author : ysoftman
// encoding : utf-8
// title : string 테스트
package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {

	func() {
		fmt.Println("-----")
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
		strslice[3] = '_'
	}()

	func() {
		fmt.Println("-----")
		str := "ysoftman ysoftman\tysoftman"
		strslice := []byte(str)
		strslice[3] = '_'
		// Replace 함수의 마지막 인자(n) 은 교체 횟수 제한을 뜻한다.
		// n 문자열의 앞에서부터 교체할 수 있는 회수를 정한다
		// n < 0 인경우 교체 회수에 제한을 두지 않는다.
		str2 := strings.Replace(string(str), "_", "", -1)
		fmt.Printf("str = %s\n", str)
		fmt.Printf("str2 = %s\n", str2)
		str2 = strings.Replace(str2, "\t", "", -1)
		fmt.Printf("str2 = %s\n", str2)
		str2 = strings.Replace(str2, " ", "", -1)
		fmt.Printf("str2 = %s\n", str2)
	}()

	func() {
		fmt.Println("-----")
		str := "ysoftman ysoftman\tysoftman"
		strslice := []byte(str)
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
	}()

	func() {
		fmt.Println("-----")
		str1 := []string{"apple", "lemon", "orange"}
		// 스트링 배열의 값이 복사된다.
		str2 := str1
		// 스트링 배열의 참조만 복사된다.(str1 이 바뀌면 str3 도 바뀐다.)
		str3 := &str1
		str1 = append(str1, "milke")
		fmt.Printf("str1 = %s\n", str1)
		fmt.Printf("str2 = %s\n", str2)
		fmt.Printf("str3 = %s\n", str3)
	}()

	func() {
		fmt.Println("-----")
		str1 := []string{"1", "2", "3", "4"}
		str2 := []string{"4", "3", "2", "1"}
		str1 = append(str1, "5")
		str2 = append(str2, "5")
		fmt.Println("str1:", str1)
		fmt.Println("str2:", str2)
		// calculate (digit string slice)
		num1, _ := strconv.Atoi(strings.Join(str1, ""))
		num2, _ := strconv.Atoi(strings.Join(str2, ""))
		fmt.Println("num1+num2:", num1+num2)
	}()
}
