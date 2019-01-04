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

	v := url.Values{}
	v.Set("key1", "1111")
	v.Set("key2", "aaa bbb")
	v.Add("key2", "ccc")
	fmt.Println(v)
	// 같은 키가 여러개인 경우 첫번째 값만 리턴한다.
	fmt.Println(v.Get("key2"))
	// Encode() 내에서 sort 한다.
	// 값에 공백이  있는 경우 + 로 표시된다.
	fmt.Println(v.Encode())
}
