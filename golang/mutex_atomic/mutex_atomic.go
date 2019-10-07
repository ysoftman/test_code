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

func thread1(wg *sync.WaitGroup, enableMutex bool) {
	defer wg.Done()
	for {
		// 뮤텍스 락으로 동기화
		if enableMutex {
			g_mutex.Lock()
		}

		g_value++
		fmt.Println("[", time.Now().Format(time.StampMilli), "] thread1, g_value = ", g_value)
		if enableMutex {
			g_mutex.Unlock()
		}

		if g_value > 20 {
			return
		}

		time.Sleep(10 * time.Millisecond)

		// 원자성을 보장하여 2씩 증가시키
		atomic.AddInt32(&g_atomic_value, 2)
	}
}

func thread2(wg *sync.WaitGroup, enableMutex bool) {
	defer wg.Done()
	for {
		// 뮤텍스 락으로 동기화
		if enableMutex {
			g_mutex.Lock()
		}

		g_value++
		fmt.Println("[", time.Now().Format(time.StampMilli), "] thread2, g_value = ", g_value)
		if enableMutex {
			g_mutex.Unlock()
		}

		if g_value > 20 {
			return
		}

		time.Sleep(10 * time.Millisecond)

		// 원자성을 보장하여 2씩 증가시키
		atomic.AddInt32(&g_atomic_value, 2)
	}
}

func thread3(wg *sync.WaitGroup, enableMutex bool) {
	defer wg.Done()
	for {
		// 뮤텍스 락으로 동기화
		if enableMutex {
			g_mutex.Lock()
		}

		g_value++
		fmt.Println("[", time.Now().Format(time.StampMilli), "] thread3, g_value = ", g_value)
		if enableMutex {
			g_mutex.Unlock()
		}

		if g_value > 20 {
			return
		}

		time.Sleep(10 * time.Millisecond)

		// 원자성을 보장하여 2씩 증가시키
		atomic.AddInt32(&g_atomic_value, 2)
	}
}

func main() {
	fmt.Println("[", time.Now().Format(time.StampMilli), "] Mutext test...")
	var wg sync.WaitGroup

	wg.Add(3)
	go thread1(&wg, false)
	go thread2(&wg, false)
	go thread3(&wg, false)
	wg.Wait()
	fmt.Println("g_atomic_value = ", g_atomic_value)

	g_value = 0
	g_atomic_value = 0
	wg.Add(3)
	// mutext 사용한 경우 g_value 순서 보장
	go thread1(&wg, true)
	go thread2(&wg, true)
	go thread3(&wg, true)
	wg.Wait()
	fmt.Println("g_atomic_value = ", g_atomic_value)
}
