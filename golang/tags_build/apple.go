// go run -tags apple . 등으로 lemon 이 아닐때만 빌드된다.
// go:... 로 주석시작에 공백에 없어야 한다.
//go:build !lemon

package main

import "fmt"

func Name() {
	fmt.Println("apple!")
}
