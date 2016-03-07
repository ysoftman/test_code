// author : ysoftman
// encoding : utf-8
// title : strconv 패키지 테스트
package main

import "fmt"
import "os"
import "strconv"

func main() {
	fmt.Println("strconv test...")

	text := "ysoftman123!@#"
	fmt.Println("text:", text)

	// convert string to int and binary
	nLen := len(text)
	for i := 0; i < nLen; i++ {
		n := int64(text[i])
		temp := strconv.FormatInt(n, 2)
		strBinary := ""
		// 7비트로 맞추기
		if len(temp) < 7 {
			for i := 0; i < 7-len(temp); i++ {
				strBinary += "0"
			}
		}
		strBinary += temp
		fmt.Fprintf(os.Stderr, "text: %c  integer: %3v  binary: %7v\n", text[i], n, strBinary)
	}
}
