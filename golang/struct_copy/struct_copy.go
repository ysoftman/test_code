// ysoftman
// struct copy test
// go get "github.com/jinzhu/copier"
package main

import (
	"bytes"
	"encoding/gob"
	"fmt"
	"log"

	"github.com/jinzhu/copier"
)

type mystruct struct {
	str    string
	num    int
	fruits []string
}

type mystruct2 struct {
	Str    string
	Num    int
	Fruits []string
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

	fmt.Println("")

	// gob 를 이용한 struct copy
	// struct 필드들이 export(대문자로 시작)되어야 한다.
	usingGob()

	fmt.Println("")

	// copier 라이브러리 사용(동작안함)
	// usingCopier()
}

func usingGob() {
	myst1 := mystruct2{"ysoftman", 123, []string{"lemon", "apple", "banana"}}
	var buf bytes.Buffer
	enc := gob.NewEncoder(&buf)
	dec := gob.NewDecoder(&buf)

	// struct 필드들이 export(대문자로 시작)되어야 한다.
	err := enc.Encode(myst1)
	if err != nil {
		log.Fatal("encode myst1 error ", err.Error())
	}

	myst2 := mystruct2{}
	err = dec.Decode(&myst2)
	if err != nil {
		log.Fatal("decode myst2 error")
	}

	myst1.Fruits[0] = "zzz"
	fmt.Printf("%#v\n", myst1)
	fmt.Printf("%#v\n", myst2)
}

func usingCopier() {
	myst1 := mystruct{"ysoftman", 123, []string{"lemon", "apple", "banana"}}
	myst2 := mystruct{}
	err := copier.Copy(&myst2, &myst1)
	if err != nil {
		log.Fatal("copier.Copy error ", err)
	}

	myst1.fruits[0] = "zzz"
	fmt.Printf("%#v\n", myst1)
	fmt.Printf("%#v\n", myst2)
}
