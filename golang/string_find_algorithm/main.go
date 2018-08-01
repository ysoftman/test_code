// ysoftman
// 문자열 찾기 알고리즘 테스트
package main

import (
	"fmt"
)

func main() {
	sentence := "abcdef abcabc bcabcabcd"
	word := "abcabc"
	fmt.Println("sentence:", sentence)
	fmt.Println("word:", word)

	idx, result := simpleFind(sentence, word)
	fmt.Println("simpleFind() = ", idx, result)

	fmt.Println("-----")

	indexes, results := kmp(sentence, word)
	fmt.Println("kmp() = ", indexes, results)

	fmt.Println("-----")

	words := []string{"ab", "a", "abcd", "abc", "aa", "bc", "cd"}
	indexes, results = ahocorasick(sentence, words)
	fmt.Println("ahocorasick() = ", indexes)
	fmt.Println("ahocorasick() = ", results)
}
