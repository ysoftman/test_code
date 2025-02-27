// author : ysoftman
// encoding : utf-8
// title : os 패키지 테스트
package main

import (
	"fmt"
	"io"
	"os"
	"os/exec"
)

func main() {
	runExternalCommand()

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
	// 0 > 경우 비정상 종료로 처리
	//	os.Exit(-1)
	// 정상종료로 처리
	os.Exit(0)
}

func runExternalCommand() {
	fmt.Println("runExternalCommand - start")
	cmd := exec.Command("sleep", "2")
	fmt.Printf("cmd: %v\n", cmd)
	// 명령이 끝날때까지 기다린다.
	if err := cmd.Run(); err != nil {
		fmt.Println("[error run sleep]", err)
	}

	cmd = exec.Command("echo", "orange", "lemon")
	fmt.Printf("cmd: %v\n", cmd)
	stdout, err := cmd.StdoutPipe()
	if err != nil {
		fmt.Println("[error echo StdoutPipe]", err)
	}
	// 명령이 끝날때까지 기다리지 않는다.
	if err := cmd.Start(); err != nil {
		fmt.Println("[error run echo]", err)
	}
	stdbytes, err := io.ReadAll(stdout)
	if err != nil {
		fmt.Println("[error echo readall stdout]", err)
	}
	// 명령이 끝날때 까지 기다린다.
	cmd.Wait()
	fmt.Println(string(stdbytes))

	cmd = exec.Command("bash", "-c", "echo pwd:${PWD}; echo home:${HOME};")
	fmt.Printf("cmd: %v\n", cmd)
	stdout, err = cmd.StdoutPipe()
	if err != nil {
		fmt.Println("[error bash StdoutPipe]", err)
	}
	// 명령이 끝날때까지 기다리지 않는다.
	if err := cmd.Start(); err != nil {
		fmt.Println("[error start bash]", err)
	}
	stdbytes, err = io.ReadAll(stdout)
	if err != nil {
		fmt.Println("[error bash readall stdout]", err)
	}
	// 명령이 끝날때 까지 기다린다.
	cmd.Wait()
	fmt.Println(string(stdbytes))
	fmt.Println("runExternalCommand - end")
}
