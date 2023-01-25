package main

import (
	"fmt"
	"time"
)

func main() {
	// mac > system preferences > date & time > time zone 에서 변경해서 테스트해보자.
	t := time.Now()
	fmt.Println("local:", t.Format(time.RFC3339))
	// Asia/Seoul 시간으로 변경
	// zoneName := "Asia/Seoul"
	zoneName := "Europe/Berlin"
	// loc, _ := time.LoadLocation()
	loc, _ := time.LoadLocation(zoneName)
	t = t.In(loc)
	fmt.Println(zoneName+":", t.Format(time.RFC3339))
}
