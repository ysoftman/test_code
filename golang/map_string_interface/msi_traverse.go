package main

import (
	"fmt"
)

type innerAData struct {
	innera int
	innerb string
}
type AData struct {
	a int
	b int
	c string
	d innerAData
}

func traverse() {
	fmt.Println("----- msi traverse -----")
	// 값이 interface 인 빈맵은 make 없이 생성한다.
	// 값이 interface{}이면 어떤 타입이도 자유롭게 사용할 수 있다.
	mi := map[string]interface{}{}
	mi["num"] = 123
	mi["num"] = 999
	mi["string"] = "abc"
	mi["a"] = AData{
		a: 1,
		b: 2,
		c: "c",
		d: innerAData{
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

	traverseMI(mi)
}

func traverseMI(mi map[string]interface{}) {
	for k, v := range mi {
		switch v.(type) {
		case string:
			fmt.Printf("key(%v) : string(%v)\n", k, v.(string))
		case int:
			fmt.Printf("key(%v) : int(%v)\n", k, v.(int))
		case map[string]interface{}:
			fmt.Printf("map[string]interface{}")
			traverseMI(v.(map[string]interface{}))
		case interface{}:
			fmt.Printf("interface{} --> ")
			traverseI(v.(interface{}))
		}
	}
}

func traverseI(interf interface{}) {
	switch v := interf.(type) {
	case string:
		fmt.Printf("string(%v)\n", interf.(string))
	case int:
		fmt.Printf("int(%v)\n", interf.(int))
	case map[string]interface{}:
		fmt.Printf("map[string]interface{}")
		traverseMI(interf.(map[string]interface{}))
	case AData:
		fmt.Printf("Adata\n")
		temp := interf.(AData)
		fmt.Println(temp.d.innera)
		fmt.Println(temp.d.innerb)
	default:
		fmt.Println("unknown type:", v)
	}
}
