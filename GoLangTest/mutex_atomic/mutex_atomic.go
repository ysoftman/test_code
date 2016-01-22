// author : ysoftman
// encoding : utf-8
// title : mutext, atomic 테스트
package main

import (
	"fmt"
	"sync"
	"sync/atomic"
	"time"
)

var g_value int = 0
var g_atomic_value int32 = 0
var g_mutex = &sync.Mutex{}

func thread1() {
	for {
		// 뮤텍스 락으로 동기화
		g_mutex.Lock()

		g_value++
		fmt.Println("[", time.Now(), "] thread1, g_value = ", g_value)

		if g_value > 20 {
			return
		}

		g_mutex.Unlock()

		time.Sleep(1 * time.Second)

		// 원자성을 보장하여 2씩 증가시키
		atomic.AddInt32(&g_atomic_value, 2)
	}
}

func thread2() {
	for {
		// 뮤텍스 락으로 동기화
		g_mutex.Lock()

		g_value++
		fmt.Println("[", time.Now(), "] thread2, g_value = ", g_value)
		if g_value > 20 {
			return
		}

		g_mutex.Unlock()

		time.Sleep(1 * time.Second)

		// 원자성을 보장하여 2씩 증가시키
		atomic.AddInt32(&g_atomic_value, 2)
	}
}

func thread3() {
	for {
		// 뮤텍스 락으로 동기화
		g_mutex.Lock()

		g_value++
		fmt.Println("[", time.Now(), "] thread3, g_value = ", g_value)
		if g_value > 20 {
			return
		}

		g_mutex.Unlock()

		time.Sleep(1 * time.Second)

		// 원자성을 보장하여 2씩 증가시키
		atomic.AddInt32(&g_atomic_value, 2)
	}
}

func main() {
	fmt.Println("[", time.Now(), "] Mutext test...")

	go thread1()
	go thread2()
	go thread3()

	// 고루틴 쓰레드가 처리될때까지 기다려주기 위해
	input := ""
	fmt.Scanln(&input)

	fmt.Println("g_atomic_value = ", g_atomic_value)
}
