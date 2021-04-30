// ysoftman
// pprof 사용 테스트
package main

import (
	"fmt"
	"log"
	"net/http"
	_ "net/http/pprof"
	"time"
)

func main() {
	go func() {
		log.Println(http.ListenAndServe("localhost:6060", nil))
	}()
	for {
		time.Sleep(100 * time.Millisecond)
		fmt.Println("ysoftman")
	}
	select {}
}

// pprof.go init()에 이미 다음과 핸들러 들이 등록되 있어 별도 핸들러 등록을 하지 않는다.
// 만약 /debug/pprof/trace 등을 별도구 선언하면 실행 후 다운로드하려하면 404 NOT FOUND 가 발생한다.
// func init() {
// 	http.Handle("/debug/pprof/", http.HandlerFunc(Index))
// 	http.Handle("/debug/pprof/cmdline", http.HandlerFunc(Cmdline))
// 	http.Handle("/debug/pprof/profile", http.HandlerFunc(Profile))
// 	http.Handle("/debug/pprof/symbol", http.HandlerFunc(Symbol))
// 	http.Handle("/debug/pprof/trace", http.HandlerFunc(Trace))
// }
// 참고 https://stackoverflow.com/questions/30560859/cant-use-go-tool-pprof-with-an-existing-server
