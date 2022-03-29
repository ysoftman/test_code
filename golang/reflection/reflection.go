// author : ysoftman
// encoding : utf-8
// title : 리플렉션 테스트

package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"log"
	"reflect"
)

type TheBox struct {
	user      string `aaa:"value1"`
	cnt       int
	extradata interface{}
}

func main() {
	fmt.Println("Relfection test...")
	getFieldInfo()
	makeStruct()

	strs := []string{"apple", "banana"}
	for _, v := range strs {
		fmt.Println("v:", v, " reflect.TypeOf(v)", reflect.TypeOf(v))
	}
}

func makeStruct() {
	type myvalue struct {
		a []int
	}

	var extradata *interface{}
	// https://golang.org/pkg/reflect/#StructField
	// reflect 로 TheBox 와 같은 구조체를 생성해보자
	mystruct := reflect.StructOf([]reflect.StructField{
		{
			// Export 되어야 해서 대문자로 시작하는 이름을 사용해야 한다.
			Name: "User",
			Type: reflect.TypeOf(string("")),
			Tag:  `json:"user"`,
		},
		{
			Name:      "Cnt",
			Type:      reflect.TypeOf(int(0)),
			Tag:       `json:"cnt"`,
			Anonymous: false,
			// embeded  field
			// struct in struct 이 필드 이름을지정하지 않고 struct 명만 명시하는것
			// AAA 를 embeded field 로 사용한 예시
			// type AAA struct {
			// 	a int
			// }
			// type b struct {
			// 	s string
			// AAA }
		},
		{
			Name: "Mv",
			Type: reflect.TypeOf(myvalue{}),
		},
		{
			// interface 타입으로 필드 생성하려면 interface{} 로 선언되 변수를 사용하자.
			Name: "Extradata",
			Type: reflect.TypeOf(extradata),
			Tag:  `json:"extra"`,
		},
	})
	fmt.Println("makeStruct:", mystruct)

	// 값 설정해보기
	v := reflect.New(mystruct).Elem()
	fmt.Println("v.Field(0).Type():", v.Field(0).Type())
	fmt.Println("v.Field(1).Type():", v.Field(1).Type())
	fmt.Println("v.Field(2).Type():", v.Field(2).Type())
	fmt.Println("v.Field(3).Type():", v.Field(3).Type())
	v.Field(0).SetString("ysoftman")
	v.Field(1).SetInt(999)
	mv := myvalue{
		a: []int{1, 2, 3},
	}
	v.Field(2).Set(reflect.ValueOf(mv))
	fmt.Println("v:", v)

	// v.Field(3) interface 로 선언된 필드는 아래 json decode 시 입력되도록 한다.
	s := v.Addr().Interface()
	jsonstr := `{"cnt":10,"user":"ysoftman", "extra":["lemon","orange"]}`
	json.Unmarshal([]byte(jsonstr), &s)
	fmt.Printf("s: %+v\n", s)

	// json string 으로 출력
	w := new(bytes.Buffer)
	if err := json.NewEncoder(w).Encode(s); err != nil {
		panic(err)
	}
	fmt.Printf("json: %s", w.Bytes())
}

func getFieldInfo() {
	myBox := TheBox{
		user:      "ysoftman",
		cnt:       99,
		extradata: []string{"a", "b"},
	}
	fmt.Printf("myBox ==> %+#v\n", myBox)

	// reflection 은 런타임시 대상 구조체(클래스),함수 등의 메모리는 알고 있지만 형식(타입)을 모를 경우
	// 분석하여 클래스 또는 변수의 이름, 타입, 값등을 파악할 수 있도록 해준다.
	// reflect.TypeOf 로 대상의 타입을 파악한다.
	myBoxReflectType := reflect.TypeOf(myBox)
	// reflect.ValueOf 로 대상의 저장된 값을 파악한다.
	myBoxReflectValue := reflect.ValueOf(myBox)

	// struct 이름
	fmt.Println("myBoxReflectType.Name():", myBoxReflectType.Name())
	// 필드 파악
	fmt.Println("myBoxReflectType.Field(0).Name:", myBoxReflectType.Field(0).Name)
	fmt.Println("myBoxReflectType.Field(0).Tag:", myBoxReflectType.Field(0).Tag)
	fmt.Println("myBoxReflectType.Field(0).Type:", myBoxReflectType.Field(0).Type)
	fmt.Println("myBoxReflectType.Field(0).Type.Kind():", myBoxReflectType.Field(0).Type.Kind())
	if myBoxReflectType.Field(0).Type.Kind() == reflect.String {
		fmt.Println("myBoxReflectType.Field(0).Type.Kind() == reflect.String")
		fmt.Println("myBoxReflectValue.Field(0).String():", myBoxReflectValue.Field(0).String())
	}
	fmt.Println("myBoxReflectType.Field(1).Name:", myBoxReflectType.Field(1).Name)
	fmt.Println("myBoxReflectType.Field(1).Tag:", myBoxReflectType.Field(1).Tag)
	fmt.Println("myBoxReflectType.Field(1).Type:", myBoxReflectType.Field(1).Type)
	fmt.Println("myBoxReflectType.Field(1).Type.Kind():", myBoxReflectType.Field(1).Type.Kind())
	if myBoxReflectType.Field(1).Type.Kind() == reflect.Int {
		fmt.Println("myBoxReflectType.Field(1).Type.Kind() == reflect.Int")
		fmt.Println("myBoxReflectValue.Field(1).Int():", myBoxReflectValue.Field(1).Int())
	}

	fmt.Println("myBoxReflectType.Field(2).Name:", myBoxReflectType.Field(2).Name)
	fmt.Println("myBoxReflectType.Field(2).Tag:", myBoxReflectType.Field(2).Tag)
	fmt.Println("myBoxReflectType.Field(2).Type:", myBoxReflectType.Field(2).Type)
	fmt.Println("myBoxReflectType.Field(2).Type.Kind():", myBoxReflectType.Field(2).Type.Kind())
	if myBoxReflectType.Field(2).Type.Kind() == reflect.Interface {
		fmt.Println("myBoxReflectType.Field(2).Type.Kind() == reflect.Interface")
		fmt.Println("myBoxReflectValue.Field(2).Elem():", myBoxReflectValue.Field(2).Elem())
		fmt.Println("myBoxReflectValue.Field(2).Elem().Slice(0,2):", myBoxReflectValue.Field(2).Elem().Slice(0, 2))
	}

	// 타입 내부의 변수명으로 필드를 가져올 수 도 있다.
	myBoxFieldByName, ret := myBoxReflectType.FieldByName("user")
	if ret == false {
		log.Fatal("can't find the 'name' field.")
	}
	fmt.Println("myBoxFieldByName.Name:", myBoxFieldByName.Name)
	fmt.Println("myBoxFieldByName.Type:", myBoxFieldByName.Type)
	fmt.Println("myBoxFieldByName.Tag:", myBoxFieldByName.Tag)

}
