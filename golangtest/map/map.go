// ysoftman
// map 사용
package main

import "fmt"

func main() {
	var mymap map[int](string)
	mymap = make(map[int]string)
	mymap[10] = "number10"
	mymap[20] = "number20"
	fmt.Println(mymap)
}
