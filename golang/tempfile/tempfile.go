package main

import (
	"fmt"
	"log"
	"os"
	"path/filepath"
)

func main() {
	/*
		// os.TempDir() 는 다음 로직으로 정해진다.
		dir := Getenv("TMPDIR")
		if dir == "" {
			if runtime.GOOS == "android" {
				dir = "/data/local/tmp"
			} else {
				dir = "/tmp"
			}
		}
	*/
	fmt.Println("os.TempDir():", os.TempDir())
	// 첫번째 인자가 "" 이면 os.TempDir() 위치를 사용한다.
	tmpf, err := os.CreateTemp("", "patternString")
	if err != nil {
		log.Fatal("error!!! - ", err)
	}
	// Name() 은 path 가 포함
	fmt.Println("tmpf.Name():", tmpf.Name())
	fmt.Println("filepath.Base(tmpf.Name()):", filepath.Base(tmpf.Name()))
	fmt.Println("filepath.Dir(tmpf.Name()):", filepath.Dir(tmpf.Name()))
	os.RemoveAll(tmpf.Name())
	fmt.Println("deleted :", tmpf.Name())
	// time.Sleep(10 * time.Second)
}
