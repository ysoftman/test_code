// author : ysoftman
// encoding : utf-8
// title : http client test

package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"net/url"
	"os"
)

func main() {
	get()
	post()
}

func get() {
	// 일반적인 http get 요청
	fmt.Println("using http.Get()")
	resp, err := http.Get("http://httpbin.org/ip")
	if err != nil {
		log.Println(err.Error())
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
}

func post() {
	// 참고로 http.post 는 default client 1개로 여러 고루틴에서 쓰기엔 느리다.
	// 헤더를 추가하거나 post 방식으로 요청할경우
	fmt.Println("using http.NewRequest()")
	// data 추가
	// form 형식
	// "data": "ysoftman1=lemon&ysoftman2=orange&ysoftman3=banana",
	// requestbody := url.Values{}
	// requestbody.Set("ysoftman1", "lemon")
	// requestbody.Set("ysoftman2", "orange")
	// requestbody.Set("ysoftman3", "banana")
	// req, err := http.NewRequest("GET", "http://httpbin.org/anything", strings.NewReader(requestbody.Encode()))
	// struct -> json 형식
	reqBody := struct {
		Ysoftman1 string `json:"ysoftman1"`
		Ysoftman2 string `json:"ysoftman2"`
	}{
		Ysoftman1: "lemon",
		Ysoftman2: "orange",
	}
	requestbody := new(bytes.Buffer)
	err := json.NewEncoder(requestbody).Encode(reqBody)
	if err != nil {
		log.Fatal(err)
		return
	}
	req, err := http.NewRequest(http.MethodPost, "http://httpbin.org/post", requestbody)
	if err != nil {
		log.Fatal("can't create NewRequest()")
	}
	// Content-Type 에 json 을 명시하지 않으면 서버에서 data 값을 사용하지 못할 수 있다.
	req.Header.Set("Content-Type", "application/json")
	fmt.Println("req:", req)

	// 참고로 req 생성후 req.Form 을 설정하면 http.Client 에 의해 무시되기 때문에 body 추가해야 한다.
	req.Form = url.Values{}
	req.Form.Set("ysoftman4", "apple")
	// 헤더 추가
	req.Header.Add("test-header1", "test-requester_value1")
	req.Header.Add("test-header2", "test-requester_value2")
	req.Header.Add("test-header3", "test-requester_value3")

	// 요청 수행
	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		log.Fatal("can't read resp.Body")
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
}
