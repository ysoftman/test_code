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
	user string `aaa:"value1"`
	cnt  int
}

func main() {
	fmt.Println("Relfection test...")
	myBox := TheBox{
		user: "ysoftman",
		cnt:  99,
	}
	fmt.Printf("myBox ==> %+#v\n", myBox)

	// reflection 은 런타임시 대상 구조체(클래스),함수 등의 메모리는 알고 있지만 형식(타입)을 모를 경우
	// 분석하여 클래스 또는 변수의 이름, 타입등을 파악할 수 있도록 해준다.
	// reflect.TypeOf 로 대상의 타입을 파악한다.
	myBoxReflectType := reflect.TypeOf(myBox)

	// struct 이름
	fmt.Println("myBoxReflectType.Name():", myBoxReflectType.Name())
	// 필드 파악
	fmt.Println("myBoxReflectType.Field(0).Name:", myBoxReflectType.Field(0).Name)
	fmt.Println("myBoxReflectType.Field(0).Type:", myBoxReflectType.Field(0).Type)
	fmt.Println("myBoxReflectType.Field(0).Tag:", myBoxReflectType.Field(0).Tag)
	fmt.Println("myBoxReflectType.Field(1).Name:", myBoxReflectType.Field(1).Name)
	fmt.Println("myBoxReflectType.Field(1).Type:", myBoxReflectType.Field(1).Type)
	fmt.Println("myBoxReflectType.Field(1).Tag:", myBoxReflectType.Field(1).Tag)

	// 타입 내부의 변수명으로 필드를 가져올 수 도 있다.
	myBoxFieldByName, ret := myBoxReflectType.FieldByName("user")
	if ret == false {
		log.Fatal("can't find the 'name' field.")
	}
	fmt.Println("myBoxFieldByName.Name:", myBoxFieldByName.Name)
	fmt.Println("myBoxFieldByName.Type:", myBoxFieldByName.Type)
	fmt.Println("myBoxFieldByName.Tag:", myBoxFieldByName.Tag)

}
