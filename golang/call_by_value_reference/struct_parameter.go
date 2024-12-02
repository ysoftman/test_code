package main

import "fmt"

type myData struct {
	valint int
	valstr string
}

// struct : (default) call by value
// call by value : struct 복사
// caller 쪽에 변경된 값이 반영되지 않는다.
func funcCallByValue(data myData) {
	data.valint = 20
	data.valstr = "lemon"
	fmt.Printf("funcCallByValue2, %p data: %#v\n", &data, data)
}

// call by reference : caller struct 참조
// 포인터 파라메터를 받아 caller 쪽에 변경된 값이 보인다.
func funcCallByReference(data *myData) {
	// To access the field X of a struct when we have the struct pointer p we could write (*p).X. However, that notation is cumbersome, so the language permits us instead to write just p.X, without the explicit dereference.
	// https://tour.golang.org/moretypes/4
	// (*data).valint = 100
	data.valint = 99
	data.valstr = "apple"
	fmt.Printf("funcCallByReference2, %p data: %#v\n", data, data)
}

func main() {
	data := myData{
		valint: 10,
		valstr: "ysoftman",
	}
	fmt.Printf("main, %p data: %#v\n", &data, data)
	funcCallByValue(data)
	fmt.Printf("main, %p data: %#v\n", &data, data)
	funcCallByReference(&data)
	fmt.Printf("main, %p data: %#v\n", &data, data)
}
