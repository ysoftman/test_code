package main

import (
	"fmt"

	"golang.org/x/sync/syncmap"
)

func main() {
	// syncmap 은 자동 동기화 맵으로 concurrent 환경에서 사용
	smap := new(syncmap.Map)
	smap.Store("name", "ysoftman")
	smap.Store("phone", 123456789)
	smap.Store(1, "number1value")
	fmt.Println(smap)

	value, _ := smap.Load("name1")
	fmt.Println(value)

	value, _ = smap.Load("name")
	fmt.Println(value)
	value, _ = smap.Load("phone")
	fmt.Println(value)
	value, _ = smap.Load(1)
	fmt.Println(value)

	smap.Delete(1)
	value, _ = smap.Load(1)
	fmt.Println(value)

	i := 0

	out := make(map[interface{}]interface{})
	// Range 는 smap 각 (키,값)에 대해서 사용자가 구현한 함수를 호출한다.
	// 사용자가 함수에서는 key, value 를 받아 사용자가 정의한 map 에 담는다.
	smap.Range(func(key, value interface{}) bool {
		out[key] = value
		i++
		fmt.Println(i)
		return true
	})
	fmt.Println(out)
}
