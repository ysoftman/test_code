package main

import "fmt"

func main() {
	// https://go.dev/blog/maps
	// map 은 pointer 나 slice 처럼 reference 타입으로 pointer(*) 로 사용할 필요가 없다.
	// map 크기가 변해도 최초 주소 공간이 변하지 않아 caller map과 같은 주소공간으로 유지(공유)된다.
	hashmap := map[int]int{0: 1}
	fmt.Printf("hashmap(%p) : %v\n", &hashmap, hashmap)
	modifyMapValue(hashmap)
	fmt.Printf("hashmap(%p) : %v\n", &hashmap, hashmap)
	addMapKeyValue(hashmap)
	fmt.Printf("hashmap(%p) : %v\n", &hashmap, hashmap)
}

func modifyMapValue(hm map[int]int) {
	hm[0] = 0
}
func addMapKeyValue(hm map[int]int) {
	hm[1] = 10
	for i := 0; i < 100; i++ {
		hm[i] = i
	}
}
