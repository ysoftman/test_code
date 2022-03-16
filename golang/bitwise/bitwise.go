package main

import "fmt"

func main() {
	a := 5 // 0101
	fmt.Printf("%5d %10b\n", a, a)
	// golang 에는 not 비트연산자(C 에서는 ~)가 없어 XOR 를 이용해 구한다.
	// 0101 -> 1111 XOR 101 -> 1010
	fmt.Printf("%5d %10b\n", 0xf^a, 0xf^a)

	// XOR 를 단항연산으로 사용시 보수를 구할 수 있다.
	// https://go.dev/ref/spec#Arithmetic_operators
	// +x                          is 0 + x
	// -x    negation              is 0 - x
	// ^x    bitwise complement    is m ^ x  with m = "all bits set to 1" for unsigned x
	//                                       and  m = -1 for signed x
	// 양수 -> 음수, MSB(Most Significant Bit) 는 음수가 된다.
	// a 는 signed 값이라 -1 과 xor 한다.
	// 0101 ^ 1001 (-1) => 1100 + 1 => 1101
	fmt.Printf("%5d %10b\n", ^a+1, ^a+1)
	// 음수 -> 양수, MSB(Most Significant Bit) 는 양수가 된다.
	// 1101 ^ 1001 (-1) => 0100 + 1 => 0101
	a *= -1
	fmt.Printf("%5d %10b\n", ^a+1, ^a+1)
}
