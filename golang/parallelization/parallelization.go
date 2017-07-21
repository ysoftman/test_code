// author : ysoftman
// encoding : utf-8
// title : 병렬화(parallelization) 테스트
// [desc]
// golang 의 go routine(고루틴) 이라고 하는 경량 쓰레드를 사용한다.
// 고루틴은 기본적으로 concurrency(동시성)하게 동작한다.
// 고루틴를 이용한 동시성 처리 예시 https://gobyexample.com/goroutines
// 만약 병렬처리(실제 다수의 cpu 를 사용해서 병렬 처리하는 경우)하려면
// 프로그램에서 사용할 수 있는 cpu 개수를 GOMAXPROCS 로 늘리면된다.
// 기본적으로 GOMAXPROCS 를 사용하지 않더라도 기본적으로
// 현재 머신의 cpu 개수로 설정되어 있다.
package main

import "runtime"
import "fmt"

func main() {
	nCpu := runtime.NumCPU()
	fmt.Println("Num Of CPUs =", nCpu)

	// 프로그램에서 동시에 사용할 수 있는 cpu 개수 설정
	nPreviousSetting := runtime.GOMAXPROCS(nCpu)
	fmt.Println("Previous gomaxprocs =", nPreviousSetting)

	// busy 작업을 하는 익명함수들을 고루틴으로 수행해 보자
	// 4코어 cpu 의 경우 cpu 사용이 100%
	// GOMAXPROCS 로 설정한 cpu 개수만큼 고루틴을 처리하게 된다.
	// 프로그램 수행 후 cpu 사용율을 모니터링 해보자
	go func() {
		for {
		}
	}()

	go func() {
		for {
		}
	}()

	go func() {
		for {
		}
	}()

	go func() {
		for {
		}
	}()

	fmt.Println("Num Of go routine =", runtime.NumGoroutine())

	// cpu 100% 사용중이라면 키입력이 버벅거릴 수 있으니 주의
	input := ""
	fmt.Scanln(&input)
}
