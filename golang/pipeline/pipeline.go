// ysoftman
// stdin pipeline 테스트
package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

func main() {
	br := bufio.NewReader(os.Stdin)
	input, isprefix, err := br.ReadLine()
	if err != nil {
		log.Fatal("error isprefix:", isprefix)
	}
	fmt.Println(string(input))
}
