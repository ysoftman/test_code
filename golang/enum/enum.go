// ysoftman
// enum 구현
// 참고 https://blog.learngoprogramming.com/golang-const-type-enums-iota-bc4befd096d3

package main

import "fmt"

type week int

// 모든 enum 마다 값을 설정하는경우
// const (
// 	Sunday   week = 1
// 	Monday        = 2
// 	Tuesday       = 3
// 	Wednesday     = 4
// 	Thursday      = 5
// 	Friday        = 6
// 	Saturday      = 7
// )

// iota 로 자동 증가값이 설정되도록 할 수 있다.
const (
	// 5부터 시작
	Sunday week = 5 + iota
	// 주석, 빈줄을 증가되지 않고 skip 된다.

	Monday
	Tuesday
	Wednesday
	Thursday
	Friday
	Saturday
)

type fruit int

const (
	// left shift 연산으로 증가하도록
	apple fruit = 1 << iota
	lemon
	pineapple
	banana
	mango
	strawberry
)

func printday(d week) {
	fmt.Println(d)
}

func printfruit(f fruit) {
	fmt.Println(f)
}

func main() {
	fmt.Println("[week]")
	printday(Sunday)
	printday(Monday)
	printday(Tuesday)
	printday(Wednesday)
	printday(Thursday)
	printday(Friday)
	printday(Saturday)

	// printday 는 week type 파라미터가 아니면 사용할 수 없다.
	// someday := 5
	// printday(someday)
	fmt.Println("[fruit]")
	printfruit(apple)
	printfruit(lemon)
	printfruit(pineapple)
	printfruit(banana)
	printfruit(mango)
	printfruit(strawberry)
}
