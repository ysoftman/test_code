// author : ysoftman
// encoding : utf-8
// title : cgo 패키지 테스트
// 자세한 설명 https://golang.org/cmd/cgo/
// package 와 import "C" 사이에 주석으로 C 코드를 작성해 놓는다.
// mac 환경에서 go 1.7.4 버전에서 signal: killed 에러가 발생함
// go 1.8.2 버전으로 업그레이 후 해결
// #cgo 지시자를 이용해서 CFLAGS, CPPFLAGS, CXXFLAGS, FFLAGS LDFLAGS 옵셙 값을 설정 할 수 있다.
package main

/*
#cgo CFLAGS: -DPNG_DEBUG=1
#cgo amd64 386 CFLAGS: -DX86=1
#cgo LDFLAGS: -lpng

#include <stdio.h>
#include <png.h>

int sum(int a, int b)
{
	return a + b;
}

void print_int(int num)
{
	printf("%d\n", num);
}
*/
import "C"
import "fmt"

func main() {
	fmt.Println("cgo test")
	// 위 주석으로 작성된 C 함수 호출
	result := C.sum(1, 2)
	C.print_int(result)
}
