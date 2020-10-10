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
