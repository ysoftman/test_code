// author : ysoftman
// encoding : utf-8
// title : json 테스트
package main

import (
	"encoding/json"
	"fmt"
)

type obj1 struct {
	Aa string `json:"a"`
	Bb int    `json:"b"`
}

type obj2 struct {
	obj1
}

type obj3 struct {
	Cc obj1 `json:"c"`
}

func HasAIsAJSON() {
	var o1 obj1
	o1.Aa = "Aaa"
	o1.Bb = 123
	ms1, _ := json.Marshal(o1)
	fmt.Println("o1 = ", o1)
	fmt.Println("marshal(o1) = ", string(ms1))

	// is a 관계로 marshal
	var o2 obj2
	o2.Aa = "apple"
	o2.Bb = 100
	ms2, _ := json.Marshal(o2)
	fmt.Println("o2 = ", o2)
	fmt.Println("marshal(o2) = ", string(ms2))

	// is a 관계로 marshal
	var o3 obj3
	o3.Cc.Aa = "lemon"
	o3.Cc.Bb = 200
	ms3, _ := json.Marshal(o3)
	fmt.Println("o3 = ", o3)
	fmt.Println("marshal(o3) = ", string(ms3))
}
