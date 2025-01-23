package main

import (
	"fmt"
	"log"
	"time"
)

func ToKST(dateStr string) time.Time {
	t, err := time.Parse(time.RFC3339, dateStr)
	if err != nil {
		log.Fatal("err:", err)
	}
	loc, _ := time.LoadLocation("Asia/Seoul")
	return t.In(loc)
}

func main() {
	// 한국 지역 시간으로 기간에 따라 KST(Korea Standard Time), JST(Japan Standard Time)와 LMT(Local Mean Time) 로 표기된다
	// LMT 사용 기간 : 1908-03-31 이전
	fmt.Println("->", ToKST("0001-01-01T01:01:00+09:00"))
	fmt.Println("->", ToKST("0100-12-31T01:01:00Z"))
	fmt.Println("->", ToKST("1908-03-31T00:00:01Z"))

	// KST 사용 기간: 1908-04-01 ~ 1911-12-31
	// 1908년 4월 1일(대한제국): 서양식 시간대를 처음 도입하며, 관보 제3994호(칙령 제5호)에 따라 동경 127.5°를 기준으로 GMT+08:30
	// +0830 KST
	fmt.Println("->", ToKST("1908-04-01T00:00:00Z"))
	fmt.Println("->", ToKST("1911-12-31T00:00:00Z"))

	// JST 사용 기간: 1912-01-01 ~ 1945-09-07
	// 1912년 1월 1일(일제강점기): 조선총독부 관보 제367호(고시 제338호)에 따라 일본과 같은 동경 135° GMT+09:00로 변경
	// +0900 JST
	fmt.Println("->", ToKST("1912-01-01T00:00:00Z"))
	fmt.Println("->", ToKST("1945-09-07T00:00:00Z"))

	// KST 사용 기간: 1945-09-08 ~ 1948-05-31
	// +0900 KST
	fmt.Println("->", ToKST("1945-09-08T00:00:00Z"))
	fmt.Println("->", ToKST("1948-05-31T00:00:00Z"))

	// KDT(Korea Daylight Time, 한국 써머 타임) 사용 기간: 1948-06-01 ~ 1960-09-17
	// +1000 KDT
	fmt.Println("->", ToKST("1948-06-01T00:00:00Z"))
	// +0930 KDT
	fmt.Println("->", ToKST("1960-09-17T00:00:00Z"))

	// KST 사용 기간: 1960-09-18 ~ 1961-08-09
	// +0830 KST
	fmt.Println("->", ToKST("1960-09-18T00:00:00Z"))
	fmt.Println("->", ToKST("1961-08-09T00:00:00Z"))

	// KST 사용 기간: 1961-08-10 ~ 1961-08-09
	// 1961년 8월 10일(박정희 정권): 국가재건최고회의 결정에 따라 동경 135° GMT+09:00로 변경. 구 표준자오선 변경에 관한 법률(1961. 8. 7. 제676호로 제정되어, 1986. 12. 31. 법률 제3919호로 폐지). 구 표준시에 관한 법률(1986. 12. 31. 법률 제3919호로 제정. 2011. 5. 19. 법률 제10640호로 전부 개정되기 전의 것).
	// +0900 KST
	fmt.Println("->", ToKST("1961-08-10T00:00:00Z"))
	fmt.Println("->", ToKST("1970-01-01T00:00:00Z"))
	fmt.Println("->", ToKST("1987-05-09T00:00:00Z"))

	// KDT(Korea Daylight Time, 한국 써머 타임) 사용 기간: 1987-05-10 ~ 1988-10-08
	// 1987년, 1988년: 1988 서울 올림픽과 그 전 해 하절기 동안 서머타임(UTC+10:00)을 시행, 올림픽 폐막 직후 폐지.
	// +1000 KDT
	fmt.Println("->", ToKST("1987-05-10T00:00:00Z"))
	fmt.Println("->", ToKST("1988-10-08T00:00:00Z"))

	// KST 사용 기간: 1988-10-09 ~ 현재
	fmt.Println("->", ToKST("1988-10-09T00:00:00Z"))
}
