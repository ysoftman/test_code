package main

import "fmt"

func main() {
	// golang 에는 not 비트연산자(C 에서는 ~)가 없어 XOR 를 이용해 구한다.
	// XOR 를 단항연산으로 사용시 보수(not)를 구할 수 있다.
	// https://go.dev/ref/spec#Arithmetic_operators
	// +x                          is 0 + x
	// -x    negation              is 0 - x
	// ^x    bitwise complement    is m ^ x  with m = "all bits set to 1" for unsigned x
	//                                       and  m = -1 for signed x
	// 위 설명대로 ^x 는
	// x 가 unsigned 라면 0xfffff..(모든비트1) ^ x 로 동작하고
	// x 가 signed 라면 -1 ^ x 로 동작한다

	// not 구하기
	var aa uint = 5 // 0101
	fmt.Printf("%3d(%10b)\n", aa, aa)
	// 모든 비트가 1로 설정된 m 과 xor 되어 not(비트 반전, 1의보수)결과를 구할 수 있다.
	fmt.Printf("%3d(%10b)\n", ^aa, ^aa)
	// 0xf 등으로 xor 해서 비트 범위를 줄여서 not 결과를 만들 수도 있다.
	fmt.Printf("%3d(%10b)\n", 0xf^aa, 0xf^aa)

	bb := 5 // 0101
	// singed 형이라면 위 설명대로 -1 ^ bb 가 된다.
	fmt.Printf("%3d(%10b)\n", ^bb, ^bb)

	// 양수 -> 음수, MSB(Most Significant Bit) 는 음수가 된다.
	// bb 는 signed 라서 위 설명처럼 ^bb 하면 -1 과 xor 된다.
	// 여기에 +1(2의보수)를 하면 음수가 된다.
	fmt.Printf("%3d(%8b) -> %3d(%8b) -> %3d(%8b)\n", bb, bb, ^bb, ^bb, ^bb+1, ^bb+1)

	bb = -5
	// 음수 -> 양수, MSB(Most Significant Bit) 는 양수가 된다.
	// bb 는 signed 라서 위 설명처럼 ^bb 하면 -1 과 xor 된다.
	// 여기에 +1(2의보수)를 하면 양수가 된다.
	fmt.Printf("%3d(%8b) -> %3d(%8b) -> %3d(%8b)\n", bb, bb, ^bb, ^bb, ^bb+1, ^bb+1)
}
