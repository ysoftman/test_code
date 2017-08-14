// author : ysoftman
// encoding : utf-8
// title : go routine, channel, select 테스트
package main

import "time"
import "fmt"
import "sync"

// Maxcnt 대문자로 시작하면 export 된다.
const Maxcnt = 10

func main() {
	// go routine 간의 통신 및 동기화를 위한 channel(고루틴간의 데이터 공유를 위한 통로) 생성
	// 버퍼 명시를 안하면 상대가 준비될때까지 블록되어 lock 없이 동기화 가능
	//channel1 := make(chan int)
	// 버퍼를 명시하면 비동기로 블록되지 않고 바로 수행된다.
	channel1 := make(chan int, 10)
	channel2 := make(chan int, 10)

	var wg sync.WaitGroup
	// 고루틴 3개를 WaitGroup 에 추가
	wg.Add(3)
	// go 로 go routine(경량 쓰레드) 돌리기
	// go routine 생성 비용은 크지 않아 수천개를 사용해도 된다.
	go send_value1(channel1, &wg)
	go send_value2(channel2, &wg)
	go recv_value(channel1, channel2, &wg)
	//  WaitGroup 의 고루틴들이 모두 끝날(Done)때까지 대기
	wg.Wait()
}

func send_value1(ch chan int, wg *sync.WaitGroup) int {
	defer wg.Done()
	value := 0
	for {
		time.Sleep(100 * time.Millisecond)
		fmt.Printf("[%s] send_value1 [%d]\n", time.Now().Format("2006-01-02 15:04:05"), value)

		// 채널에 value 값 전달
		ch <- value

		// 채널 송신측에서는 채널을 close 할 수 있다.
		if value >= Maxcnt {
			//fmt.Printf("[%s] send_value1 채널닫음\n", time.Now().Format("2006-01-02 15:04:05"))
			//close(ch)
			break
		}
		value++
	}
	fmt.Printf("[%s] send_value1 end\n", time.Now().Format("2006-01-02 15:04:05"))
	return 0
}

func send_value2(ch chan int, wg *sync.WaitGroup) int {
	defer wg.Done()
	value := 0
	for {
		time.Sleep(200 * time.Millisecond)
		fmt.Printf("[%s] send_value2 \t[%d]\n", time.Now().Format("2006-01-02 15:04:05"), value)

		// 채널에 value 값 전달
		ch <- value

		// 채널 송신측에서는 채널을 close 할 수 있다.
		if value >= Maxcnt {
			//fmt.Printf("[%s] send_value2 채널닫음\n", time.Now().Format("2006-01-02 15:04:05"))
			//close(ch)
			break
		}
		value++
	}
	fmt.Printf("[%s] send_value2 \tend\n", time.Now().Format("2006-01-02 15:04:05"))
	return 0
}

func recv_value(ch1, ch2 chan int, wg *sync.WaitGroup) {
	defer wg.Done()
	cnt1, cnt2 := 0, 0
	for {
		// 다음과 같이 사용하면 ch1,ch2 값을 모두 받을때까지 대기한다.
		// value1 := <-ch1:
		// value2 := <-ch2:
		// select 을 사용하면 대기하고 있다가 먼저 발생하는 채널을 처리하고 끝낸다.
		curch := 0
		curval := 0
		addpadding := ""
		select {
		case value1 := <-ch1:
			curch = 1
			curval = value1
			addpadding = ""
			cnt1++
		case value2 := <-ch2:
			curch = 2
			curval = value2
			addpadding = "\t"
			cnt2++
		}
		fmt.Printf("[%s] recv%d	  %s[%d]\n", time.Now().Format("2006-01-02 15:04:05"), curch, addpadding, curval)
		if cnt1 >= Maxcnt && cnt2 >= Maxcnt {
			break
		}
	}
	fmt.Printf("[%s] recv end\n", time.Now().Format("2006-01-02 15:04:05"))
}
