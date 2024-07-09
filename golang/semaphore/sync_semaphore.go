// author : ysoftman
// encoding : utf-8
// title : semaphore 테스트
package main

import (
	"context"
	"fmt"
	"runtime"
	"sync"
	"time"

	"golang.org/x/sync/semaphore"
)

func thread(wg *sync.WaitGroup, jobid int) {
	defer wg.Done()
	fmt.Printf("[%v] processing job=%v\n", time.Now().Format(time.StampMilli), jobid)
	time.Sleep(2 * time.Second)
}

func main() {
	wg := sync.WaitGroup{}
	ctx := context.Background()
	maxThreads := runtime.GOMAXPROCS(0)
	numJobs := 20
	wg.Add(numJobs)
	fmt.Println("maxThreads:", maxThreads)

	//maxThreads 개수(weight) 만큼 lock 을 가질 수 있다.
	sem := semaphore.NewWeighted(int64(maxThreads))
	for i := 0; i < numJobs; i++ {
		fmt.Println("job=", i)
		// 1개 락을 잡을 수 있도록 시도, 이미 weight 개수만큼 사용중이라면 끝날때까지 대기
		if err := sem.Acquire(ctx, 1); err != nil {
			fmt.Printf("failed to acquire semaphore: %v\n", err)
			break
		}
		go func(i int) {
			defer sem.Release(1)
			thread(&wg, i)
		}(i)
	}
	wg.Wait()
}
