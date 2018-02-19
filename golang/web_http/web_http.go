// author : ysoftman
// encoding : utf-8
// title : http 웹 서버 테스트
package main

import (
	"context"
	"fmt"
	"html/template"
	"net/http"
	"strconv"
)

//import "os"

// net/http 패키지의 ServeHTTP 인터페이스
//type Handler interface {
//	ServeHTTP(w ResponseWriter, r *Request)
//}

// Handler 타임 선언
type myHTTP struct{}

var requestCnt int

type userData struct {
	UserNo  int64
	StrName string
}

var mapUserData map[int64]userData

func main() {
	fmt.Println("web http start...")

	// map 사용하기위새 미리 make 해놓음 := 를 사용하면 지역 변수로 취급
	mapUserData = make(map[int64]userData)
	fmt.Println("len(g_mapUserDatalen) = ", len(mapUserData))

	// 서버띄우기 방법1
	// 요청 주소에 따른 핸들러 등록
	http.HandleFunc("/", mainPage)
	http.HandleFunc("/test", testPage)
	// imgs 의 파이들에 접급 허용
	http.Handle("/imgs/", http.StripPrefix("/imgs", http.FileServer(http.Dir("./imgs"))))
	http.ListenAndServe(":55555", nil)

	// 서버띄우기 방법2
	// ServeHTTP(이미 정의됨) 함수를 mythttp 핸들로 사용
	// var web myHTTP
	// //http.ListenAndServe("127.0.0.1:55555", web)
	// http.ListenAndServe(":55555", web)
}

// ServeHTTP 인터페이스 구현
func (web myHTTP) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	fmt.Println("RequestURI : ", r.RequestURI)

	if r.RequestURI == "/" {

	} else if r.RequestURI == "/test" {

	} else {

	}
	requestCnt++
	fmt.Println("request cnt = ", requestCnt)
}

// mainpage 처리 함수
func mainPage(w http.ResponseWriter, r *http.Request) {
	fmt.Println("RequestURI : ", r.RequestURI)

	// main page 템플릿 생성
	templateMain, _ := template.ParseFiles("main.html")

	var responseData struct {
		NameList []string
	}
	responseData.NameList = append(responseData.NameList, "ysoftman", "bill", "yoon")
	// fmt.Println("responseData.NameList = ", responseData.NameList)

	type key string
	type value int
	var mykey key = "aaa"

	fmt.Println(`r.FormValue("ysoftman")`, r.FormValue("ysoftman"))
	fmt.Println(`r.Header.Get("Accept-Language")`, r.Header.Get("Accept-Language"))
	fmt.Println(`r.Header`, r.Header)
	ctx := context.WithValue(r.Context(), mykey, "aaa")
	fmt.Println(ctx)

	ctx = context.WithValue(context.Background(), mykey, "aaa")
	mykey = "bbb"
	ctx = context.WithValue(ctx, mykey, "bbb")
	mykey = "ccc"
	ctx = context.WithValue(ctx, mykey, 3333)
	fmt.Println(ctx)

	mykey = "aaa"
	fmt.Println(`ctx.Value("aaa")`, ctx.Value(mykey))
	mykey = "bbb"
	fmt.Println(`ctx.Value("bbb")`, ctx.Value(mykey))
	mykey = "ccc"
	fmt.Println(`ctx.Value("ccc")`, ctx.Value(mykey))

	// 템플릿 실행(html 응답)
	//templateMain.Execute(os.Stdout, nil)
	templateMain.Execute(w, responseData)

	requestCnt++
	fmt.Println("request cnt = ", requestCnt)
}

// testpage 처리 함수
func testPage(w http.ResponseWriter, r *http.Request) {
	fmt.Println("RequestURI : ", r.RequestURI)

	// test page 템플릿 생성
	templateMain, _ := template.ParseFiles("test.html")

	// 클라가 보낸 값 파악
	data := userData{}
	//data.userno, _ = strconv.Atoi(r.FormValue("user_no")) // 32bit int 인 경우
	data.UserNo, _ = strconv.ParseInt(r.FormValue("user_no"), 0, 64) // 64bit int 인 경우
	data.StrName = r.FormValue("user_name")

	fmt.Println("data:", data)

	// 템플릿 실행(html 응답)
	//templateMain.Execute(os.Stdout, nil)
	// data 를 템플릿으로 넘겨 동적 html 을 생성할 수 있도록 한다.
	//err := templateMain.Execute(w, data)

	// 전역 리에 저장하여 보여주기
	mapUserData[data.UserNo] = data
	err := templateMain.Execute(w, mapUserData)

	if err != nil {
		fmt.Println(err.Error())
	}
	requestCnt++
	fmt.Println("request cnt = ", requestCnt)
}
