package main

import "fmt"

// type casting 은 다른 데이터 타입 변환을 하지만 보장은 되지 않는다.
func main() {
	num1 := 123
	fmt.Printf("%T %v\n", num1, num1)
	num2 := int32(num1)
	fmt.Printf("%T %v\n", num2, num2)
	num3 := int64(num1)
	fmt.Printf("%T %v\n", num3, num3)
	num4 := float32(num1)
	fmt.Printf("%T %v\n", num4, num4)
	num5 := byte(num1)
	fmt.Printf("%T %v\n", num5, num5)
	num6 := rune(num1)
	fmt.Printf("%T %v\n", num6, num6)
	// conversion from int to string yields a string of one rune, not a string of digits (did you mean fmt.Sprint(x)?)stringintconv
	num7 := string(num1)
	fmt.Printf("%T %v\n", num7, num7)
	num8 := fmt.Sprint(num1)
	fmt.Printf("%T %v\n", num8, num8)
	// cannot convert num1 (type int) to type bool
	// num9 := bool(num1)
	// fmt.Printf("%T %v\n", num9, num9)

	fmt.Println("-----")
	str1 := "ysoftman"
	fmt.Printf("%T %v\n", str1, str1)
	// cannot convert str1 (type string) to type rune
	// str2 := rune(str1)
	str2 := rune(str1[0]) // rune is alias of int32
	fmt.Printf("%T %v %c\n", str2, str2, str2)
	str3 := byte(str1[0])
	fmt.Printf("%T %v %c\n", str3, str3, str3)
	// cannot convert str1 (type string) to type bool
	// str4 := bool(str1)
	// fmt.Printf("%T %v %c\n", str4, str4, str4)
}
