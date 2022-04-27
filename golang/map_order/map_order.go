package main

import (
	"fmt"
	"sort"
)

func main() {
	// go builtin map 은 unordered 로 hash table 을 사용해 O(1) 시간 복잡도를 가진다.
	// map 은 입력순서와 상관없이 키로 정렬되지 않은 상태로 저장된다.
	m1 := make(map[int]int, 0)
	m1[1231] = 100
	m1[982] = 200
	m1[34] = 300
	m1[413] = 400
	m1[14235] = 500

	// https://tip.golang.org/doc/go1.12  부터 fmt 로 map 을 출력하면 정렬 순서로 출력된다.
	fmt.Println("m1:", m1)

	// iterate 할때마다 다르게 출력된다.
	for k, v := range m1 {
		fmt.Println(k, v)
	}
	fmt.Println("---")
	for k, v := range m1 {
		fmt.Println(k, v)
	}
	fmt.Println("---")

	// key 만 따로 slice 저장해 정렬하고 정렬된 key slice 순서대로 map 을 접근해 iterate 하면 순서대로 순회할 수 있다.
	keys := []int{}
	for k := range m1 {
		keys = append(keys, k)
	}
	sort.Ints(keys)
	fmt.Println("sorted keys:", keys)
	for _, v := range keys {
		fmt.Printf("%v:%v\n", v, m1[v])
	}
}
