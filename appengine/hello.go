package main

// main()을 사용하지 않을때
// package hello

import (
	"fmt"
	"log"
	"net/http"
	"text/template"

	"google.golang.org/appengine" // Required external App Engine library
)

func handlerHello(w http.ResponseWriter, r *http.Request) {
	if r.URL.Path != "/" {
		http.Redirect(w, r, "/", http.StatusFound)
		return
	}
	var data struct {
		Title string
	}
	data.Title = "ysoftman first appengine test"
	templateMain, err := template.ParseFiles("hello.html")
	if err != nil {
		log.Println(err)
		return
	}
	templateMain.Execute(w, data)
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
	// appengine 에서는 기본 http client 를 할 수 없다.
	// google.golang.org/appengine/urlfetch 를 사용해야 하나.
	// http.DefaultTransport and http.DefaultClient are not available in App Engine. See https://cloud.google.com/appengine/docs/go/urlfetch/
	// resp, err := http.Post(url, "text/html", data)
	// resp, err := client.Post(url, "text/html", data)
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
