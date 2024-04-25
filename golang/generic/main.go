package main

import (
	"fmt"
	"time"
)

// generic - go 1.18 부터 사용 가능
type Number interface {
	// ~를 붙이면 해당 타입을 별칭으로 사용하는 모든것을 의미
	// ex) time.Duration --> type Duration int64
	int32 | ~int64 | float32 | float64 | string
}

func add[T Number](a, b T) T {
	return a + b
}
func add2[T int | int32 | int64](a, b T) T {
	var result T
	result = a + b
	result += 10_000
	return result
}

// any 는 모든 타입을 의미 하지만 모든 타입이 + oprator 가 있는것은 아니니 + 를 사용할순 없다
func add3[T any](a, b T) (T, T) {
	fmt.Println("operator + not defined on a (variable of type T constrained by any)")
	return a, b
}
func main() {
	fmt.Println("generic test...")
	fmt.Println(add(int32(1), int32(2)))
	fmt.Println(add(float32(1), float32(2)))
	fmt.Println(add(time.Duration(1), time.Duration(2)))
	fmt.Println(add("aaa", "bbb"))
	// Number 에 int 은 정의하지 않아 동작은 안됨
	fmt.Println(add2(1, 2))
	fmt.Println(add2(int(1), int(2)))
	fmt.Println(add3(1, 2))
}
