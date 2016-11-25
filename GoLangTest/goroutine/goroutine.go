// author : ysoftman
// encoding : utf-8
// title : go routine, channel, select 테스트
package main

import "time"
import "fmt"

func main() {
	// go routine 간의 통신 및 동기화를 위한 channel 생성
	// 버퍼 명시를 안하면 상대가 준비될때까지 블록되어 lock 없이 동기화 가능
	//channel1 := make(chan int)
	// 버퍼를 명시하면 비동기로 블록되지 않고 바로 수행된다.
	channel1 := make(chan int, 10)
	channel2 := make(chan int, 10)

	// go 로 go routine(경량 쓰레드) 돌리기
	// go routine 생성 비용은 크지 않아 수천개를 사용해도 된다.
	go func1(channel1)
	go func2(channel2)
	go func3(channel1, channel2)

	// 키입력 하면 프로그램 종료
	input := ""
	fmt.Scanln(&input)
}

func func1(ch chan int) int {
	value := 0
	for {
		time.Sleep(500 * time.Millisecond)
		fmt.Printf("[%s] func1 %2d\n", time.Now().Format("2006-01-02 15:04:05"), value)

		// 채널에 value 값 전달
		ch <- value

		// 채널 송신측에서는 채널을 close 할 수 있다.
		if value >= 10 {
			//fmt.Printf("[%s] func1 채널닫음\n", time.Now().Format("2006-01-02 15:04:05"))
			//close(ch)
			break
		}
		value += 2
	}
	fmt.Printf("[%s] func1 end\n", time.Now().Format("2006-01-02 15:04:05"))
	return 0
}

func func2(ch chan int) int {
	value := 1
	for {
		time.Sleep(500 * time.Millisecond)
		fmt.Printf("[%s] func2 %2d\n", time.Now().Format("2006-01-02 15:04:05"), value)

		// 채널에 value 값 전달
		ch <- value

		// 채널 송신측에서는 채널을 close 할 수 있다.
		if value >= 10 {
			//fmt.Printf("[%s] func2 채널닫음\n", time.Now().Format("2006-01-02 15:04:05"))
			//close(ch)
			break
		}
		value += 2
	}
	fmt.Printf("[%s] func2 end\n", time.Now().Format("2006-01-02 15:04:05"))
	return 0
}

func func3(ch1, ch2 chan int) {
	for {
		// select 로 수신 채널들 구분하기(채널에서의 switch)
		select {
		// 채널1 값을 value 로 전달
		case value1 := <-ch1:
			fmt.Printf("[%s] func3 value1 %2d\n", time.Now().Format("2006-01-02 15:04:05"), value1)
		// 채널2 값을 value 로 전달
		case value2 := <-ch2:
			fmt.Printf("[%s] func3 value2 %2d\n", time.Now().Format("2006-01-02 15:04:05"), value2)
		}
	}
}
