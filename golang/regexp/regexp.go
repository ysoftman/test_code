package main

import (
	"fmt"
	"regexp"
)

// 정규식 사용하기
func main() {
	// 방법1
	// l로 시작하고 z 로 끝나고, l 과 z 사이에 a-z 까지 1번이상 온다.
	isMatch, _ := regexp.MatchString("l([a-z]+)z", "leeemonnnz")
	fmt.Println(isMatch)

	// 방법2
	// 정규식을 한번 컴파일해두고 match, find 할때마다 재사용
	// l 과 z 사이에 영소문자가 있는 패턴
	re := regexp.MustCompile("l([a-z]+)z")
	fmt.Println(re.MatchString("lemonz"))
	fmt.Println(re.MatchString("lz"))
	// 정규식에 합당하는 문자열 부분 출력
	fmt.Println(re.FindString("aaaaaaalaazbbbbbb"))
	// 정규식에 맞는 문자열 모두 지정한 문자열로 바꾸기
	fmt.Println(re.ReplaceAllString("1234 lemonz ysoftmanlaazysoftman", "___replaced___"))

	// FindStringSubmatch 는 정규 표현식의 전체 및 부분 매치되는 경우를 모두 찾는다.
	// 전체 정규식 l([a-z]+)z 에 매치 => laaazllzzz = subMatched[0]
	// 부분 정규식 ([a-z]+) 에 매치 => aaazllzz = subMatched[1]
	subMatched := re.FindStringSubmatch("aalaaazllzzz")
	for i := 0; i < len(subMatched); i++ {
		fmt.Printf("%v, %v\n", i, subMatched[i])
	}
}
