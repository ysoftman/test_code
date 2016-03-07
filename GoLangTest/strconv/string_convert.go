// author : ysoftman
// encoding : utf-8
// title : strconv 패키지 테스트
package main

import "fmt"
import "os"
import "strconv"

func main() {
	fmt.Println("strconv test...")

	text := "ysoftman123"
	fmt.Println("text:", text)

	// convert string to int and binary
	nLen := len(text)
	for i := 0; i < nLen; i++ {
		n := int64(text[i])
		strBinary := strconv.FormatInt(n, 2)
		fmt.Printf("text: %c  integer: %v  binary: %v\n", text[i], n, strBinary)
        fmt.Fprintf(os.Stderr, "text: %c  integer: %v  binary: %v\n", text[i], n, strBinary)
	}

}
