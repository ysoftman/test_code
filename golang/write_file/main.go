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

var lock *sync.Mutex

func write_file(wg *sync.WaitGroup, dst io.Writer, src string) {
	lock.Lock()
	for i := 0; i < 5; i++ {
		fmt.Print(src)
		src := strings.NewReader(src)
		if _, err := io.Copy(dst, src); err != nil {
			log.Fatal(err)
		}
		time.Sleep(1 * time.Second)
	}
	wg.Done()
	lock.Unlock()
}

func main() {
	lock = &sync.Mutex{}

	dst1, err := os.Create("out.tmp")
	if err != nil {
		log.Fatal(err)
	}
	defer dst1.Close()

	// O_EXCL 파일이 존재하지 않때만 열 수 있도록 한다.
	// dst2, err := os.OpenFile("out.tmp", os.O_RDWR|os.O_CREATE|os.O_EXCL, 0666)
	dst2, err := os.Create("out.tmp")
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
