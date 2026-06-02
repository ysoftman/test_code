package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
)

type JsonData struct {
	StrVal    string  `json:"strval"`
	IntVal1   int64   `json:"intval1"`
	IntVal2   int64   `json:"intval2"`
	IntVal3   int64   `json:"intval3"`
	FloatVal1 float64 `json:"floatval1"`
	FloatVal2 float64 `json:"floatval2"`
	FloatVal3 float64 `json:"floatval3"`
}

func main() {
	fmt.Println("json float field test")
	data, _ := ioutil.ReadFile("json_sample.json")
	fmt.Println(string(data))
	var v JsonData

	// json number 타입에서
	// 큰 정수값은 2^64(9223372036854775808 ~ 9223372036854775807) 넘어가면 0, 큰 실수값은 그 범위 까지만 표현된다.
	json.Unmarshal(data, &v)
	fmt.Printf("%#v", v)
}
