// author : ysoftman
// encoding : utf-8
// title : http client test

package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"os"

	"github.com/labstack/gommon/log"
)

const testURL = "http://httpbin.org/ip"

func main() {
	// 방법1
	// 일반적인 http get 요청
	fmt.Println("using http.Get()")
	resp, err := http.Get(testURL)
	if err != nil {
		log.Error(err.Error())
		os.Exit(1)
	}
	defer resp.Body.Close()
	// 응답결과 출력
	// ioutil.ReadAll 로 resp.Body 읽고 나면 resp.Body 내용은 사라진다.
	bodybtyes, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatal("can't read resp.Body")
	}
	bodystring := string(bodybtyes)
	fmt.Println(bodystring)

	// 방법2
	// 헤더를 추가하거나 post 방식으로 요청할경우
	fmt.Println("using http.NewRequest()")
	req, err := http.NewRequest("GET", testURL, nil)
	if err != nil {
		log.Fatal("can't create NewRequeset()")
	}
	// 헤더 추가
	req.Header.Add("test-header", "test-requester")
	// 요청 수행
	client := &http.Client{}
	resp, err = client.Do(req)
	if err != nil {
		log.Fatal("can't read resp.Body")
	}
	defer resp.Body.Close()

	// 응답결과 출력
	// ioutil.ReadAll 로 resp.Body 읽고 나면 resp.Body 내용은 사라진다.
	bodybtyes, err = ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatal("can't read resp.Body")
	}
	bodystring = string(bodybtyes)
	fmt.Println(bodystring)
}
