// ysoftman
// math 테스트
package main

import (
	"fmt"
	"math"
)

func main() {
	fmt.Println("math.Abs(3-2)=", math.Abs(3-2))
	fmt.Println("math.Abs(1-2)=", math.Abs(3-2))
	fmt.Println("math.Cos(90.0)=", math.Cos(90.0))
	fmt.Println("math.Sqrt(4)=", math.Sqrt(4))
	fmt.Println("math.MaxFloat64=", math.MaxFloat64)
	fmt.Println("math.MaxFloat32=", math.MaxFloat32)
	fmt.Println("math.Ceil(10.5)=", math.Ceil(10.5))
	fmt.Println("math.Floor(10.5)=", math.Floor(10.5))
	fmt.Println("15/10=", 15/10)
	fmt.Println("float32(15)/float32(10)=", float32(15)/float32(10))
}
