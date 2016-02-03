// author : ysoftman
// encoding : utf-8
// title : Infite Writer
// desc : 디스크(USB)에 무한 쓰기 작업을 수행하는 스트레스 테스터 프로그램
package main

import "fmt"
import "os"
import "strconv"

func main() {
	fmt.Println("[Usage] " + os.Args[0] + " limit-MBytes loop-cnt")
	fmt.Println("ex) write 100 MBytes to current drive for 50 times")
	fmt.Println(os.Args[0] + " 100 50")

	// 인자 체크
	if len(os.Args) != 3 {
		fmt.Println("args != 3")
		os.Exit(1)
	}
	fmt.Println("Args[0]:", os.Args[0])
	fmt.Println("Args[1]:", os.Args[1])
	fmt.Println("Args[2]:", os.Args[2])

	limit, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Println("can't read limit bytes size")
		os.Exit(1)
	}

	loopcnt, err := strconv.Atoi(os.Args[2])
	if err != nil {
		fmt.Println("can't read loop cnt")
		os.Exit(1)
	}

	// MB 단위로 취급
	limit *= 1000 * 1000
	data := make([]byte, limit)

	// 반복해서 파일 생성(다시쓰기)
	for i := 1; i <= loopcnt; i++ {
		fmt.Printf("%d/%d\n", i, loopcnt)

		// 더미 파일 생성
		fpDummy, err := os.Create("dummyfile")
		if err != nil {
			fmt.Println("can't crate file")
			os.Exit(1)
		}
		fpDummy.Write(data)
		fpDummy.Close()

	}

}
