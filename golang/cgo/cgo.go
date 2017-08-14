// author : ysoftman
// encoding : utf-8
// title : cgo 패키지 테스트

// package 와 import "C" 사이에 주석으로 C 코드를 작성해 놓는다.
// mac 환경에서 go 1.7.4 버전에서 signal: killed 에러가 발생함
// go 1.8.2 버전으로 업그레이 후 해결
package main

/*
#include <stdio.h>

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
	// 위 주석으로 작성된 C 함수 호출
	result := C.sum(1, 2)
	fmt.Println(result)
	C.print_int(result)
}
