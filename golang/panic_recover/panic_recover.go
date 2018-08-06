// ysoftman
// recover 테스트

package main

import (
	"fmt"
	"log"
	"os"
)

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
		r := recover()
		if r != nil {

			// 패닉 내용 파일로 쓰기
			fp, err := os.OpenFile("panic.log", os.O_RDWR|os.O_APPEND|os.O_CREATE|os.O_SYNC, 0644)
			if err != nil {
				fmt.Println("open file error...", err)
			}
			defer fp.Close()
			log.SetOutput(fp)
			log.Println(r)

			fmt.Println(r)
		}
		fmt.Println("defer end")
	}()
	// panic: runtime error: integer divide by zero
	c := a / b
	fmt.Printf("%d / %d = %d\n", a, b, c)
}
