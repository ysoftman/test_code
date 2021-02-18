// author : ysoftman
// encoding : utf-8
// title : strconv 패키지 테스트
package main

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	fmt.Println("strconv test...")

	num := int64(100)
	fmt.Println("num:", num)
	fmt.Println("formatInt(num, base16):", strconv.FormatInt(num, 16))
	fmt.Println("formatInt(num, base10):", strconv.FormatInt(num, 10))
	fmt.Println("formatInt(num, base8):", strconv.FormatInt(num, 8))
	fmt.Println("formatInt(num, base5):", strconv.FormatInt(num, 5))
	fmt.Println("formatInt(num, base2):", strconv.FormatInt(num, 2))

	text := "ysoftman123!@#"
	fmt.Println("text:", text)

	// convert string to int and binary
	nLen := len(text)
	for i := 0; i < nLen; i++ {
		integer := int64(text[i])
		temp := strconv.FormatInt(integer, 2)
		strBinary := ""
		// 7비트 7자리로 맞추기(앞부분 0 으로 패딩)
		// if len(temp) < 7 {
		// 	for i := 0; i < 7-len(temp); i++ {
		// 		strBinary += "0"
		// 	}
		// }
		// strBinary += temp
		strBinary = temp
		fmt.Fprintf(os.Stderr, "text: %c  integer: %3v  binary: %07v\n", text[i], integer, strBinary)
	}
}
