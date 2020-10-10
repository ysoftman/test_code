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

	// 현재 시간
	fmt.Println("time.Now():", time.Now())
	// Now() 자체가 로커 타임이라서 굳이 Now().Local() 로 사용할 필요는 없다.
	fmt.Println("time.Now().Local():", time.Now().Local())
	fmt.Println("time.Now().UnixNano() (nanosec):", time.Now().UnixNano())
	fmt.Println("time.Now().Unix() (sec):", time.Now().Unix())
	fmt.Println("time.Now().Year():", time.Now().Year())
	fmt.Println("time.Now().Month():", time.Now().Month())
	fmt.Println("time.Now().Day():", time.Now().Day())
	// constants
	fmt.Println("time.ANSIC:", time.ANSIC)
	fmt.Println("time.UnixDate:", time.UnixDate)
	fmt.Println("time.RubyDate:", time.RubyDate)
	fmt.Println("time.RFC822:", time.RFC822)
	fmt.Println("time.RFC850:", time.RFC850)
	fmt.Println("time.RFC1123:", time.RFC1123)
	fmt.Println("time.RFC3339:", time.RFC3339)
	fmt.Println("time.Kitchen:", time.Kitchen)
	fmt.Println("time.Stamp:", time.Stamp)

	// Mon Jan 2 15:04:05 -0700 MST 2006 시간으로 포맷팅을 명시해야 한다.
	fmt.Println(`time.Now().Format("20060102150405"):`, time.Now().Format("20060102150405"))
	fmt.Println(`time.Now().Format("3:04 PM"):`, time.Now().Format("3:04 PM"))
	fmt.Println(`time.Now().Format("Mon Jan _2 17:05:30 1981"):`, time.Now().Format("Mon Jan _2 17:05:30 2006"))

	fmt.Println(`time.Now().Year() - 1:`, time.Now().Year()-1)

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

	// 날짜 설정
	fmt.Println("time.Date(1981, 2, 15, 20, 30, 0, 0, time.Local):", time.Date(1981, 2, 15, 20, 30, 0, 0, time.Local))
	fmt.Println("time.Date(1981, 2, 15, 20, 30, 0, 0, time.Local).Unix():", time.Date(1981, 2, 15, 20, 30, 0, 0, time.Local).Unix())

	countDown()
	checkPeriodically()
}

func countDown() {
	fmt.Println("Count Down")
	for i := 3; i >= 0; i-- {
		time.Sleep(1 * time.Second)
		fmt.Println(i)
	}
}

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
