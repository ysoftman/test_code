// ysoftman
// rune (alias int32) 사용 테스트
package main

import (
	"bytes"
	"fmt"
)

func main() {
	printRune()
	cutRuneByMaxByte(7)
	cutRuneByMaxByte(13)
	cutRuneByMaxByte(17)
}

func printRune() {
	str := "이건 한글, This is English"
	fmt.Println(str)

	// golang 에서 str 은 utf8 이고, rune 은 4byte utf-8(한글 3byte)을 담는데 사용한다.
	// range 로 스트링에서 개별 룬문자와 개별 룬문자의 시작 위치(index) 알 수 있다.
	for index, runeValue := range str {
		fmt.Printf("index(%d) %v %U %#U\n", index, runeValue, runeValue, runeValue)
	}
}

func cutRuneByMaxByte(maxbytes int) {
	str := "이건 한글, This is English"
	fmt.Println(str, "(maxbytes:", maxbytes, ")")

	cutStr := ""
	var byteBuf bytes.Buffer
	preindex := 0
	for index, runeValue := range str {

		if index < maxbytes {
			preindex = index

			// 스트링이 커지면 += 효율성이 떨어지니 bytes.Buffer 를 사용하자.
			byteBuf.WriteRune(runeValue)
			fmt.Printf("index(%d) < maxbytes(%d) (%v)(%#U)\n", index, maxbytes, runeValue, runeValue)

		} else {
			break
		}
	}
	fmt.Printf("byteBuf: %v\n", byteBuf.String())

	cutStr = str[:preindex]
	fmt.Printf("preindex(%d) cutstr: %v\n", preindex, cutStr)

}
