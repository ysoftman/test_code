// author : ysoftman
// encoding : utf-8
// title : http 웹 서버 테스트
package main

import (
	"bytes"
	"context"
	"fmt"
	"html/template"
	"net/http"
	"net/url"
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
	// / 를 허용하지 않도록 한다. 아래 path 외는 404 발생을 위해서
	// http.HandleFunc("/", mainPage)
	// 404 not found 디폴트 핸들러
	// http.Handle("/", http.NotFoundHandler())
	// not found 로깅을 위해 별도 핸들러에서 처리
	http.HandleFunc("/", notfound)
	http.HandleFunc("/main", mainPage)
	http.HandleFunc("/test", testPage)
	// imgs 의 파이들에 접급 허용
	http.Handle("/imgs/", http.StripPrefix("/imgs", http.FileServer(http.Dir("./imgs"))))
	http.ListenAndServe(":55555", nil)

	// https 로 띄우기(https://localhost/main 로 테스트)
	// Go 1.6 부터 net/http  에서 http2 지원
	// crt, key 파일 생성
	// openssl req -newkey rsa:2048 -nodes -keyout server.key -x509 -days 365 -out server.crt
	// 기본 https + http2
	// curl -Iv -k 'https://localhost/main'
	// https + http1.1 로 요청시
	// curl -Iv -k 'https://localhost/main' --http1.1
	// http.ListenAndServeTLS(":443", "server.crt", "server.key", nil)

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

// notfound 처리 함수
func notfound(w http.ResponseWriter, r *http.Request) {
	notFoundMsg := "404 not found... :( path: " + r.RequestURI
	fmt.Println(notFoundMsg)
	w.WriteHeader(http.StatusNotFound)

	// WriteHeader 를 여러번 쓰면 불필요한(superflous) 구문이라고 다음과 에러가 나고 수행되지 않는다.
	// http: superfluous response.WriteHeader call from main.notfound
	// w.WriteHeader(http.StatusBadRequest)

	// Write는 이전에 WriteHeader를 호출하지 않았다면 암묵적으로 WriteHeader(http.StatusOK) 를 호출한다.
	w.Write([]byte(notFoundMsg))
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

	// 헤더 추가
	w.Header().Set("ysoftman1", "lemon")
	// w.Header().Set("ysoftman2", "메인페이지 입니다.")
	// js 에서 사용하기 위해서는 한글은 QueryEscape 해준다.
	// js decodeURIComponent() 로 디코딩해 사용한다.
	w.Header().Set("ysoftman2", url.QueryEscape("메인페이지 입니다."))

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
	// templateMain, err := template.ParseFiles("test.html", "testnested.html")
	templateMain, err := template.New("test.html").Funcs(myFuncMap).ParseFiles("test.html", "testnested.html")
	if err != nil {
		panic(err)
	}

	// 클라가 보낸 값 파악
	data := userData{}
	//data.userno, _ = strconv.Atoi(r.FormValue("user_no")) // 32bit int 인 경우
	data.UserNo, _ = strconv.ParseInt(r.FormValue("user_no"), 0, 64) // 64bit int 인 경우
	data.StrName = r.FormValue("user_name")

	fmt.Println("data:", data)

	// 템플릿 실행(html 응답)
	//templateMain.Execute(os.Stdout, nil)
	// data 를 템플릿으로 넘겨 동적 html 을 생성할 수 있도록 한다.
	//err = templateMain.Execute(w, data)

	// 전역 변수에 저장하여 보여주기, 응답 주기
	mapUserData[data.UserNo] = data
	err = templateMain.Execute(w, mapUserData)

	// 템플릿 내용이 적용된 html 을 string 형태로 출력해보자
	var tpl bytes.Buffer
	err = templateMain.Execute(&tpl, mapUserData)
	fmt.Println(tpl.String())

	if err != nil {
		fmt.Println(err.Error())
	}
	requestCnt++
	fmt.Println("request cnt = ", requestCnt)
}

var myFuncMap = template.FuncMap{
	"setInt": setInt,
}

func setInt(n ...int) []int {
	var sliceint []int
	for _, val := range n {
		fmt.Println("seInt:", n)
		sliceint = append(sliceint, val)
	}
	return sliceint
}
