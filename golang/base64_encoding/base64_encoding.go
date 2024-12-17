// author : ysoftman
// encoding : utf-8
// title : base64 인코딩 테스트
package main

import (
	"fmt"
	"os"
	"encoding/base64"
)

const strURL string = "http://www.google.com"

func main() {
	fmt.Println("encoding decoding test...")
	fmt.Fprintf(os.Stdout, "%s\n", strURL)

	// base64 StdEncoding 를 이용한 인코딩
	buffer := []byte(strURL)
	output := base64.StdEncoding.EncodeToString(buffer)
	fmt.Fprintf(os.Stdout, "%s\n", output)

	// base64 URLEncoding 를 이용한 인코딩
	output = base64.URLEncoding.EncodeToString(buffer)
	fmt.Fprintf(os.Stdout, "%s\n", output)

	// base64 StdEncoding 를 이용한 디코딩
	output2, err := base64.StdEncoding.DecodeString(output)
	if err != nil {
		fmt.Fprintf(os.Stderr, "error : %s\n", err.Error())
		os.Exit(1)
	}
	fmt.Fprintf(os.Stdout, "%s\n", output2)
}
