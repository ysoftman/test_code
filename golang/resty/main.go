package main

import (
	"encoding/json"
	"fmt"
	"os"

	"github.com/go-resty/resty/v2"
	"github.com/mitchellh/mapstructure"
)

func main() {
	client := resty.New()
	resp, err := client.R().SetHeader("Accept", "application/json").SetQueryParams(map[string]string{
		"param1": "1",
		"param2": "lemon",
	}).SetQueryParam("param3", "apple").SetAuthToken("aaaa").Get("https://httpbin.org/get")
	if err != nil {
		fmt.Println(err.Error())
		os.Exit(1)
	}
	printResponse(*resp)

	type testBody struct {
		Field1 string `json:"field1"`
		Field2 int    `json:"field2"`
	}
	reqBody := testBody{
		"orange",
		120,
	}
	resp, err = client.R().SetHeader("Accept", "application/json").SetQueryParams(map[string]string{
		"param1": "1",
		"param2": "lemon",
	}).SetBody(&reqBody).SetAuthToken("aaaa").Post("https://httpbin.org/post")
	if err != nil {
		fmt.Println(err.Error())
		os.Exit(1)
	}
	printResponse(*resp)

	type RespBody struct {
		Args struct {
			Param1 string `json:"param1"`
			Param2 string `json:"param2"`
		} `json:"args"`
		Data    string   `json:"data"`
		Files   struct{} `json:"files"`
		Form    struct{} `json:"form"`
		Headers struct {
			Accept         string `json:"Accept"`
			AcceptEncoding string `json:"Accept-Encoding"`
			Authorization  string `json:"Authorization"`
			ContentLength  string `json:"Content-Length"`
			ContentType    string `json:"Content-Type"`
			Host           string `json:"Host"`
			UserAgent      string `json:"User-Agent"`
			XAmznTraceID   string `json:"X-Amzn-Trace-Id"`
		} `json:"headers"`
		JSON struct {
			Field1 string `json:"field1"`
			Field2 int    `json:"field2"`
		} `json:"json"`
		Origin string `json:"origin"`
		URL    string `json:"url"`
	}
	rb := RespBody{}
	if err := json.Unmarshal(resp.Body(), &rb); err != nil {
		fmt.Println("error:", err.Error())
		os.Exit(1)
	}
	tb := testBody{}
	if err := mapstructure.Decode(rb.JSON, &tb); err != nil {
		fmt.Println("error:", err.Error())
		os.Exit(1)
	}
	fmt.Printf("resp body using mapstructure: %#v\n", tb)
}

func printResponse(resp resty.Response) {
	fmt.Println("time:", resp.Time())
	fmt.Println("receivedAt:", resp.ReceivedAt())
	fmt.Println("status:", resp.Status())
	fmt.Println("headers:", resp.Header())
	fmt.Println("cookies:", resp.Cookies())
	fmt.Println("resp.Body:", string(resp.Body()))
	fmt.Println("resp.RawResponse.ContentLength:", resp.RawResponse.ContentLength)
	fmt.Println("len(resp.Body():", len(resp.Body()))
	// buffer := make([]byte, resp.RawResponse.ContentLength)
	// if n, err := resp.RawBody().Read(buffer); err != nil {
	// 	fmt.Println("error:", err.Error())
	// } else {
	// 	fmt.Printf("read length: %v", n)
	// }
	// fmt.Println("resp.RawBody():", string(buffer))

	// buffer2, _ := ioutil.ReadAll(resp.RawBody())
	// fmt.Println("resp.RawBody():", buffer2)
}
