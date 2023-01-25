package main

import (
	"fmt"
	"time"
)

func printDate() {
	// 날짜 설정
	fmt.Println("time.Date(1981, 2, 15, 20, 30, 0, 0, time.Local):", time.Date(1981, 2, 15, 20, 30, 0, 0, time.Local))
	fmt.Println("time.Date(1981, 2, 15, 20, 30, 0, 0, time.Local).Unix():", time.Date(1981, 2, 15, 20, 30, 0, 0, time.Local).Unix())

	fmt.Println("time.Duration(1):", time.Duration(1))
	fmt.Println("time.Duration(1)*time.Microsecond:", time.Duration(1)*time.Microsecond)
	fmt.Println("time.Duration(1)*time.Millisecond:", time.Duration(1)*time.Millisecond)
	fmt.Println("time.Duration(1)*time.Second:", time.Duration(1)*time.Second)
	fmt.Println("time.Duration(1)*time.Minute:", time.Duration(1)*time.Minute)
	fmt.Println("time.Duration(1)*time.Hour:", time.Duration(1)*time.Hour)

	// Mon Jan 2 15:04:05 -0700 MST 2006 시간으로 포맷팅을 명시해야 한다.
	fmt.Println(`time.Now().Format("20060102150405"):`, time.Now().Format("20060102150405"))
	fmt.Println(`time.Now().Format("3:04 PM"):`, time.Now().Format("3:04 PM"))
	fmt.Println(`time.Now().Format("Mon Jan _2 17:05:30 1981"):`, time.Now().Format("Mon Jan _2 17:05:30 2006"))

	fmt.Println(`time.Now().Year() - 1:`, time.Now().Year()-1)
}
