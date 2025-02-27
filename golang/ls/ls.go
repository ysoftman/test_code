// author : ysoftman
// encoding : utf-8
// title : 파일 리스트(ls)
package main

// import "log"
import (
	"fmt"
	"log"
	"os"
)

func main() {
	nArgs := len(os.Args)
	// 대상 경로가 없다면 현재 경로가 디폴트
	targetpath, _ := os.Getwd()
	//	log.Println("len(os.Args[])= ", nArgs)
	if nArgs >= 1 {
		targetpath, _ = os.Getwd()
	} else if nArgs >= 2 {
		targetpath = os.Args[1]
	}
	//	log.Println("exefile= ", os.Args[0])
	//	log.Println("targetpath= ", targetpath)

	// 대상 경로의 디렉토리 및 파일 리스트 파악
	entries, _ := os.ReadDir(targetpath)
	for _, entry := range entries {
		if entry.Type().IsRegular() {
			filePath := targetpath + "/" + entry.Name()
			fileInfo, err := os.Stat(filePath)
			if err != nil {
				log.Println(err)
				continue
			}
			fmt.Printf("Name(%v), Size(%v), IsDir(%v), Mode(%v), ModTime(%v)\n",
				fileInfo.Name(), fileInfo.Size(), fileInfo.IsDir(), fileInfo.Mode(), fileInfo.ModTime())
		}
	}
}
