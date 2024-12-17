// ysoftman
// recover 테스트

// https://golang.org/pkg/runtime/
// https://dave.cheney.net/tag/gotraceback
// GOTRACEBACK 의 레벨에 따라 스택 출력 내용이 달라진다. (go env 에선 안보임)
// GOTRACEBACK=none 모든 고루틴 스택 내용 출력 안함
// GOTRACEBACK=single 패닉 발생 고루린 스택만 출력
// GOTRACEBACK=all 현재돌고 있는 사용자 고루틴 모두 (default)
// GOTRACEBACK=system 시스템을 사용하는 고루틴 모두 출력
// GOTRACEBACK=crash 크래시 발생
// 실행)
// env GOTRACEBACK=all go run panic_recover.go
package main

import (
	"fmt"
	"log"
	"os"
	"runtime/debug"
	"time"
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
			fp1, err := os.OpenFile("panic1.log", os.O_RDWR|os.O_APPEND|os.O_CREATE|os.O_SYNC, 0644)
			if err != nil {
				fmt.Println("open file error...", err)
			}
			defer fp1.Close()
			log.SetOutput(fp1)
			log.Println(r)

			fp2, err := os.OpenFile("panic2.log", os.O_RDWR|os.O_APPEND|os.O_CREATE|os.O_SYNC, 0644)
			if err != nil {
				fmt.Println("open file error...", err)
			}
			defer fp2.Close()
			perr := fmt.Errorf("aaa_panic %v", r)
			fp2.WriteString(perr.Error() + "\n" + string(debug.Stack()))

			debug.PrintStack()
			fmt.Println(r)
		}
		fmt.Println("defer end")
	}()

	go func() {
		fmt.Println("1")
		time.Sleep(time.Second * 5)
		fmt.Println("2")
	}()
	go func() {
		fmt.Println("3")
		time.Sleep(time.Second * 5)
		fmt.Println("4")
	}()
	go func() {
		// panic: runtime error: integer divide by zero
		c := a / b
		fmt.Printf("%d / %d = %d\n", a, b, c)
	}()

	// go 루틴의 로직들이 수행되기전 종료되면 안된다.
	time.Sleep(time.Second * 10)
}
