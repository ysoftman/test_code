// author : ysoftman
// encoding : utf-8
// title : cgo 패키지 테스트
// 참고
// https://golang.org/cmd/cgo/
// https://github.com/golang/go/wiki/cgo
// package 와 import "C" 사이에 주석으로 C 코드를 작성해 놓는다.
// C 코드의 끝과 import "C" 사이에 공백줄이 있으면 안된다.
// import "C" 부분은 다른 패키지와 함께 import ( "C" "fmt") 과 같이 사용하면 안된다.
// mac 환경에서 go 1.7.4 버전에서 signal: killed 에러가 발생함
// go 1.8.2 버전으로 업그레이 후 해결
// #cgo 지시자를 이용해서 CFLAGS, CPPFLAGS, CXXFLAGS, FFLAGS LDFLAGS 옵셙 값을 설정 할 수 있다.
package main

/*
#cgo CFLAGS: -DPNG_DEBUG=1
#cgo amd64 386 CFLAGS: -DX86=1
#cgo LDFLAGS: -lpng

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

int sum(int a, int b)
{
	return a + b;
}

void print_int(int num)
{
	printf("[print by C] %d\n", num);
}

void print_string(char *str)
{
	printf("[print by C] %s\n", str);
}

char *modify_string(char *str)
{
	int len = strlen(str);
	printf("[print by C] strlen(%s) : %d\n", str, len);
	if (len > 0)
	{
		str[0] = '_';
		return str;
	}
	return NULL;
}
*/
import "C"

import (
	"fmt"
	"unsafe"
)

func main() {
	fmt.Println("cgo test")

	// https://github.com/golang/go/issues/975 이슈로 아직까지는 C 의 printf 를 바로 쓸 수 없다.
	// C.printf("aaaa")

	// 위 주석으로 작성된 C 함수 호출
	result := C.sum(1, 2)
	C.print_int(result)

	cint := C.int(10)
	C.print_int(cint)

	text := "this is test string"
	// Go string -> C String (*C.char 으로 malloc 으로 heap 에 할당된다.)
	cstr := C.CString(text)
	// CString 은 malloc 으로 사용하기 때문에 호출한쪽에서 free 해야 한다.
	defer C.free(unsafe.Pointer(cstr))

	C.print_string(cstr)
	cstr2 := C.modify_string(cstr)

	// // C string -> Go string
	gostr := C.GoString(cstr2)
	fmt.Println(gostr)
}
