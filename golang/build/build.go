// ysoftman
// build 인자 전달 테스트
// -ldflag 로 go link (go tool link) 시 인자를 전달 할 수 있다.
// -X importpath.name=value 형태로 패키지내의 변수에 값을 전달 할 수 있다.
// 다음과 같이 버전을 명시하는데 유용하다.
// go build -ldflags "-X main.var1=ysoftman -X main.version=1.2.3 -X main.buildtime=`date -u +%Y%m%d%H%M`"
// ./build
package main

import (
	"fmt"
)

var (
	var1      string
	version   string
	buildtime string
)

func main() {
	fmt.Println("build test")
	fmt.Println("var1", var1)
	fmt.Println("version", version)
	fmt.Println("buildtime", buildtime)
}
