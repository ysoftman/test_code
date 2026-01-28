// author : ysoftman
// encoding : utf-8
// title : hello world

/*
// cross compilation, mac 용, linux 용 실행 바이너리 만들기
// Mac에서 리눅스용 ARM 바이너리를 만들 때 CGO_ENABLED=0을 붙여주는 것이 좋습니다.
// 기본적으로 Go는 표준 라이브러리 일부(네트워크, DNS 등)를 처리할 때 호스트 OS의 C 라이브러리를 사용하려고 시도하는데
// 이를 비활성화하면 대상 환경의 라이브러리에 의존하지 않는 정적 바이너리(Static Binary)가 생성되어 어디서든 에러 없이 실행됩니다.
CGO_ENABLED=0 GOOS=linux GOARCH=amd64 go build -o hello_world_linux_amd64 hello_world.go
CGO_ENABLED=0 GOOS=darwin GOARCH=arm64 go build -o hello_world_mac_arm64 hello_world.go
*/
package main

import "fmt"

func main() {
	fmt.Println("Hello world!")
}
