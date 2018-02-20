package main

import (
	"bytes"
	"fmt"

	"golang.org/x/text/encoding/korean"
	"golang.org/x/text/transform"
)

func main() {
	msg := "this is test, 이건 테스트 문자입니다."
	fmt.Println("msg(utf8):", msg)

	var byteBuffer bytes.Buffer
	euckrEncoder := transform.NewWriter(&byteBuffer, korean.EUCKR.NewEncoder())
	euckrEncoder.Write([]byte(msg))
	euckrEncoder.Close()
	fmt.Println("[utf8->euckr]")
	fmt.Println(byteBuffer.String())
	fmt.Printf("%x\n", byteBuffer.Bytes())

	var byteBuffer2 bytes.Buffer
	euckrDecoder := transform.NewWriter(&byteBuffer2, korean.EUCKR.NewDecoder())
	euckrDecoder.Write([]byte(byteBuffer.String()))
	euckrDecoder.Close()
	fmt.Println("[euckr->utf8]")
	fmt.Println(byteBuffer2.String())
	fmt.Printf("%x\n", byteBuffer2.Bytes())
}
