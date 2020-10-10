// ysoftman
// textproto package 테스트
package main

import (
	"fmt"
	"net/textproto"
)

func main() {
	// CanonicalMIMEHeaderKey 는 첫 문자나 - 뒤에 첫문자만 대문자이고 나머지는 소문자로 컨버트한다.
	header := "Xabc-ABCD"
	fmt.Println(textproto.CanonicalMIMEHeaderKey(header))
	header = "xabc-abcd"
	fmt.Println(textproto.CanonicalMIMEHeaderKey(header))
	header = "xAbC-AcCd"
	fmt.Println(textproto.CanonicalMIMEHeaderKey(header))
}
