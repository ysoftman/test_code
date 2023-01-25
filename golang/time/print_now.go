package main

import (
	"fmt"
	"time"
)

func main() {
	// 현재 시간
	fmt.Println("time.Now():", time.Now())
	// Now() 자체가 로컬 타임이라서 굳이 Now().Local() 로 사용할 필요는 없다.
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
}
