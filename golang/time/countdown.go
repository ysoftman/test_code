package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Println("Count Down")
	for i := 3; i >= 0; i-- {
		time.Sleep(1 * time.Second)
		fmt.Println(i)
	}
}
