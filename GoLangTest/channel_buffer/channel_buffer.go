// ysoftman
// channel buffer 테스트
package main

import "fmt"

func main() {
	fmt.Println("channel buffer test")
	fmt.Println("test start")

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
		ch <- 2
		fmt.Println("set 2")
		// 버퍼풀로 인해 버퍼가 비워질때까지 블럭된다.
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

	close(ch)

	fmt.Println("test end")
}
