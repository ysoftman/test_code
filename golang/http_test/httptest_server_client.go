// author : ysoftman
// encoding : utf-8
// title : httptest 사용하기
package main

import (
	"fmt"
	"io"
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

func makeMockup2() *httptest.Server {
	// 테스트를 위한 http 서버 생성
	httpserver := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintln(w, "ysoftman2 response")
	}))

	fmt.Printf("[httptest server] %s running...\n", httpserver.URL)
	return httpserver
}

func makeMockupMux() *httptest.Server {
	mux := http.NewServeMux()
	mux.HandleFunc("/path1", http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintln(w, "path1 response")
	}))
	mux.HandleFunc("/path2", http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintln(w, "path2 response")
	}))
	// 테스트를 위한 http 서버 생성
	httpserver := httptest.NewServer(mux)

	fmt.Printf("[httptest server(mux)] %s running...\n", httpserver.URL)
	return httpserver
}

func main() {
	ht := makeMockup()
	defer ht.Close()
	// 테스트 http 서버에 get 요청
	resp, _ := http.Get(ht.URL)
	body, _ := io.ReadAll(resp.Body)
	fmt.Println("[client]", string(body))

	ht2 := makeMockup2()
	defer ht2.Close()
	resp2, _ := http.Get(ht2.URL)
	body2, _ := io.ReadAll(resp2.Body)
	fmt.Println("[client]", string(body2))

	htmux := makeMockupMux()
	defer htmux.Close()
	respmux, _ := http.Get(htmux.URL + "/path1")
	bodymux, _ := io.ReadAll(respmux.Body)
	fmt.Println("[client]", string(bodymux))
	respmux, _ = http.Get(htmux.URL + "/path2")
	bodymux, _ = io.ReadAll(respmux.Body)
	fmt.Println("[client]", string(bodymux))
}
