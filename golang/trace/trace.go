// ysoftman
// go 1.11 에 추가된 trace 패키지 테스트
// 트레이스 결과 웹브라우저로 보기 - https://golang.org/cmd/trace/
// 실행해서 trace.out 남기리고 결과 확인
// go run trace.go && go tool trace trace.out

package main

import (
	"context"
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

	ctx := context.Background()

	// 프로그램 종료될때까지 트레이싱 기록
	// trace.out 결과(브라우저에서)에서 User-defined regions 항목에서 확인가능하다.
	defer trace.StartRegion(ctx, "ysoftman trace...").End()

	// trace.WithRegion(ctx, "http listen start", func() {
	// 	fmt.Println("ysoftman start")
	// })

	var wg sync.WaitGroup
	wg.Add(5)
	go func() {
		// trace.WithRegion(ctx, "http listen start", func() {
		// 	fmt.Println("ysoftman - go routine1")
		// })
		time.Sleep(5 * time.Second)
		wg.Done()
	}()
	go func() {
		// trace.WithRegion(ctx, "http listen start", func() {
		// 	fmt.Println("ysoftman - go routine2")
		// })
		time.Sleep(4 * time.Second)
		wg.Done()
	}()
	go func() {
		// trace.WithRegion(ctx, "http listen start", func() {
		// 	fmt.Println("ysoftman - go routine3")
		// })
		time.Sleep(3 * time.Second)
		wg.Done()
	}()
	go func() {
		// trace.WithRegion(ctx, "http listen start", func() {
		// 	fmt.Println("ysoftman - go routine4")
		// })
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
