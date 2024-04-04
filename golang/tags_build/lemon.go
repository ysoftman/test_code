// go run -tags lemon .  일때만 빌드된다.
// go:... 로 주석시작에 공백에 없어야 한다.
//go:build lemon

// go run -tags lemon .  일때만 빌드된다.
package main

import "fmt"

func Name() {
	fmt.Println("lemon!")
}
