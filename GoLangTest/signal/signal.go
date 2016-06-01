// author : ysoftman
// encoding : utf-8
// title : 시그널 테스트, 콘솔에서 실행 후 Ctrl+C 시그널을 발생해보자.
package main

import (
	"fmt"
	"os"
	"os/signal"
	"syscall"
)

func main() {
	fmt.Println("Signal Test")
	fmt.Println("waiting for signal...")
	// 시그널을 받을 채널들 생성
	ch1 := make(chan os.Signal, 1)
	ch2 := make(chan os.Signal, 1)

	// 채널1은 SIGNT 시그널만 받을수 있도록 등록
	signal.Notify(ch1, syscall.SIGINT)
	// 채널2에 SIGINT 와 SIGQUIT 시그널만 받을 수 있도록 등록
	signal.Notify(ch2, syscall.SIGINT, syscall.SIGQUIT)

	// 채널로 부터 시그널 받기을때 까지 블럭
	recv1 := <-ch1
	fmt.Println("ch1 received signal :", recv1)

	recv2 := <-ch2
	fmt.Println("ch2 received signal :", recv2)
}
