package main

import "fmt"

func main() {
	for i := 0; i <= 100; i++ {
		fmt.Println(i, isEven1(i), isEven2(i), isEven3(i), isEven4(i))
	}
}

func isEven1(n int) bool {
	return n%2 == 0
}

// and 연산으로 홀,짝 판별
// 2(10) & 1(01) = 0
// 3(11) & 1(01) = 1
func isEven2(n int) bool {
	return n&1 == 0
}

// or 연산으로 홀,짝 판별
// 2(10) | 1(01) = 11 > 2(10)
// 3(11) | 1(01) = 11 = 3(11)
func isEven3(n int) bool {
	return n|1 > n
}

// xor 연산으로 홀,짝 판별
// 2(10) ^ 1(01) = 11 = 2+1(11)
// 3(11) ^ 1(01) = 10 != 2+1(11)
func isEven4(n int) bool {
	return n|1 == n+1
}
