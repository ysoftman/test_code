// author : ysoftman
// encoding : utf-8
// title : contetxt 테스트, go 1.7 부터 지원
package main

import (
	"context"
	"fmt"
	"time"
)

func main() {
	// https://blog.golang.org/context
	// context 는 사용자 요청이 취소되거나 타임아웃되었을때 요청에 반응했던 모든 고루틴을 빠르게 정리하여 리소스를 시스템에 반환한다.
	fmt.Println("context test....")

	// 부모 context 를 인자로 주고 파생된 새로운 컨텍스를 만든다.
	// 5초 타임아웃(데드라인)인 context 를 생성한다.
	// context.Background() 는 빈값으로 최상위 context 로 main(), init() 에서 컨텍스를 만들때 사용된다.
	// 생성된 context 를 취소(리소스 해제)할 수 있는 cancel 함수를 리턴한다.
	// context 는 여러개의 고루틴에서 동시에 안전하게 사용할 수 있다.
	ctx, cancel := context.WithTimeout(context.Background(), 500*time.Millisecond)

	// 채널 하나 생성
	ch := make(chan string)

	go func(ctx context.Context) {
		fmt.Println("----- go routine start")

		type key int
		type value int
		var userkey key = 1
		// int32 형식의 1234 값을 가진 자식 context 생성
		ctx2 := context.WithValue(ctx, userkey, 1234)
		fmt.Println("ctx2.Value", ctx2.Value(userkey))

		dealine, _ := ctx.Deadline()
		fmt.Println("deadline", dealine)

		// context 타임아웃전에 일을 마치는 경우
		time.Sleep(300 * time.Millisecond)
		// context 타임아웃되는 경우
		// time.Sleep(700 * time.Millisecond)

		fmt.Println("----- go routine end")
		// 작업 완료
		ch <- "complete"
	}(ctx)

	// 가장 먼저 도착하는 채널 파악
	select {
	// context 타임아웃 이후라 발생할 수 없음
	case time := <-time.After(2000 * time.Millisecond):
		fmt.Println("overslpet!!!", time)
		// nil
		fmt.Println(ctx.Err())
	// 채널로부터 작업완료 통보가 된 경우
	case <-ch:
		fmt.Println("complete job!")
	// context 가 취소되었거나 타임아웃되어 context 끝난경우
	case <-ctx.Done():
		fmt.Println("context done()")
		// context.Canceled => "context canceled"
		// context.DeadlineExceeded => "context deadline exceeded"
		fmt.Println(ctx.Err())
	}

	fmt.Println("cancel()....")
	// context 리소스 해제
	// 모든 파생된 자식 context 들도 해제된다.
	cancel()
}
