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

// pprof.go init()에 이미 다음과 핸들러 들이 등록되 있어 별도로 등록하지 않아도 된다.
// func init() {
// 	http.Handle("/debug/pprof/", http.HandlerFunc(Index))
// 	http.Handle("/debug/pprof/cmdline", http.HandlerFunc(Cmdline))
// 	http.Handle("/debug/pprof/profile", http.HandlerFunc(Profile))
// 	http.Handle("/debug/pprof/symbol", http.HandlerFunc(Symbol))
// 	http.Handle("/debug/pprof/trace", http.HandlerFunc(Trace))
// }
// 만약 별도 선언 후 /debug/pprof/trace 등 사용시 404 NOT FOUND 가 발생한다면
// 다음과 같이 pprof.Trace 등을 사용하도록 해야 한다.
// r.HandleFunc("/pprof/cmdline", pprof.Cmdline)
// r.HandleFunc("/pprof/symbol", pprof.Symbol)
// r.HandleFunc("/pprof/profile", pprof.Profile)
// r.HandleFunc("/pprof/trace", pprof.Trace)
