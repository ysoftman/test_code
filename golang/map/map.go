// ysoftman
// map 사용
package main

import "fmt"

func main() {
	// mymap 은 맵을 참조하고 있고 nil 상태이다.
	var mymap map[int](string)
	// nil 상태의 mymap 은 쓸 수 없어 make 로 초기화해야 한다.
	mymap = make(map[int]string)
	mymap[10] = "number10"
	mymap[20] = "number20"
	fmt.Println(mymap)

	// 맵에서 값을 가져올때는 value 와 값 존재여부의 bool 을 리턴한다.
	value, exist := mymap[10]
	if exist {
		fmt.Println(value)
	} else {
		fmt.Println("Not Exist 10")
	}
	value, exist = mymap[15]
	if exist {
		fmt.Println(value)
	} else {
		fmt.Println("Not Exist 15")
	}

	// element 삭제, delete builtin 함수로 리턴이 없다, 키가 없다면 아무동작 하지 않는다.
	fmt.Println("delete element(key:20)")
	delete(mymap, 20)
	fmt.Println(mymap)
}
