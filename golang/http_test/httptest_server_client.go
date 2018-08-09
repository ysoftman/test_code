// author : ysoftman
// encoding : utf-8
// title : httptest 사용하기
package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"net/http/httptest"
)

func makeMockup() *httptest.Server {
	// 테스트를 위한 http 서버 생성
	httpserver := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintln(w, "ysoftman response")
	}))

	fmt.Printf("[httptest server] %s running...\n", httpserver.URL)
	return httpserver
}

func main() {
	hs := makeMockup()
	defer hs.Close()

	// 테스트 http 서버에 get 요청
	resp, err := http.Get(hs.URL)
	if err != nil {
		log.Fatal(err)
	}
	// httpserver 응답 확인
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("[client]", string(body))
}
