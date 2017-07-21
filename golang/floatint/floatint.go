// ysoftman
// float int 처리 테스트
package main

import "fmt"

func main() {
	op1 := 2
	op2 := 5
	fmt.Printf("op1:%v %f\n", op1, float32(op1))
	fmt.Printf("op2:%v %f\n", op2, float32(op2))
	fmt.Printf("op2-op1:%v %f\n", op2-op1, float32(op2-op1))
	fmt.Printf("op2/op1:%v %f\n", op2/op1, float32(op2/op1))
	fmt.Printf("op2/op1:%v %f\n", op2/op1, float32(op2)/float32(op1))
}
