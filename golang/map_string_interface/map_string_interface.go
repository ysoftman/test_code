package main

import (
	"fmt"
)

func main() {
	// 일반 맵은 make 로 빈맵을 생성해야 한다.
	// 값이 정의한 타입으로만 사용할 수 있다.
	// normalmap := map[string]string
	normalmap := make(map[string]string)
	normalmap["aa"] = "lemon"
	normalmap["aa"] = "lemon-juice"
	normalmap["bb"] = "orange-juice"
	fmt.Println(normalmap)

	create()
	unmarshal()
	traverse()
}
