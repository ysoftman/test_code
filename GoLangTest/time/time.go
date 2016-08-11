// author : ysoftman
// encoding : utf-8
// title : time 테스트

package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Println("time test...")

	// 현재 unix epoch time(nano sec 까지 표시)
	fmt.Println("unix epoch time(nanosec): ", time.Now().UnixNano())

	// 현재 unix epoch time(sec로 표시)
	unixtime := time.Now().Unix()
	fmt.Println("unix epoch time(sec): ", unixtime)

	// 현재 unix epoch time(날짜로 표시)
	unixtime2 := time.Unix(unixtime, 0).String()
	fmt.Println("unix epoch time(date): ", unixtime2)

	// 현재 시간 파악
	curtime := time.Now()
	fmt.Println("curtime:", curtime)
	fmt.Println("curtime.Year():", curtime.Year())
	fmt.Println("curtime.Month():", curtime.Month())
	fmt.Println("curtime.Day():", curtime.Day())

	// 현재로 부터 2달 20일 뒤 시간 파악
	nexttime := curtime.AddDate(0, 2, 10)
	fmt.Println("Now()+2months+20days:", nexttime)

	// 1초 표헌
	fmt.Println("time.Second:", time.Second)

	fmt.Println("time.Now():", time.Now())

	// 3초 슬립
	fmt.Println("Sleep 3 sec...")
	time.Sleep(3 * time.Second)

	fmt.Println("time.Now():", time.Now())

	// 1초를 duration 으로 표현(nanosec)
	fmt.Println("time.Duration(1):", time.Duration(1))

	// 날짜 설정
	targetTime := time.Date(1981, 2, 15, 20, 30, 0, 0, time.Local)
	fmt.Println("targetTime:", targetTime)
	fmt.Println("targetTime.Unix():", targetTime.Unix())

	// constants
	fmt.Println("ANSIC:", time.ANSIC)
	fmt.Println("UnixDate:", time.UnixDate)
	fmt.Println("RubyDate:", time.RubyDate)
	fmt.Println("RFC822:", time.RFC822)
	fmt.Println("RFC850:", time.RFC850)
	fmt.Println("RFC1123:", time.RFC1123)
	fmt.Println("RFC3339:", time.RFC3339)
	fmt.Println("Kitchen:", time.Kitchen)
	fmt.Println("Stamp:", time.Stamp)

	countDown()
}

func countDown() {
	fmt.Println("Count Down")
	for i := 100; i >= 0; i-- {
		time.Sleep(1 * time.Second)
		fmt.Println(i)
	}
}
