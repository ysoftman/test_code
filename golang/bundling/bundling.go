// ysoftman
// js, html, css bundling(의존성등을 고려한 패키징) 테스트
package main

import (
	"net/http"

	rice "github.com/GeertJohan/go.rice"
)

func main() {
	// 일반적인 웹서버를 띄우는 경우
	// http://localhost:8080/web/  --> 404 page not found 발생
	// http://localhost:8080/web/sample.html 식으로 해당 리소스만 접근
	// http://localhost:8080/web/sample.js 식으로 해당 리소스만 접근
	// http://localhost:8080/web/sample.css --> 404 page not found
	// http.Handle("/web/.", http.StripPrefix("/src/", http.FileServer(http.Dir("./src"))))
	// http.ListenAndServe(":8080", nil)

	// 번들링하여 웹서버를 띄우는 경우
	// http://localhost:8080/web/ 으로 /src 내의 모든 정적 리소스 액세스 할 수 있다.
	box := rice.MustFindBox("src")
	staticFileServer := http.StripPrefix("/web/", http.FileServer(box.HTTPBox()))
	http.Handle("/web/", staticFileServer)
	http.ListenAndServe(":8080", nil)
}
