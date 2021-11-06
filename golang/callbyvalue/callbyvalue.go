// ysoftman
// call by value test

package main

import "fmt"

type myData struct {
	valint int
	valstr string
}

func main() {
	a := 1

	// 참고로 golang 에는 다음과 같은 참조 변수가 없다.
	// var &b = a
	// &연산자로 주소값을 가지는 변수가 있지만 그 변수 자체가 별도의 주소를 가지고 있기 때문에 참조변수는 아니다
	// https://dave.cheney.net/2017/04/29/there-is-no-pass-by-reference-in-go

	func1(a)
	fmt.Printf("main, a: %#v\n", a)
	func2(&a)
	fmt.Printf("main, a: %#v\n", a)

	data := myData{
		valint: 10,
		valstr: "ysoftman",
	}
	fmt.Printf("main, data: %#v\n", data)
	funcCallByValue(data)
	fmt.Printf("main, data: %#v\n", data)
	funcCallByReference(&data)
	fmt.Printf("main, data: %#v\n", data)

}

func func1(a int) {
	a = 123
	fmt.Printf("func1, a: %#v\n", a)
}

func func2(a *int) {
	*a = 55
	fmt.Printf("func2, a: %#v\n", *a)
}

// call by value
func funcCallByValue(data myData) {
	data.valint = 20
	data.valstr = "lemon"
	fmt.Printf("funcCallByValue, data: %#v\n", data)
}

// call by reference
func funcCallByReference(data *myData) {

	// To access the field X of a struct when we have the struct pointer p we could write (*p).X. However, that notation is cumbersome, so the language permits us instead to write just p.X, without the explicit dereference.
	// https://tour.golang.org/moretypes/4
	// (*data).valint = 100
	data.valint = 99
	data.valstr = "apple"
	fmt.Printf("funcCallByReference, data: %#v\n", data)
}
