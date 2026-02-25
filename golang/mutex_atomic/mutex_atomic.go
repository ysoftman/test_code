// author : ysoftman
// encoding : utf-8
// title : mutex, atomic 테스트
package main

import (
	"fmt"
	"sync"
	"sync/atomic"
	"time"
)

var (
	g_value        int   = 0
	g_atomic_value int32 = 0
	g_mutex              = &sync.Mutex{}
)

func thread(wg *sync.WaitGroup, id int, enableMutex bool) {
	defer wg.Done()
	for {
		// 뮤텍스 락으로 동기화
		if enableMutex {
			g_mutex.Lock()
		}
		// 원자성을 보장하여1씩 증가시키(thread 실행 횟수 확인용도)
		atomic.AddInt32(&g_atomic_value, 1)
		g_value++
		// g_atomic_value 프린트는 락을 걸지 않으면 중복된값이 출력될 수 있다.
		fmt.Printf("[%v] thread%v g_atomic_value=%2v g_value=%2v\n", time.Now().Format(time.StampMilli), id, g_atomic_value, g_value)
		if enableMutex {
			g_mutex.Unlock()
		}
		if g_value > 20 {
			return
		}
		time.Sleep(10 * time.Millisecond)
	}
}

func main() {
	var wg sync.WaitGroup

	wg.Add(3)
	go thread(&wg, 1, false)
	go thread(&wg, 2, false)
	go thread(&wg, 3, false)
	wg.Wait()
	fmt.Println("g_atomic_value:", g_atomic_value)

	g_value = 0
	g_atomic_value = 0
	wg.Add(3)
	// mutex 사용한 경우 g_value 순서 보장
	go thread(&wg, 1, true)
	go thread(&wg, 2, true)
	go thread(&wg, 3, true)
	wg.Wait()
	fmt.Println("g_atomic_value:", g_atomic_value)
}
