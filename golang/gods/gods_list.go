package main

import (
	"fmt"

	"github.com/emirpasic/gods/lists/arraylist"
	dll "github.com/emirpasic/gods/lists/doublylinkedlist"
	"github.com/emirpasic/gods/utils"
)

func list_arraylist() {
	list := arraylist.New()
	list.Add("a") // ["a"]
	fmt.Println(list)
	list.Add("c", "b") // ["a","c","b"]
	fmt.Println(list)
	list.Sort(utils.StringComparator) // ["a","b","c"]
	fmt.Println(list)
	_, _ = list.Get(0) // "a",true
	fmt.Println(list.Get(0))
	_, _ = list.Get(100) // nil,false
	fmt.Println(list.Get(100))
	_ = list.Contains("a", "b", "c")      // true
	_ = list.Contains("a", "b", "c", "d") // false
	list.Swap(0, 1)                       // ["b","a",c"]
	list.Remove(2)                        // ["b","a"]
	list.Remove(1)                        // ["b"]
	list.Remove(0)                        // []
	list.Remove(0)                        // [] (ignored)
	_ = list.Empty()                      // true
	_ = list.Size()                       // 0
	list.Add("a")                         // ["a"]
	list.Clear()                          // []
	list.Insert(0, "b")                   // ["b"]
	list.Insert(0, "a")                   // ["a","b"]
}

func list_doublylinkedlist() {
	list := dll.New()
	list.Add("a") // ["a"]
	fmt.Println(list)
	list.Add("c", "b")                    // ["a","c","b"]
	list.Sort(utils.StringComparator)     // ["a","b","c"]
	_, _ = list.Get(0)                    // "a",true
	_, _ = list.Get(100)                  // nil,false
	_ = list.Contains("a", "b", "c")      // true
	_ = list.Contains("a", "b", "c", "d") // false
	list.Swap(0, 1)                       // ["b","a",c"]
	list.Remove(2)                        // ["b","a"]
	list.Remove(1)                        // ["b"]
	list.Remove(0)                        // []
	list.Remove(0)                        // [] (ignored)
	_ = list.Empty()                      // true
	_ = list.Size()                       // 0
	list.Add("a")                         // ["a"]
	list.Clear()                          // []
	list.Insert(0, "b")                   // ["b"]
	list.Insert(0, "a")                   // ["a","b"]
}
