// author : ysoftman
// encoding : utf-8
// title : runtime 패키지 테스트
package main

import (
	"fmt"
	"runtime"
	"time"
)

func main() {
	fmt.Println("Go Version =", runtime.Version())
	fmt.Println("Go Root =", runtime.GOROOT())
	fmt.Println("NumOfCPUs =", runtime.NumCPU())
	// 프로그램에서 동시에 사용할 수 있는 cpu 개수 설정
	cur_setting_num := 2
	previous_setting_num := runtime.GOMAXPROCS(cur_setting_num)
	fmt.Println("set num of go cpus =", cur_setting_num, " preivous_setting_num =", previous_setting_num)
	sum1(1, 2)

	// cgo 개수
	fmt.Println("Current NumofCGo =", runtime.NumCgoCall())
	// 현재 생성된 고루틴 개수
	fmt.Println("Current NumofGoRoutines =", runtime.NumGoroutine())
	go myfunc1()
	go myfunc2()

	// cpu 가 다른 고 루틴을 우선 처리할 수 있도록 한다.
	runtime.Gosched()

	// 현재 생성된 고루틴 개수
	fmt.Println("Current NumofGoRoutines =", runtime.NumGoroutine())

	// 쓰레드 동작을 계속 확인하기 위해서 키입력 하면 프로그램 종료
	input := ""
	fmt.Scanln(&input)

	// 현재 생성된 고루틴 개수
	fmt.Println("Current NumofGoRoutines =", runtime.NumGoroutine())

	fmt.Println("end program...")
}

func sum1(a int, b int) int {
	// 스택 플레임에서 몇번재인지
	for skipNumOfFrame := 0; skipNumOfFrame < 5; skipNumOfFrame++ {
		// 이 함수를 호출한 곳의 정보(스택 정보)
		pc, file, line, ok := runtime.Caller(skipNumOfFrame)
		fmt.Println("caller)", "skipNumOfFrames =", skipNumOfFrame, " pc =", pc, " file=", file, " line=", line, " ok=", ok)
	}

	return a + b
}

func myfunc1() {
	for i := 0; i < 10; i++ {
		time.Sleep(time.Second)
		if i == 5 {
			// 고루틴 종료하려면 리턴시키거나 runtime.Goexit() 사용
			// return
			fmt.Println("go_routine1 exit")
			runtime.Goexit()

		}
		fmt.Println("go_routine1", i)
	}
}

func myfunc2() {
	for i := 0; i < 10; i++ {
		time.Sleep(time.Second)
		if i == 5 {
			// 고루틴 종료하려면 리턴시키거나 runtime.Goexit() 사용
			// return
			fmt.Println("go_routine2 exit")
			runtime.Goexit()
		}
		fmt.Println("go_routine2", i)
	}
}
