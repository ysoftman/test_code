package main

import (
	"fmt"
	"io"
	"log"
	"os"
	"strings"
	"sync"
	"time"
)

func write_file(wg *sync.WaitGroup, dst io.Writer, src string) {
	for i := 0; i < 5; i++ {
		fmt.Print(src)
		src := strings.NewReader(src)
		if _, err := io.Copy(dst, src); err != nil {
			log.Fatal(err)
		}
		time.Sleep(1 * time.Second)
	}
	wg.Done()
}

func main() {
	dst1, err := os.Create("out.tmp")
	if err != nil {
		log.Fatal(err)
	}
	defer dst1.Close()

	// dst2, err := os.Create("out.tmp")
	// O_EXCL 파일이 존재하지 않떄만 열 수 있도록 한다.
	dst2, err := os.OpenFile("out.tmp", os.O_RDWR|os.O_CREATE|os.O_EXCL, 0666)
	if err != nil {
		fmt.Println(err)
	}
	defer dst2.Close()

	wg := sync.WaitGroup{}
	wg.Add(1)
	go write_file(&wg, dst1, "aaaaa\n")
	if dst2 != nil {
		wg.Add(1)
		go write_file(&wg, dst2, "bbbbb\n")
	}
	wg.Wait()
}
