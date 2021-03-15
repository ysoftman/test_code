package main

import (
	"fmt"
)

func create() {
	fmt.Println("----- msi create -----")

	// map string interface 어떤 데이터 구조든 만들 수 있다.
	msi := map[string]interface{}{
		"name":  "ysoftman",
		"fruit": "lemon",
		"age":   30,
		"etc": struct {
			innerA string
			innerB int
		}{"aaa", 123},
	}

	msi["zzz"] = "ㅋㅋㅋ"
	fmt.Println("msi:", msi)
}
