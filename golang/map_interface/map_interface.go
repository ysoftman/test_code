package main

import "fmt"

func main() {
	// 일반 맵은 make 로 빈맵을 생성해야 한다.
	// 값이 정의한 타입으로만 사용할 수 있다.
	// normalmap := map[string]string
	normalmap := make(map[string]string)
	normalmap["aa"] = "lemon"
	normalmap["aa"] = "lemon-juice"
	normalmap["bb"] = "orange-juice"
	fmt.Println(normalmap)

	// 값이 interface 인 빈맵은 make 없이 생성한다.
	// 값이 interface{}이면 어떤 타입이도 자유롭게 사용할 수 있다.
	mi := map[string]interface{}{}
	mi["num"] = 123
	mi["num"] = 999
	mi["string"] = "abc"
	mi["a"] = struct {
		a int
		b int
		c string
		d struct {
			innera int
			innerb string
		}
	}{
		a: 1,
		b: 2,
		c: "c",
		d: struct {
			innera int
			innerb string
		}{
			innera: 3,
			innerb: "inner",
		},
	}
	mi["b"] = struct {
		aaa int
		bbb string
	}{
		aaa: 1,
		bbb: "lemon",
	}
	// fmt.Printf("%#v\n", mi)
	fmt.Println(mi)
}
