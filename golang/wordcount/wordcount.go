// author : ysoftman
// encoding : utf-8
// title : 주어진 문자열에서 단어 카운트 하기

package main

import (
	"fmt"
	"strings"
)

func WordCount(s string) map[string]int {
	// strings.Count(s, "s")

	mapData := make(map[string]int)
	str := strings.Split(s, " ")
	for key, value := range str {
		fmt.Println("key = ", key, "value = ", value)
		mapData[value]++
	}

	return mapData
}

func main() {
	mapData := WordCount("apple fineapple cheese milk yogurt orange apple cheese")

	for key, value := range mapData {
		fmt.Println("mapData[", key, "] = ", value)
	}
}
