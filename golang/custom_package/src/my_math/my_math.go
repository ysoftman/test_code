// Package my_math 패키지
// author : ysoftman
// encoding : utf-8
package my_math

import "fmt"

// 패키지 import 시 초기화
func init() {
	fmt.Println("my_math package initialization")
}

// 소문자로 시작하는 함수는 외부 패키지에서 접근할 수 없다.
func add(x int, y int) (result int) {
	fmt.Println("add() called.")
	return x + y
}

// Add 대문자로 시작하는 함수는 외부 패키지에서 접근할 수 있다.
func Add(x int, y int) (result int) {
	fmt.Println("Add() called.")
	return x + y
}
