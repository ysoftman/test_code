/*
# github.com 오픈 소스 사용하기(윈도우 환경 기준)
# GOPATH 에 현재 작업디렉토리 경로 추가
set gopath=%cd%;

# go get 으로 github 오픈 소스 다운받기(pkg, src 디렉토리 자동 생성)
go get github.com/benbjohnson/clock

# liteide 사용시 GOPATH 에 현재 작업 디렉토리 경로 추가
View -> Manage GOPATH -> Custom Directories -> Add Directory
*/

// author : ysoftman
// encoding : utf-8
// title : https://github.com/benbjohnson/clock 오픈소스 테스트
package main

import (
	"fmt"
	"time"

	"github.com/benbjohnson/clock"
)

func main() {
	fmt.Println("mocking time in go... test")
	// 기본 time 사용시
	cur := time.Now()
	fmt.Println("cur = ", cur)
	fmt.Println("cur.Date() year,month,day ", cur.Year(), cur.Month(), cur.Day())
	fmt.Println("cur.Hour()", cur.Hour())
	fmt.Println("cur.Minute()", cur.Minute())
	fmt.Println("cur.Second()", cur.Second())
	fmt.Println("cur.Nanosecond()", cur.Nanosecond())

	// clock 사용하기
	mockingtime := clock.New() // real time
	fmt.Println("mockingtime.Now()", mockingtime.Now())
	year, month, day := mockingtime.Now().Date()
	fmt.Println("mockingtime.Now().Date() year,month,day ", year, month, day)
	fmt.Println("mockingtime.Now().Hour()", mockingtime.Now().Hour())
	fmt.Println("mockingtime.Now().Minute()", mockingtime.Now().Minute())
	fmt.Println("mockingtime.Now().Second()", mockingtime.Now().Second())
	fmt.Println("mockingtime.Now().Nanosecond()", mockingtime.Now().Nanosecond())

	// clock 에서 사용할 수 있는 add 기능
	mockingtime2 := clock.NewMock() // unix epoch time 초기값
	fmt.Println("mockingtime2.Now()", mockingtime2.Now())
	fmt.Println("mockingtime2.Add(5 * time.Hour)")
	// 5시간 더하기
	mockingtime2.Add(5 * time.Hour)
	fmt.Println("mockingtime2.Now()", mockingtime2.Now())
}
