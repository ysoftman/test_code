// author : ysoftman
// encoding : utf-8
// title : chess queen path
// desc : 체스 퀸의 경로를 탐색해서 상대말을 잡을 수 있는지 체크

package main

import (
	"fmt"
	"math"
)

func main() {
	fmt.Println("Check Queen Path")

	checkTarget(0, 0, 1, 1)
	checkTarget(0, 0, 2, 1)
	checkTarget(0, 0, 3, 1)
	checkTarget(0, 0, 2, 2)

	checkTarget(0, 1, 1, 1)
	checkTarget(0, 1, 1, 2)
	checkTarget(0, 1, 1, 0)
	checkTarget(0, 1, 2, 2)
}

func checkTarget(Qx, Qy, Tx, Ty int) {
	fmt.Printf("Queen(%d %d) --> ", Qx, Qy)

	// 직선 체크
	if Qx == Tx || Qy == Ty {
		fmt.Printf("Target(%d, %d) UnSafe\n", Tx, Ty)
		return
	}
	// 대각선 체크
	if math.Abs(float64(Qx)-float64(Tx)) == math.Abs(float64(Qy)-float64(Ty)) {
		fmt.Printf("Target(%d, %d) UnSafe\n", Tx, Ty)
		return
	}
	fmt.Printf("Target(%d, %d) Safe\n", Tx, Ty)
}
