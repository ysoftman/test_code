package main

// main()을 사용하지 않을때
// package hello

import (
	"fmt"
	"net/http"

	"google.golang.org/appengine" // Required external App Engine library
)

func handlerHello(w http.ResponseWriter, r *http.Request) {
	if r.URL.Path != "/" {
		http.Redirect(w, r, "/", http.StatusFound)
		return
	}
	resp := `ysoftman first appengine test<br>
	appengine /<br>
	<br>
	<H2>filebase 파일</H2>
	xelloss image<br>
	<img src="https://firebasestorage.googleapis.com/v0/b/ysoftman-test.appspot.com/o/xelloss.jpg?alt=media&token=498bde0a-1802-40fb-b51a-c3c0c814eec6">
	<br>
	박카스<br>
	<img src="https://firebasestorage.googleapis.com/v0/b/ysoftman-test.appspot.com/o/%E1%84%87%E1%85%A1%E1%86%A8%E1%84%8F%E1%85%A1%E1%84%89%E1%85%B3.jpg?alt=media&token=79f4c9ce-5269-478f-a402-12e41a7e9d0e">
	<br>
	filebase gs(google) url로 파일 다운로드<br>
	gsutil cp -v gs://ysoftman-test.appspot.com/xelloss.jpg . <br>
	gsutil cp -v gs://ysoftman-test.appspot.com/박카스.jpg . <br>
	`
	fmt.Fprint(w, resp)
}

func handlerTest(w http.ResponseWriter, r *http.Request) {
	resp := `
	ysoftman first appengine test<br>
	appengine /test<br>
	`
	fmt.Fprint(w, resp)
	// 슬랙 채널에 메시지 보내기
	// 슬랙 app -> 슬랫 bot api 사용
	// slackURL := ""
	// slackToken := ""
	// slackChannel := "dustinfo"
	// slackMsg := "슬랙봇테스트입니다"
	// data := strings.NewReader(slackMsg)
	// url := "https://" + url + "?token=" + slackToken + "&channel=%23" + slackChannel
	// resp, err := http.Post(url, "text/html", data)
	// if err != nil {
	// 	log.Println(err)
	// 	return
	// }
	// fmt.Fprintln(w, "sent a message to slack channel(dustinfo) : "+resp.Status)
}

func init() {
	http.HandleFunc("/test", handlerTest)
}

func main() {
	http.HandleFunc("/", handlerHello)
	appengine.Main() // Starts the server to receive requests
}
