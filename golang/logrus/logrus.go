// ysoftman
// logrus test
// go get -u "github.com/Sirupsen/logrus"
// go get -u "github.com/natefinch/lumberjack"
package main

import (
	"errors"
	"fmt"
	"sync"
	"time"

	"github.com/natefinch/lumberjack"
	log "github.com/sirupsen/logrus"
)

func main() {

	// 로그 출력 대상 선택
	// log.SetOutput(os.Stderr)

	// lumberjack 으로 rotate log
	lj := &lumberjack.Logger{
		// 기본 로그 파일 명
		Filename: "ysoftman.log",
		// 로그 파일당 최대 허용 크기(megabytes) - rotate 조건
		// MaxSize is the maximum size in megabytes of the log file before it gets
		// rotated. It defaults to 100 megabytes.
		// MaxSize 보다 커야만 rotate 된다.
		// MaxSize: 999999,
		MaxSize: 1,

		// old 로그 유지 조건 - MaxAge or MaxBackups
		// old 로그 유지 기간(days)
		// MaxAge is the maximum number of days to retain old log files based on the
		// timestamp encoded in their filename.  Note that a day is defined as 24
		// hours and may not exactly correspond to calendar days due to daylight
		// savings, leap seconds, etc. The default is not to remove old log files
		// based on age.
		MaxAge: 1,

		// old 로그 유지 개수
		// MaxBackups is the maximum number of old log files to retain.  The default
		// is to retain all old log files (though MaxAge may still cause them to get
		// deleted.)
		MaxBackups: 5,

		// 로컬 시간으로 파일명(타임스탬프)사용, 기본 UTC
		// LocalTime determines if the time used for formatting the timestamps in
		// backup files is the computer's local time.  The default is to use UTC
		// time.
		LocalTime: true,

		// 압축여부
		// Compress determines if the rotated log files should be compressed
		// using gzip. The default is not to perform compression.
		Compress: false,
	}
	log.SetOutput(lj)

	// 디버그 레벨 이상의 로그는 출력 하도록 설정
	log.SetLevel(log.DebugLevel)

	fmt.Printf("lumberjack rotate options\n%#v\n", lj)
	fmt.Println("Press Ctrl + c to stop to rotate log...")
	// json 형식으로 로그 출력
	log.SetFormatter(&log.JSONFormatter{PrettyPrint: true})
	printlog()
	var wg sync.WaitGroup
	wg.Add(1)
	go func() {

		// 강제로 로그 로테이션
		// for i := 0; i < 10; i++ {
		// 	// 로그 파일 로테이션
		// 	// 현재 사용 중인 로그는 ysoftman.log
		// 	// 지난 로그는 ysoftman-타임스탬프.log 로 변경됨
		// 	<-time.After(time.Second * 2)
		// 	lj.Rotate()
		// 	printlog()
		// }

		// 로그 파일을 1MB write 해서 로테이션하기
		for true {
			printlog()
			time.Sleep(10 * time.Microsecond)
		}
		defer wg.Done()

	}()
	wg.Wait()

}

func printlog() {
	// info 레벨 로그 출력
	log.Debug("debug level log")
	log.Info("info level log")
	log.Warn("warn level log")
	log.Error("error level log")

	// fatal, panic 의 경우 프로그램 종료된다.
	// log.Fatal("info level log")
	// log.Panic("panic level log")

	// 필드가 추가된 로그 출력
	log.WithFields(log.Fields{"id": "ysoftman", "age": "30"}).Debug("okay")

	// 필드형식의 포맷을 만들어 재사용 사용할 수 있다.
	mylogformat := log.WithFields(log.Fields{"id": "ysoftman", "age": "30"})
	mylogformat.Info("mylog.info")
	mylogformat.Warn("mylog.warn")
	mylogformat.Error("mylog.error")

	// "error" 를 키로 하는 필드를 추가해서 출력한다.
	err := errors.New("my error")
	mylogformat2 := log.WithError(err)
	mylogformat2.Debug(err.Error())
	mylogformat2.Info(err.Error())
	mylogformat2.Warn(err.Error())
	mylogformat2.Error(err.Error())
}
