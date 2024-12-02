// ysoftman
// call by value test
package main

import "fmt"

func main() {
	arr := [...]int{10, 20, 30, 40, 50}
	arrayCallByValue(arr)
	fmt.Printf("main, %p arr: %#v\n", &arr, arr)
	arrayCallByReference(&arr)
	fmt.Printf("main, %p arr: %#v\n", &arr, arr)
}

// array : default call by value
func arrayCallByValue(arr [5]int) {
	arr[1] = 100
	fmt.Printf("arrayCallByValue, %p arr: %#v\n", &arr, arr)
}

func arrayCallByReference(arr *[5]int) {
	(*arr)[0] = 90
	fmt.Printf("arrayCallByReference, %p arr: %#v\n", arr, arr)
}
