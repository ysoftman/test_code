package main

import (
	//_ "embed"
	"embed"
	"fmt"
	"log"
	"net/http"
)

// embed 는 go1.16 에 포함된 기능으로 go:embed 주석으로 달면 파일을 바이너리에 포함시킨다.
// 바이너리 사이즈와 메모리 사용량이 늘어난다.
// embed 파일을 사용하기 때문에 ./files 에 파일이 추가돼도 반영되지 않는다.

// embed.xxx 를 사용하지 않으면 import _ embed 로 사용
// //go:.... 로 주석시작에 공백이 없어야 한다.
//
//go:embed files/file1.txt
var file1 string

// files/file3.zzz embed 되지 않는다.
//
//go:embed files/*.txt
var files embed.FS

func main() {
	fmt.Println("file1:", file1)
	portStr := "8080"
	mux := http.NewServeMux()
	//mux.Handle("/", http.FileServer(http.Dir(".")))
	// embed 된 files/*.txt 만 있는것으로 된다.
	mux.Handle("/", http.FileServer(http.FS(files)))
	fmt.Printf("running server(:%v) for embed test...", portStr)
	err := http.ListenAndServe(":"+portStr, mux)
	if err != nil {
		log.Fatal(err)
	}
}
