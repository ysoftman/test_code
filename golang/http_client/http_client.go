// author : ysoftman
// encoding : utf-8
// title : http client test

package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"os"
	"strings"

	"github.com/labstack/gommon/log"
)

func main() {
	// 방법1
	// 일반적인 http get 요청
	fmt.Println("using http.Get()")
	resp, err := http.Get("http://httpbin.org/ip")
	if err != nil {
		log.Error(err.Error())
		os.Exit(1)
	}
	defer resp.Body.Close()
	// 응답결과 출력
	// ioutil.ReadAll 로 resp.Body 읽고 나면 resp.Body 내용은 사라진다.(read 시 offset 이 EOF 로 이동되어서)
	bodybtyes, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatal("can't read resp.Body")
	}
	bodystring := string(bodybtyes)
	fmt.Println(bodystring)

	// 방법2
	// 헤더를 추가하거나 post 방식으로 요청할경우
	fmt.Println("using http.NewRequest()")
	requestbody := "ysoftman"
	req, err := http.NewRequest("GET", "http://httpbin.org/anything", strings.NewReader(requestbody))
	if err != nil {
		log.Fatal("can't create NewRequeset()")
	}
	// 헤더 추가
	req.Header.Add("test-header1", "test-requester_value1")
	req.Header.Add("test-header2", "test-requester_value2")
	req.Header.Add("test-header3", "test-requester_value3")
	// 요청 수행
	client := &http.Client{}
	resp, err = client.Do(req)
	if err != nil {
		log.Fatal("can't read resp.Body")
	}
	defer resp.Body.Close()

	// 응답결과 출력
	// ioutil.ReadAll 로 resp.Body 읽고 나면 resp.Body 내용은 사라진다.(read 시 offset 이 EOF 로 이동되어서)
	bodybtyes, err = ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatal("can't read resp.Body")
	}
	bodystring = string(bodybtyes)
	fmt.Println(bodystring)
}
