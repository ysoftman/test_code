// ysoftman
// rune (alias int32) 사용 테스트
package main

import (
	"bytes"
	"fmt"
	"unicode/utf8"
)

func main() {
	// byte
	a := byte('a')
	fmt.Printf("type %T %v\n", a, a)
	// string len 은 string, slice, map, array 등은 되지만 byte, int32, rune 은 안된다.
	aa := "a"
	fmt.Printf("type %T %v %v\n", aa, aa, len(aa))
	// int32 == rune
	aaa := 'a'
	fmt.Printf("type %T %v\n", aaa, aaa)
	aaaa := rune('a')
	fmt.Printf("type %T %v\n", aaaa, aaaa)

	printRune()
	cutRuneByMaxByte(7)
	cutRuneByMaxByte(13)
	cutRuneByMaxByte(17)
}

func printRune() {
	str := "이건 한글, This is English"
	fmt.Println(str)
	// byte 기준 글자 개수
	fmt.Println("len(str):", len(str))
	// rune 기준 글자 개수
	fmt.Println("utf8.RuneCountInString(str):", utf8.RuneCountInString(str))

	// golang 에서 str 은 utf8 이고, str 의 각 요소는 rune 타입이다.
	// rune 은 int32(4bytes) alias 로, utf-8(영어 1byte, 한글 3bytes 1~4바이트 차지)을 담는데 사용한다.
	// range 로 스트링에서 개별 룬문자와 개별 룬문자의 시작 위치(index) 알 수 있다.
	for index, runeValue := range str {
		fmt.Printf("index(%d) %T %v %U %#U len(string(%d))\n", index, runeValue, runeValue, runeValue, runeValue, len(string(runeValue)))
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
