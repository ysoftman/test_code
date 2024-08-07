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
	checkK8SName("")
	checkK8SName("ysoftman.123")
	checkK8SName("ysoftman-123")
	checkK8SName("999abc")
	checkK8SName("1")
	checkK8SName("a-b-c-d-1-2-3-4-5")

	checkName1("123a-b-c-c-d")
	checkName1("Aa-b-c-c-d")
	checkName1("a-b-c-c-dddddddddd")
	checkName1("-b-c-c-d")
	checkName1("a-b-c-c-d")
}

func checkK8SName(name string) bool {
	// k8s deployment 이름 규칙
	// a DNS-1123 label must consist of lower case alphanumeric characters or '-', and must start and end with an alphanumeric character (e.g. 'my-name',  or '123-abc', regex used for validation is '[a-z0-9]([-a-z0-9]*[a-z0-9])?')"
	matched, err := regexp.MatchString("^[a-z0-9]([-a-z0-9]*[a-z0-9])?$", name)
	if err != nil {
		fmt.Println(err.Error())
	}
	fmt.Println("matched:", matched, "name:", name)
	return matched
}

// 소문자 시작,  이후 소문자,  숫자,  - 허용, 최대 30글자까지
var nameRule1 = regexp.MustCompile(`^[a-z]([a-z0-9-]{1,10})$`)

func checkName1(name string) {
	fmt.Println(name, nameRule1.MatchString(name))
}
