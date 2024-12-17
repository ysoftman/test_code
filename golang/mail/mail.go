// author : ysoftman
// encoding : utf-8
// title : mail 테스트
// mail 패키지는 메일 보내는 기능은 없고, 파싱 기능만 있다.
package main

import (
	"fmt"
	"net/mail"
	"strings"
	"log"
	"io/ioutil"
)

func main() {
	fmt.Println("parse mail...")
	mailmsg := `Date: Mon, 23 Jun 2015 11:40:36 -0400
From: bill, <bill@ysoftman.com>
To: jane <to@aaa.com>
Subject: 테스트 메일

테스트 메일입니다.
`
	maildata := strings.NewReader(mailmsg)
	msg, err := mail.ReadMessage(maildata)
	if err != nil {
		log.Fatal(err)
	}
	// 메일 헤더 파싱
	header := msg.Header
	fmt.Println("Date:", header.Get("Date"))
	from := header.Get("From")
	fmt.Println("From:", from)

	// 메일 주소 파싱해보기
	address := strings.Replace(from, ",", "", -1)
	f, err := mail.ParseAddress(address)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("(name:", f.Name, " address:", f.Address, ")")
	fmt.Println("To:", header.Get("To"))
	fmt.Println("Subject:", header.Get("Subject"))

	// 메일 내용
	body := msg.Body
	contents, err := ioutil.ReadAll(body)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("contents:%s", contents)
}
