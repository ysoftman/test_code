// author : ysoftman
// encoding : utf-8
// title : hijack 테스트

package main

import (
	"fmt"
	"net/http"
)

func main() {
	// curl -v http://localhost:8080/test
	// 일반적인 http 응답
	http.HandleFunc("/normal", func(w http.ResponseWriter, r *http.Request) {
		w.Write([]byte("this is test\n"))
	})

	// curl -v http://localhost:8080/hijack -X POST -d "ysoftman
	// hijack 으로 응답 변경
	http.HandleFunc("/hijack", func(w http.ResponseWriter, r *http.Request) {
		// http responsewrite 를 hijacker 로 사용
		// 이제 부터는 hijack 방시기으로 응답을 처리한다.
		hj, err := w.(http.Hijacker)
		if !err {
			return
		}
		// hijack 으로 커넥션, 응답버퍼를 가져온다.
		conn, buff, err2 := hj.Hijack()
		if err2 != nil {
			fmt.Println("error:", err)
			return
		}
		defer conn.Close()

		// 클라이언트가 요청한 data "ysoftman" 가 reader 에 있어 가져올 수 있다.
		var ss []byte
		ss = make([]byte, 100, 100)
		buff.Read(ss)
		fmt.Println(string(ss))

		// http (헤더, 바디) 대신 커스텀 데이터를 기록한다.
		// 응답 데이터 쓰기 방법1 - buff Writer 에 쓰기
		buff.WriteString("hijaking... aaa\n")
		buff.Flush()
		// 응답 데이터 쓰기 방법2
		conn.Write([]byte("hijacking... bbbbb\n"))
	})

	http.ListenAndServe(":8080", nil)
}
