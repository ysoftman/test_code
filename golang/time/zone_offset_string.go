package main

import (
	"fmt"
	"log"
	"time"
)

func main() {
	now := time.Now()
	zoneName, zoneOffset := now.Zone()
	fmt.Println("zoneName:", zoneName)
	fmt.Println("zoneOffset:", zoneOffset)

	// zone offset string 만들기
	zoneOffsetString := "Z"
	timestring := fmt.Sprintf("2022-12-12T00:00:00%v", zoneOffsetString)
	fmt.Println(timestring)
	if _, err := time.Parse(time.RFC3339, timestring); err != nil {
		log.Fatal("err:", err)
	}
	zoneOffsetString = fmt.Sprintf("+%02d:00", zoneOffset/(60*60))
	timestring = fmt.Sprintf("2022-12-12T00:00:00%v", zoneOffsetString)
	fmt.Println(timestring)
	if _, err := time.Parse(time.RFC3339, timestring); err != nil {
		log.Fatal("err:", err)
	}
	zoneOffset *= -1
	zoneOffsetString = fmt.Sprintf("-%02d:00", (-1*zoneOffset)/(60*60))
	timestring = fmt.Sprintf("2022-12-12T00:00:00%v", zoneOffsetString)
	fmt.Println(timestring)
	if _, err := time.Parse(time.RFC3339, timestring); err != nil {
		log.Fatal("err:", err)
	}
}
