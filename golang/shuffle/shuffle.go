// ysoftman
package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	l := []int{0, 1, 2, 3, 4}
	fmt.Println("l = ", l)

	rand.Seed(time.Now().UnixNano())

	// 셔플1 - Perm()
	fmt.Println("Perm():", rand.Perm(len(l)))

	// 셔플2 - Shuffle() golang 1.10 에서 생김
	l2 := make([]int, len(l))
	copy(l2, l)
	rand.Shuffle(len(l2), func(i, j int) {
		l2[i], l2[j] = l2[j], l2[i]
	})
	fmt.Println("Shuffle(): ", l2)

	// 셔플3 - Fisher Yates shuffle algorithm
	l3 := make([]int, len(l))
	copy(l3, l)
	for i := len(l3) - 1; i > 0; i-- {
		j := rand.Intn(i + 1)
		l3[i], l3[j] = l3[j], l3[i]
	}
	fmt.Println("FisherYates: ", l3)
}
