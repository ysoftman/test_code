// ysoftman
// recover 테스트

package main

import "fmt"

func main() {
	fmt.Println("panic and recover...")
	fmt.Println("test start...")

	makePanicAndRecover(1, 0)

	fmt.Println("test end...")
}

func makePanicAndRecover(a int, b int) {

	// 패닉이 발생하면 모든 defer 를 실행한다.
	// defer 로 처리되는 함수에 recover 를 사용해서 패닉 메시지를 출력하고 프로그램을 계속 실행할 수 있다.
	// recover() defer 내에서 처리되이어야 한다.
	defer func() {
		err := recover()
		if err != nil {
			fmt.Println(err)
		}
		fmt.Println("defer end")
	}()
	// panic: runtime error: integer divide by zero
	c := a / b
	fmt.Printf("%d / %d = %d\n", a, b, c)
}
