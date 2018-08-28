// ysoftman
// go 1.11 에 추가된 trace 패키지 테스트

// 트레이스 결과 웹브라우저로 보기 - https://golang.org/cmd/trace/
// go tool trace trace.out
package main

import (
	"fmt"
	"log"
	"os"
	"runtime/trace"
	"sync"
	"time"
)

func main() {
	f, err := os.Create("trace.out")
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	// 파일로 트레이싱 결과 출력
	trace.Start(f)
	fmt.Println("trace testing....")

	var wg sync.WaitGroup
	wg.Add(5)
	go func() {
		time.Sleep(5 * time.Second)
		wg.Done()
	}()
	go func() {
		time.Sleep(4 * time.Second)
		wg.Done()
	}()
	go func() {
		time.Sleep(3 * time.Second)
		wg.Done()
	}()
	go func() {
		time.Sleep(2 * time.Second)
		wg.Done()
	}()
	go func() {
		time.Sleep(1 * time.Second)
		wg.Done()
	}()
	wg.Wait()

	trace.Stop()
}
