// ysoftman
// atoi 구현해보기
package main

import "fmt"

func main() {
	str := "1234567"
	n := atoi(str)
	fmt.Printf("str=%s, n:=%d", str, n)
}

func atoi(str string) (result int) {
	result = 0
	fmt.Println("Atoi()")

	for i := range str {
		result *= 10
		// result += int(str[i]) - 48
		result += int(str[i]) - '0'
		// fmt.Println(str[i], result)
	}

	return result
}
