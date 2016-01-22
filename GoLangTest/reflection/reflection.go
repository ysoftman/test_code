// author : ysoftman
// encoding : utf-8
// title : 리플렉션 테스트

package main

import (
	"fmt"
	"log"
	"reflect"
)

type TheBox struct {
	name string `key1:"value1", key2:123`
	cnt  int
}

func main() {
	fmt.Println("Relfection test...")
	myBox := TheBox{}

	// reflection 은 런타임시 대상 구조체(클래스),함수 등의 메모리는 알고 있지만 형식(타입)을 모를 경우
	// 분석하여 타입, 값등을 파악할 수 있도록 해준다.
	// reflect.TypeOf 로 대상의 타입을 파악한다.
	myBoxType := reflect.TypeOf(myBox)

	// 타입을 파악하고 첫번째 필드를 가져온다.
	myField := myBoxType.Field(0)
	fmt.Println("myBox.name:", myField.Tag.Get("key1"))
	// 타입 내부의 변수명으로 필드를 가져올 수 도 있다.
	myField2, ret := myBoxType.FieldByName("name")
	if ret == false {
		log.Fatal("can't find the 'name' field.")
	}

	fmt.Println("myBox.name:", myField2.Tag.Get("key1"))

}
