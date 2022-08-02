package main

import (
	"fmt"

	"github.com/emirpasic/gods/maps/hashmap"
)

func map_hashmap() {
	m := hashmap.New() // empty
	m.Put(1, "x")      // 1->x
	m.Put(2, "b")      // 2->b, 1->x (random order)
	m.Put(1, "a")      // 2->b, 1->a (random order)
	fmt.Println(m)
	_, _ = m.Get(2) // b, true
	_, _ = m.Get(3) // nil, false
	_ = m.Values()  // []interface {}{"b", "a"} (random order)
	_ = m.Keys()    // []interface {}{1, 2} (random order)
	m.Remove(1)     // 2->b
	m.Clear()       // empty
	m.Empty()       // true
	m.Size()        // 0
}
