package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"path/filepath"
)

func main() {
	// TempFile() 첫번째 인자가 "" 이면 os.TempDir() 로 $TMPDIR 위치를 사용한다.
	tmpf, err := ioutil.TempFile("", "patternString")
	if err != nil {
		log.Fatal("error!!! - ", err)
	}
	fmt.Println("tempfilename:", tmpf.Name())
	baseName := filepath.Base(tmpf.Name())
	fmt.Println("baseName:", baseName)
	dirName := filepath.Dir(tmpf.Name())
	fmt.Println("dirName:", dirName)
	// time.Sleep(10 * time.Second)
}
