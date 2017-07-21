// author : ysoftman
// encoding : utf-8
// title : anagram
// desc : 주어진 문자들을 재배열하 나올수 있는 모든 스트링 찾기
package main

import (
	"fmt"
	"strings"
)

func anagram(prefix string, remain string, result *[]string) int {

	strslice := []byte(remain)
	// for debug
	//	fmt.Println("prefix :", prefix, "remain :", remain, "len(strslice) :", len(strslice))

	for i := 0; i < len(strslice); i++ {
		if len(strslice) > 1 {
			// 문자 선택
			temp := strslice[i]

			// 선택한 문자를 제외한 나머지 문자열 만들기
			strslice_temp := make([]byte, len(strslice))
			copy(strslice_temp, strslice)
			strslice_temp[i] = '_'
			remain = strings.Replace(string(strslice_temp), "_", "", -1)

			anagram(prefix+string(temp), remain, result)

		} else if len(strslice) == 1 {
			// fmt.Println(prefix + string(strslice[i]))
			*result = append(*result, prefix+string(strslice[i]))
		}
	}
	return 1
}

func main() {

	result := []string{}

	anagram("", "biro", &result)

	for _, v := range result {
		fmt.Println(v)
	}

	fmt.Println("total cnt =", len(result))

}
