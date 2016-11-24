// ysoftman
// logrus test
// go get -u "github.com/Sirupsen/logrus"
package main

import (
	"os"

	log "github.com/Sirupsen/logrus"
)

func main() {

	// 로그 출력 대상 선택
	log.SetOutput(os.Stderr)
	// 디버그 레빌 이상의 로그는 출력 하도록
	log.SetLevel(log.DebugLevel)

	printlog()

	// json 형식으로 로그 출력
	log.SetFormatter(&log.JSONFormatter{})

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
