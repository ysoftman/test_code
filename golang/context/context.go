// author : ysoftman
// encoding : utf-8
// title : context 테스트, go 1.7 부터 지원
package main

import (
	"context"
	"fmt"
	"io"
	"log"
	"net/http"
	"time"
)

type mydata struct {
	Name   string
	Number int
}

var timeout = 500 * time.Millisecond

func main() {
	// https://blog.golang.org/context
	// 같은 성격의 또는 이어지는 작업들이 맥락(context)을 통해 값을 전달하거나, 작업을 종료하는증의 작업을 할 수 있다.
	fmt.Println("context test....")

	// WithTimeout 는 사용자 요청이 취소되거나 타임아웃되었을때 요청에 반응했던 모든 고루틴을 빠르게 정리하여 리소스를 시스템에 반환한다.
	// 부모 context 를 인자로 주고 파생된 새로운 컨텍스를 만든다.
	// 5초 타임아웃(데드라인)인 context 를 생성한다.
	// context.Background() 는 빈값으로 최상위 context 로 main(), init() 에서 컨텍스를 만들때 사용된다.
	// 생성된 context 를 취소(리소스 해제)할 수 있는 cancel 함수를 리턴한다.
	// context 는 여러개의 고루틴에서 동시에 안전하게 사용할 수 있다.
	ctx, cancel := context.WithTimeout(context.Background(), timeout)
	// context 리소스 해제
	// 모든 파생된 자식 context 들도 해제된다.
	defer cancel()

	// 채널 하나 생성
	ch := make(chan string)

	go func(ctx context.Context) {
		fmt.Println("----- go routine start")

		// go-lint 에서 context with value 사용시 키는 커스텀 타입을 만들어 사용하라고 한다.
		type intkey int
		type value int
		var userintkey intkey = 1
		type strkey string
		var userstrkey1 strkey = "ysoftman1"
		var userstrkey2 strkey = "ysoftman2"
		var userstrkey3 strkey = "ysoftman3"
		// int32 형식의 1234 값을 가진 자식 context 생성
		ctx2 := context.WithValue(ctx, userintkey, 1234)
		// ctx2 에 값 추가
		ctx2 = context.WithValue(ctx2, userstrkey1, "lemon")
		ctx2 = context.WithValue(ctx2, userstrkey2, "orange")
		ctx2 = context.WithValue(ctx2, userstrkey3, "apple")
		// ctx2 구조체로 추가
		md := mydata{
			Name:   "ysoftman",
			Number: 999,
		}
		ctx2 = context.WithValue(ctx2, mydata{}, &md)
		fmt.Println("ctx2.Value(userintkey)", ctx2.Value(userintkey))
		fmt.Println("ctx2.Value(userstrkey)", ctx2.Value(userstrkey1))
		fmt.Println("ctx2.Value(userstrkey)", ctx2.Value(userstrkey2))
		fmt.Println("ctx2.Value(userstrkey)", ctx2.Value(userstrkey3))
		fmt.Println("ctx2.Value(mydata{})", ctx2.Value(mydata{}))
		if v, ok := ctx2.Value(mydata{}).(*mydata); ok {
			fmt.Println("ctx2.Value(mydata{}).(*mydata):", v)
			fmt.Println("ctx2.Value(mydata{}).(*mydata).Name:", v.Name)
			fmt.Println("ctx2.Value(mydata{}).(*mydata).Number:", v.Number)
		}

		// context 데드라인 시간 파악
		deadline, _ := ctx.Deadline()
		fmt.Println("deadline", deadline)

		// context 타임아웃되는 경우 더이상 진행되지 않는다.(cancel)
		// <-time.After(timeout) 없으면 <-ctx.Done 이 된다.
		// time.Sleep(700 * time.Millisecond)

		fmt.Println("----- go routine end")
		// 작업 완료
		ch <- "complete"
	}(ctx)

	// 가장 먼저 도착하는 채널 파악
	select {
	// context 타임아웃 이후라 발생할 수 없음
	// case time := <-time.After(2000 * time.Millisecond):
	case time := <-time.After(timeout):
		fmt.Println("timeout!!!", time)
	// 채널로부터 작업완료 통보가 된 경우
	case a := <-ch:
		fmt.Println("go routine end, <-ch:", a)
	// context 가 취소되었거나 타임아웃되어 context 끝난경우
	case <-ctx.Done():
		// context.Canceled => "context canceled"
		// context.DeadlineExceeded => "context deadline exceeded"
		fmt.Println("ctx.Done(), ctx.Err():", ctx.Err())
	}

	request_timeout_test()
}

func request_timeout_test() {
	// ctx, cancel := context.WithTimeout(context.Background(), 2000*time.Millisecond)
	// 응답이 100ms 없으면  timeout(context deadline exceeded)
	ctx, cancel := context.WithTimeout(context.Background(), 100*time.Millisecond)
	defer cancel()
	req, err := http.NewRequestWithContext(ctx, http.MethodGet, "https://httpbin.org/get", nil)
	if err != nil {
		log.Fatal(err)
	}
	cli := http.Client{}
	res, err := cli.Do(req)
	if err != nil {
		log.Fatal("client do error...", err)
	}
	defer res.Body.Close()
	out, err := io.ReadAll(res.Body)
	if err != nil {
		log.Fatal("client do error...", err)
	}
	fmt.Println("[out]", string(out))
}
