// ysoftman
// channel buffer 테스트
package main

import (
	"fmt"
	"strconv"
	"sync"
	"time"
)

func main() {
	channelUnbuffered()

	channelBuffer1()

	channelBuffer2()

	channelBytes()
}

func channelUnbuffered() {
	fmt.Println("channelUnbuffered - start")
	// unbuffered channel
	channel0 := make(chan int)

	go func() {
		// 고루틴에서 데이터 송신
		channel0 <- 123456789
	}()

	// unbuffered channel 로 부터 수신될때까지 기다리게 된다.
	fmt.Println(<-channel0)
	fmt.Println("channelUnbuffered - end")
	close(channel0)
}

func channelBuffer1() {
	fmt.Println("channel buffer 1 - start")

	// 채널 버퍼를 1로 설정
	// 버퍼의 크기를 늘리면 채널에 한번에 값을 쓸 수 있어 빨라진다.
	ch := make(chan int, 1)

	// go 루틴 수행전의 ch 는 nil
	// nil 상태의 ch 에 값을 쓰면 되면 무한블럭(deadlock)
	// ch <- 1
	// nil 상태의 ch 로 부터 값을 가져오게 되면 무한블럭(deadlock)
	// fmt.Println("ch:", <-ch)

	go func() {
		ch <- 1
		fmt.Println("set 1")
		// 버퍼풀로 인해 버퍼가 비워질때까지 블럭된다.
		ch <- 2
		fmt.Println("set 2")
		ch <- 3
		fmt.Println("set 3")
		ch <- 4
		fmt.Println("set 4")
	}()

	fmt.Println("recv ch:", <-ch)
	fmt.Println("recv ch:", <-ch)
	fmt.Println("recv ch:", <-ch)
	// 채널에 값이 설정되어야 받을 수 있다.
	fmt.Println("recv ch:", <-ch)

	// 채널을 닫으면 채널로 송신할 수 없지만 수신은 할 수 있다.
	close(ch)
	// 채널이 닫히고 수신을 하면 두번째 값이 false 로 수신이 제대로 되지 않은것으로 표시된다.
	val, success := <-ch
	fmt.Println("recv ch:", val, " success:", success)

	fmt.Println("channel buffer 1 - end")
}

func channelBuffer2() {
	fmt.Println("channel buffer 2 - start")
	var wg sync.WaitGroup
	wg.Add(10)
	queue := make(chan int, 10)
	for i := 1; i <= 10; i++ {
		queue <- i
	}

	fmt.Println("len(queue):", len(queue))
	// for i := 0; i < 10; i++ {
	// 	fmt.Println(<-queue)
	// }
	// range 로 채널을 조회하려면 채널을 닫아 송신이 없도록 보장해야 한다.
	// 채널을 닫지 않으면 range 마지막 루프에서 채널을 기다리며 deadlock 이 발생한다.
	close(queue)
	for i := range queue {
		fmt.Println("i", i)
		// 고루틴에 전달하기 위해 현재 루프에서의 인스턴스틀 생성해야 한다.
		// 현재 루프 변수와 같은 이름의 변수를 사용해도 된다.
		// 인스턴스가 없다면 range i 의 값이 루프마다 재사용되어 고루틴에 중복값(마지막 푸르의 i=10)이 전달 된다.
		// 10개의 고루틴이 한꺼번에 실행되서 모두 1초안에 완료된다.
		i := i
		go func() {
			time.Sleep(1 * time.Second)
			fmt.Println("closure:", i)
			wg.Done()
		}()
	}
	wg.Wait()
	fmt.Println("channel buffer 2 - end")
}

func channelBytes() {
	var wg sync.WaitGroup
	wg.Add(10)
	data := []byte("ysoftman0")
	ch := make(chan []byte)
	go func() {
		for i := 0; i < 10; i++ {
			fmt.Println(string(<-ch))
			wg.Done()
		}
	}()
	for i := 0; i < 10; i++ {
		data[len(data)-1] = []byte(strconv.Itoa(i))[0]
		time.Sleep(1 * time.Second)
		ch <- data
	}
	wg.Wait()
	close(ch)
}
