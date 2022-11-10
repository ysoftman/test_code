// author : ysoftman
// encoding : utf-8
// title : 일정 기간이 경과한 로그 파일 삭제 프로그램
package main

import "log"
import "os"
import "fmt"
import "io/ioutil"
import "time"
import "strconv"

func main() {
	nArgs := len(os.Args)

	// 로그 디렉토리 위치를 인자로 받기
	if nArgs != 3 {
		fmt.Println("logEraser (https://github.com/ysoftman/logEraser.git)")
		fmt.Println("ex) logEraser ./log/path/ 7      # ./log/path/ 에서 7일 이전 로그 삭제")
		os.Exit(0)
	}
	targetpath := os.Args[1]
	diffsec, err := strconv.Atoi(os.Args[2])
	if err != nil {
		log.Fatalln("day argument error.")
	}
	log.Printf("day = %v\n", diffsec)
	diffsec = diffsec * 60 * 60 * 24
	log.Printf("path = %v\n", targetpath)

	curtime := time.Now()
	log.Printf("curtime.Unix() = %v", curtime.Unix())

	// 대상 경로의 디렉토리 및 파일 리스트 파악
	fileinfo, _ := ioutil.ReadDir(targetpath)
	for _, value := range fileinfo {
		log.Printf("Name(%v), Size(%v), IsDir(%v), Mode(%v), ModTime(%v)\n", value.Name(), value.Size(), value.IsDir(), value.Mode(), value.ModTime())

		//		// 폴더이름 시간을 계산
		//		dirtime := GetDirNameToDate(value.Name())
		//		if dirtime == 0 {
		//			continue;
		//		}

		// 기간 경과한 대상 경로의 파일(디렉토리) 삭제
		delpath := ""
		//		if dirtime.Unix() < curtime.Unix() && curtime.Unix()-dirtime.Unix() > int64(diffsec) {
		if value.ModTime().Unix() < curtime.Unix() && curtime.Unix()-value.ModTime().Unix() > int64(diffsec) {
			delpath = targetpath + "/" + value.Name()
			log.Println("delete directory... ", delpath)
			err := os.RemoveAll(delpath)
			if err != nil {
				log.Println(err.Error())
			}
		}

	}

}

func GetDirNameToDate(dirname string) int64 {

	// 폴더 이름이 날짜인 경우 시간 계산
	strYear := dirname[0:4]
	strMonth := dirname[4:6]
	strDay := dirname[6:]
	nYear, err := strconv.Atoi(strYear)
	if err != nil {
		log.Printf("Can't read dir year, skip dir(%v)", dirname)
		return 0
	}
	nMonth, err := strconv.Atoi(strMonth)
	if err != nil {
		log.Printf("Can't read dir month, skip dir(%v)", dirname)
		return 0
	}
	nDay, err := strconv.Atoi(strDay)
	if err != nil {
		log.Printf("Can't read dir day, skip dir(%v)", dirname)
		return 0
	}
	log.Printf("nYear(%v) nMonth(%v) nDay(%v)\n", nYear, nMonth, nDay)
	dirtime := time.Date(nYear, time.Month(nMonth), nDay, 0, 0, 0, 0, time.Local)
	log.Println(dirtime)
	log.Println(dirtime.Unix())

	return dirtime.Unix()
}
