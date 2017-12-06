// ysoftman
// random 사용하기
package main

import (
	"fmt"
	"math/rand"
	"time"
)

const randRange = 10

func main() {
	seed := time.Now().UnixNano()
	fmt.Println("random seed =", seed)
	rand.Seed(seed)
	fmt.Println("rand.Int() =", rand.Int())

	// randRange 의 모든 값을 랜덤으로 채워 넣기
	trycnt := 0
	var result []int
	for {
		bFind := false
		r := rand.Intn(randRange)
		fmt.Println("rand.Intn(10) =", r)
		for i := range result {
			if r == result[i] {
				bFind = true
			}
		}
		trycnt++
		if !bFind {
			result = append(result, r)
		}
		if len(result) == randRange {
			break
		}
	}
	fmt.Println("trycnt =", trycnt)
	fmt.Println("result =", result)
}
