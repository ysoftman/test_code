// ysoftman
// toml 테스트
package main

import (
	"fmt"
	"os"
	"time"
)

// go get github.com/BurntSushi/toml
import "github.com/BurntSushi/toml"

// Config : toml 을 저장할 자료 구조
type Config struct {
	Title string
	Zone1 ZoneInfo1 `toml:"zone1"`
	Zone2 ZoneInfo2 `toml:"zone2"`
}

// ZoneInfo1 자료구조
type ZoneInfo1 struct {
	Name string
	Sex  string
	Age  int
}

// ZoneInfo2 자료구조
type ZoneInfo2 struct {
	StringArray []string
	NumberArray []int
	Pi          float64
	Date        time.Time
}

func main() {
	fmt.Println("toml parser test...")

	var conf Config
	// 파일로 부터 파싱해서 conf 로 저장하기
	_, err := toml.DecodeFile("myconfig.toml", &conf)
	if err != nil {
		fmt.Printf("can't parse...\n")
		os.Exit(1)
	}
	fmt.Printf("Title:%s\n", conf.Title)
	fmt.Printf("Zone1.Name:%s\n", conf.Zone1.Name)
	fmt.Printf("Zone1.Sex:%s\n", conf.Zone1.Sex)
	fmt.Printf("Zone1.Age:%d\n", conf.Zone1.Age)
	fmt.Println("Zone2.StringArray:", conf.Zone2.StringArray)
	fmt.Println("Zone2.NumberArray:", conf.Zone2.NumberArray)
	fmt.Printf("Zone2.Pi:%f\n", conf.Zone2.Pi)
	fmt.Println("Zone2.Date:", conf.Zone2.Date)
}
