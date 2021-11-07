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

	funcCallByValue1(a)
	fmt.Printf("main, %p a: %#v\n", &a, a)
	funcCallByReference1(&a)
	fmt.Printf("main, %p a: %#v\n", &a, a)

	fmt.Println()
	data := myData{
		valint: 10,
		valstr: "ysoftman",
	}
	fmt.Printf("main, %p data: %#v\n", &data, data)
	funcCallByValue2(data)
	fmt.Printf("main, %p data: %#v\n", &data, data)
	funcCallByReference2(&data)
	fmt.Printf("main, %p data: %#v\n", &data, data)

	fmt.Println()
	arr := [...]int{10, 20, 30, 40, 50}
	funcCallByValue3(arr)
	fmt.Printf("main, %p arr: %#v\n", &arr, arr)
	funcCallByReference3(&arr)
	fmt.Printf("main, %p arr: %#v\n", &arr, arr)

	fmt.Println()
	slice := []int{10, 20, 30, 40, 50}
	funcCallByValue4(slice)
	fmt.Printf("main, %p slice: %#v\n", &slice, slice)
	funcCallByReference4(&slice)
	fmt.Printf("main, %p slice: %#v\n", &slice, slice)
}

func funcCallByValue1(a int) {
	a = 123
	fmt.Printf("funcCallByValue1, %p a: %#v\n", &a, a)
}

func funcCallByReference1(a *int) {
	*a = 55
	fmt.Printf("funcCallByReference1, %p a: %#v\n", a, *a)
}

func funcCallByValue2(data myData) {
	data.valint = 20
	data.valstr = "lemon"
	fmt.Printf("funcCallByValue2, %p data: %#v\n", &data, data)
}

func funcCallByReference2(data *myData) {
	// To access the field X of a struct when we have the struct pointer p we could write (*p).X. However, that notation is cumbersome, so the language permits us instead to write just p.X, without the explicit dereference.
	// https://tour.golang.org/moretypes/4
	// (*data).valint = 100
	data.valint = 99
	data.valstr = "apple"
	fmt.Printf("funcCallByReference2, %p data: %#v\n", data, data)
}

func funcCallByValue3(arr [5]int) {
	arr[1] = 100
	fmt.Printf("funcCallByValue3, %p arr: %#v\n", &arr, arr)
}

func funcCallByReference3(arr *[5]int) {
	(*arr)[0] = 90
	fmt.Printf("funcCallByReference3, %p arr: %#v\n", arr, arr)
}

// slice 의 내부 포인터가 있기 때문에 다음과 같은 형태로도 수정된값이 반영된다.
func funcCallByValue4(slice []int) {
	slice[1] = 100
	fmt.Printf("funcCallByValue4, %p slice: %#v\n", &slice, slice)
}

func funcCallByReference4(slice *[]int) {
	(*slice)[0] = 90
	fmt.Printf("funcCallByReference4, %p slice: %#v\n", slice, slice)
}
