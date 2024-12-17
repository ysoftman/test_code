package main

import (
	"encoding/json"
	"fmt"
	"log"

	"github.com/mitchellh/mapstructure"
)

type Etc struct {
	InnerA string
	InnerB int
}

type info struct {
	Name  string
	Fruit string
	Age   int
	Etc   struct {
		InnerA string
		InnerB int
	}
	List []string
}

func unmarshal() {
	fmt.Println("----- msi unmarshal -----")

	jsonstr := `{
		"name": "ysoftman",
		"fruit": "lemon",
		"age": 30,
		"etc": {
			"innerA" : "orange",
			"innerB" : 123
		},
		"list" : ["aa", "bb", "cc"]
	}
	`
	fmt.Println("jsonstr:", jsonstr)

	// map string interface 를 사용하면 스키마를 몰라도 unmarshal 할 수 있다.
	myinfo := make(map[string]interface{})
	if err := json.Unmarshal([]byte(jsonstr), &myinfo); err != nil {
		log.Fatal(err)
	}
	fmt.Println("myinfo:", myinfo)

	// msi -> struct 로 변환하기
	// 참고로 json 의 스키마를 알고 있다면 jsonstr -> struct 로 바로 unmarshal 하지만
	// struct -> 적절한 strcut 로 변환시 mapstructure 패키지를 사용하면 쉽게 변환
	myinfo2 := struct {
		// info 에 있는 필드들은 값이 채워진다.
		Name string
		Age  int
		List []string
		Zzz  string // info 에는 없는 필드로 값이 채워지 않음
	}{}
	if err := mapstructure.Decode(myinfo, &myinfo2); err != nil {
		log.Fatal(err)
	}
	fmt.Println("myinfo2:", myinfo2)
}
