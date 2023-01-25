package main

import (
	"fmt"
	"time"
)

func checkPeriodically() {
	fmt.Println("Check Periodically")

	// 0.5초마다 ticker.C(channel) 로 time 값이 배달된다.
	ticker := time.NewTicker(time.Millisecond * 500)
	fmt.Println("ticker start")
	// tick 이 0.5 초마다 계속 발생하기 때문에 go 루틴으로 돌리고 5초후에 멈춘다.
	go func() {
		for t := range ticker.C {
			fmt.Println("tick ", t)
		}
	}()
	time.Sleep(time.Second * 5)
	ticker.Stop()
	fmt.Println("ticker stop")
}
