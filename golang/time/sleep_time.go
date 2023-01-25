package main

import (
	"fmt"
	"time"
)

func sleepTime() {
	// "" 는 UTC "Local" 이면 현재 지역을 리턴한다.
	loc, _ := time.LoadLocation("Local")
	// 정해진 레이아웃(1번째 파라미터)으로 날짜(2번째 파라미터)를 time 으로 담을 수 있다.
	myDate, _ := time.ParseInLocation("2006-01-02 15:04:05", "1981-02-15 00:00:00", loc)
	fmt.Println("myDate:", myDate)
	fmt.Println("myDate.Year():", myDate.Year())
	fmt.Println("myDate.Month():", myDate.Month())
	fmt.Println("myDate.Day():", myDate.Day())
	fmt.Println("myDate.Hour():", myDate.Hour())
	fmt.Println("myDate.Minute():", myDate.Minute())
	fmt.Println("myDate.Second():", myDate.Second())

	// 현재로 부터 2달 20일 뒤 시간 파악
	fmt.Println("time.Now()+2months+20days:", time.Now().AddDate(0, 2, 10))
	// 어제 시간 파악
	fmt.Println("time.Now()-1days:", time.Now().AddDate(0, 0, -1))
	// 현재 유닉스 시간을 날짜로 변경
	fmt.Println("time.Unix(time.Now().Unix(), 0).String() (date):", time.Unix(time.Now().Unix(), 0).String())

	// 1초 표헌
	fmt.Println("time.Second:", time.Second)

	fmt.Println("time.Now():", time.Now())

	// 3초 슬립
	fmt.Println("time.Sleep(3) sec...")
	time.Sleep(3 * time.Second)

	fmt.Println("time.Now():", time.Now())

	// 1초를 duration 으로 표현(nanosec)
	fmt.Println("time.Duration(1):", time.Duration(1))
}
