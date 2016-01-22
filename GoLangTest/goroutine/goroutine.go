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
	// 버퍼를 명시하면 비동기적으로 블록되지 않고 바로 수행된다.
	channel1 := make(chan int, 10)
	channel2 := make(chan int, 10)

	// go 로 go routine(경량 쓰레드) 돌리기
	// go routine 생성에 비용은 크지 않아 수천개를 사용해도 된다.
	go thread1(channel1)
	go thread2(channel1)
	go thread3(channel1, channel2)

	// 쓰레드 동작을 계속 확인하기 위해서 키입력 하면 프로그램 종료
	input := ""
	fmt.Scanln(&input)
}

func thread1(ch chan int) int {

	value := 0

	for {
		time.Sleep(500 * time.Millisecond)

		value++
		fmt.Printf("[%s] thread1 %2d\n", time.Now(), value)

		// 채널에 i 값 전달
		ch <- value

		// 채널 송신측에서는 채널을 close 할 수 있다.
		if value >= 5 {
			//fmt.Printf("[%s] thread1 채널닫음\n", time.Now())
			//close(ch)
			break
		}
	}
	fmt.Printf("[%s] thread1 end\n", time.Now())
	return 0
}

func thread2(ch chan int) int {

	value := 5

	for {
		time.Sleep(500 * time.Millisecond)

		value++
		fmt.Printf("[%s] thread2 %2d\n", time.Now(), value)

		// 채널에 i 값 전달
		ch <- value

		// 채널 송신측에서는 채널을 close 할 수 있다.
		if value >= 10 {
			//fmt.Printf("[%s] thread2 채널닫음\n", time.Now())
			//close(ch)
			break
		}
	}
	fmt.Printf("[%s] thread2 end\n", time.Now())
	return 0
}

func thread3(ch1, ch2 chan int) int {

	for {

		// select 로 수신 채널들 구분하기(채널에서의 switch)
		select {
		// 채널1 값을 value 로 전달
		case value1 := <-ch1:
			fmt.Printf("[%s] thread3 value1 %2d\n", time.Now(), value1)
		// 채널2 값을 value 로 전달
		case value2 := <-ch2:
			fmt.Printf("[%s] thread3 value2 %2d\n", time.Now(), value2)
		}

	}
	fmt.Printf("[%s] thread3 end\n", time.Now())
	return 0
}
