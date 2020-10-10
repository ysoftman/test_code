// ysoftman
// plugin package test
// cd ./plugin_module && go build -buildmode=plugin -o plugin_module.so && cd .. && go run plugin.go
package main

import (
	"fmt"
	"plugin"
)

func main() {
	// ../ 등의 상대 경로로 오픈할 수 없다.
	p, err := plugin.Open("./plugin_module/plugin_module.so")
	if err != nil {
		panic(err)
	}

	// 전역 변수 찾아 설정
	v, err := p.Lookup("Var1")
	if err != nil {
		panic(err)
	}
	*v.(*string) = "aaa"

	// 함수 찾아 설정
	printhelloFunc, err := p.Lookup("PringHello")
	if err != nil {
		panic(err)
	}
	printhelloFunc.(func())()

	// 함수 찾아 설정
	addFunc, err := p.Lookup("Add")
	if err != nil {
		panic(err)
	}
	ret := addFunc.(func(int, int) int)(1, 2)
	fmt.Println("addFunc result = ", ret)
}
