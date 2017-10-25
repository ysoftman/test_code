// ysoftman
// logrus test
// go get -u "github.com/Sirupsen/logrus"
// go get -u "github.com/natefinch/lumberjack"
package main

import (
	"time"

	log "github.com/Sirupsen/logrus"
	"github.com/natefinch/lumberjack"
)

func main() {

	// 로그 출력 대상 선택
	// log.SetOutput(os.Stderr)

	// lumberjack 으로 rotate log
	lj := &lumberjack.Logger{
		// 기본 로그 파일 명
		Filename: "ysoftman.log",
		// 로그 파일당 최대 허용 크기(megabytes)
		MaxSize: 999999,
		// 로컬 시간으로 파일명(타임스탬프)사용, 기본 UTC
		LocalTime: true,
	}
	log.SetOutput(lj)

	// 디버그 레벨 이상의 로그는 출력 하도록 설정
	log.SetLevel(log.DebugLevel)

	printlog()

	// json 형식으로 로그 출력
	log.SetFormatter(&log.JSONFormatter{})

	go func() {
		for {
			// 로그 파일 로테이션
			// 현재 사용 중인 로그는 ysoftman.log
			// 지난 로그는 ysoftman-타임스탬프.log 로 변경됨
			<-time.After(time.Second * 2)
			lj.Rotate()
		}
	}()

	time.Sleep(time.Second * 2)
	printlog()
	time.Sleep(time.Second * 2)
	printlog()

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
	log.WithFields(log.Fields{"id": "ysoftman", "age": "30"}).Info("okay")

	// 필드형식의 포맷을 만들어 재사용 사용할 수 있다.
	mylogformat := log.WithFields(log.Fields{"id": "ysoftman", "age": "30"})
	mylogformat.Error("oh no!")
}
