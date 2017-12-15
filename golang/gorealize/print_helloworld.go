// ysoftman
// realize 에서 사용할 테스트 파일
package main

import "fmt"
import "os"

func main() {
	if len(os.Args) < 2 {
		fmt.Println("there is no argurment")
		os.Exit(0)
	}

	msg := "just print  "
	msg += os.Args[1]
	fmt.Println(msg)
}
