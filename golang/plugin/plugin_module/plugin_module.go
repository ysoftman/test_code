// ysoftman
// plugin .so 생성
// main()
// go build -buildmode=plugin -o plugin_module.so
package main

import "fmt"

var Var1 string

func PringHello() {
	fmt.Println("hello plugin Var1=", Var1)
}

func Add(a, b int) int {
	c := a + b
	fmt.Println(a, "+", b, "=", c)
	return c
}

func main() {
}
