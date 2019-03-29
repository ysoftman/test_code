// ysoftman
// toml 테스트
// go get github.com/BurntSushi/toml
package main

import (
	"fmt"
)

func main() {
	fmt.Println("toml parser test...")

	parseZone()
	fmt.Println()

	parseFruits()
	fmt.Println()

	parseFruitsMapChild()
	fmt.Println()

	parseSongs()
	fmt.Println()
}
