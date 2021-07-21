// ysoftman
// type assertion  테스트
package main

import (
	"fmt"
)

type mytype struct {
	x int
	y int
}

func main() {

	// x 는 int 형인 동적타입으로 선언되었고 99 값을 가지고 있다.
	var x interface{} = 99

	// x는 nil 이 아니며 int 타입인것을 assert(단정) 한다는 의미
	// x가 nil 이거나 int 가 아니면 런타임 에러 panic 발생
	// panic: interface conversion: interface {} is int, not float32
	// illegal := x.(float32)
	// fmt.Println(illegal)

	// x가 nil 도 아니고 int 타입이라면 int 형의  x 값을 리턴
	intType, ok := x.(int)
	fmt.Println(intType, ok)

	// interface x 에 다른 타입의 값을 계속해서 덮어 쓸 수 있다.c/c++ void*와 같음
	x = 1.23
	floatType, ok := x.(float64)
	fmt.Println(floatType, ok)
	x = float32(1.23)
	floatType2 := x.(float32)
	fmt.Println(floatType2)

	// struct 타입도 가능하다.
	mt := mytype{
		x: 1,
		y: 2,
	}
	x = mt
	mType := x.(mytype)
	fmt.Println(mType)

	// []struct 타입도 가능하다.
	var mtlist []mytype
	mtlist = append(mtlist, mt)
	mtlist = append(mtlist, mt)
	x = mtlist
	mType2 := x.([]mytype)
	fmt.Println(mType2)
}
