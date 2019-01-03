// author : ysoftman
// encoding : utf-8
// desc : urlencoding test
package main

import (
	"fmt"
	"log"
	"net/url"
)

func main() {
	u, err := url.Parse("http://ysoftman.com/test?key1=1 2&key2=value2")
	if err != nil {
		log.Fatal(err)
	}
	// url 파싱후 각 요소 출력
	fmt.Println(u)
	fmt.Println(u.Scheme)
	fmt.Println(u.Host)
	fmt.Println(u.Path)
	fmt.Println(u.RawQuery)
	fmt.Println(u.Query())
	fmt.Println(u.Query()["key1"])
	fmt.Println(u.Query()["key2"])

	// 공백의 경우 %20 대신 + 가 된다.
	v := url.Values{}
	v.Set("key", "aaa bbb")
	fmt.Println(v)
	fmt.Println(v.Get("key"))
	fmt.Println(v.Encode())
}
