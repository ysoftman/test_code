// ysoftman
// struct copy test
package main

import (
	"fmt"
)

type mystruct struct {
	str    string
	num    int
	fruits []string
}

func main() {

	myst1 := mystruct{"ysoftman", 123, []string{"lemon", "apple", "banana"}}
	// shallow copy 된다.
	myst2 := myst1
	fmt.Println("shallow copy")
	// 일반 변수들은 복사되어 myst2 와 별개가 되지만
	myst2.str = "bill"
	myst2.num = 999
	// 슬라이스의 경우는 참조되고 있기때문에 myst1 에도 영향이 있다.
	myst2.fruits[0] = "orange"
	fmt.Printf("myst1 %#v\n", myst1)
	fmt.Printf("myst2 %#v\n", myst2)

	fmt.Println("")

	// 슬라이스 필드는 make 로 생성하여 복사해야 deep copy 가 된다.
	myst2.fruits = make([]string, len(myst1.fruits))
	copy(myst2.fruits, myst1.fruits)
	fmt.Println("deep copy")
	myst2.fruits[0] = "strawberry"
	// deep copy 되어 myst2.fruits 가 변경되어도 myst1.fruits 는 영향을 받지 않는다.
	fmt.Printf("myst1 %#v\n", myst1)
	fmt.Printf("myst2 %#v\n", myst2)
}
