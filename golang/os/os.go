// author : ysoftman
// encoding : utf-8
// title : os 패키지 테스트
package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
)

func main() {
	// 현재 워킹 디렉토리
	cur_dir, _ := os.Getwd()
	fmt.Println("current directory =", cur_dir)

	// 워킹 디렉토리 변경
	err := os.Chdir("../")
	if err != nil {
		fmt.Println(err.Error())
	}
	cur_dir, _ = os.Getwd()
	fmt.Println("current directory =", cur_dir)

	// 인자 정보
	fmt.Println("Args =", len(os.Args))
	for i := 0; i < len(os.Args); i++ {
		fmt.Printf("Arg[%v] = %v", i, os.Args[i])
	}

	fmt.Println()

	runExternalComamnd()
	// 0 > 경우 비정상 종료로 처리
	//	os.Exit(-1)
	// 정상종료로 처리
	os.Exit(0)
}

func runExternalComamnd() {
	fmt.Println("runExternalComamnd - start")
	cmd := exec.Command("sleep", "2")

	// 명령이 끝날때까지 기다린다.
	if err := cmd.Run(); err != nil {
		fmt.Println("[error run sleep]", err)
	}

	cmd = exec.Command("echo", "orange", "lemon")
	stdout, err := cmd.StdoutPipe()
	if err != nil {
		fmt.Println("[error echo StdoutPipe]", err)
	}
	// 명령이 끝날때까지 기다리지 않는다.
	if err := cmd.Start(); err != nil {
		fmt.Println("[error run echo]", err)
	}
	stdbytes, err := ioutil.ReadAll(stdout)
	if err != nil {
		fmt.Println("[error echo readall stdout]", err)
	}
	// 명령이 끝날때 까지 기다린다.
	cmd.Wait()
	fmt.Println(string(stdbytes))

	cmd = exec.Command("bash", "-c", "echo $PWD")
	stdout, err = cmd.StdoutPipe()
	if err != nil {
		fmt.Println("[error bash StdoutPipe]", err)
	}
	// 명령이 끝날때까지 기다리지 않는다.
	if err := cmd.Start(); err != nil {
		fmt.Println("[error start bash]", err)
	}
	stdbytes, err = ioutil.ReadAll(stdout)
	if err != nil {
		fmt.Println("[error bash readall stdout]", err)
	}
	// 명령이 끝날때 까지 기다린다.
	cmd.Wait()
	fmt.Println(string(stdbytes))
	fmt.Println("runExternalComamnd - end")
}
