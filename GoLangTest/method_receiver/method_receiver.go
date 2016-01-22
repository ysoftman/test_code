// author : ysoftman
// encoding : utf-8
// title : method receiver test

package main

import ysoftman "fmt" // alias 로 선언

type Vector struct {
	x int
	y int
	z int
}

// go 에는 클래스가 없지만 method receiver 를 사용하여 구조체에 함수를 붙일 수 있다.
func (v Vector) add() int {
	return v.x + v.y + v.z
}

type myData int64

// 사용자가 정의한 타입에도 함수를 붙일 수 있다.
func (data myData) add(x, y int) int {
	return x + y
}

func main() {
	// 구조체에 함수를 사용
	vec := Vector{1, 2, 3}
	ysoftman.Println(vec.add())

	// 사용자 정의 타입에 함수를 사용
	var1 := myData(10)
	ysoftman.Println(var1.add(1, 2))
}
