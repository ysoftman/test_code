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
	fmt.Println("context test....")

	// 5초 타임아웃인 context 를 생성한다.
	// context 외 cancel 함수를 리턴한다.
	ctx, cancel := context.WithTimeout(context.Background(), 500*time.Millisecond)

	select {
	// context 타임아웃 전에 발행하면
	// 1초 후 현재시간을 채널로 리턴한다.
	case time := <-time.After(1 * time.Second):
		fmt.Println("time", time)
		fmt.Println("overslept!")
	// context 가 취소되었거나 타임아웃되어 채널이 끝난경우
	case <-ctx.Done():
		fmt.Println("context done()")
	}

	fmt.Println("cancel()....")
	// context 리소스 해제
	cancel()
}
