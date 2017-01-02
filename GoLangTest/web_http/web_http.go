// author : ysoftman
// encoding : utf-8
// title : http 웹 서버 테스트
package main

import "fmt"
import "net/http"
import "html/template"
import "strconv"

//import "os"

// net/http 패키지의 ServeHTTP 인터페이스
//type Handler interface {
//	ServeHTTP(w ResponseWriter, r *Request)
//}

// Handler 타임 선언
type myHttp struct{}

var g_Request int = 0

type UserData struct {
	UserNo  int64
	StrName string
}

var g_mapUserData map[int64]UserData

func main() {
	fmt.Println("web http start...")

	// map 사용하기위새 미리 make 해놓음 := 를 사용하면 지역 변수로 취급
	g_mapUserData = make(map[int64]UserData)
	fmt.Println("len(g_mapUserDatalen) = ", len(g_mapUserData))

	// 서버띄우기 방법1
	// 요청 주소에 따른 핸들러 등록
	//http.HandleFunc("/", mainPage)
	//http.HandleFunc("/test", testPage)
	//http.ListenAndServe(":55555", nil)

	// 서버띄우기 방법2
	// ServeHTTP(이미 정의됨) 함수를 mythttp 핸들로 사용
	var web myHttp
	//http.ListenAndServe("127.0.0.1:55555", web)
	http.ListenAndServe(":55555", web)

}

// ServeHTTP 인터페이스 구현
func (web myHttp) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Listen(", g_Request, ")")
	fmt.Println("RequestURI : ", r.RequestURI)

	if r.RequestURI == "/" {
		fmt.Println("this is main page(", g_Request, ")")

		// main page 템플릿 생성
		templateMain, _ := template.ParseFiles("main.html")

		// 템플릿 실행(html 응답)
		//templateMain.Execute(os.Stdout, nil)
		templateMain.Execute(w, nil)

	} else if r.RequestURI == "/test" {
		fmt.Println("this is test page(", g_Request, ")")

		// test page 템플릿 생성
		templateMain, _ := template.ParseFiles("test.html")

		// 클라가 보낸 값 파악
		data := UserData{}
		//data.userno, _ = strconv.Atoi(r.FormValue("user_no")) // 32bit int 인 경우
		data.UserNo, _ = strconv.ParseInt(r.FormValue("user_no"), 0, 64) // 64bit int 인 경우
		data.StrName = r.FormValue("user_name")

		fmt.Println("data:", data)

		// 템플릿 실행(html 응답)
		//templateMain.Execute(os.Stdout, nil)
		// data 를 템플릿으로 넘겨 동적 html 을 생성할 수 있도록 한다.
		//err := templateMain.Execute(w, data)

		// 전역 리에 저장하여 보여주기
		g_mapUserData[data.UserNo] = data
		err := templateMain.Execute(w, g_mapUserData)

		if err != nil {
			fmt.Println(err.Error())
		}

	} else {
		fmt.Println("none(", g_Request, ")")
	}
	g_Request++
}

// mainpage 처리 함수
func mainPage(w http.ResponseWriter, r *http.Request) {
	fmt.Println("RequestURI : ", r.RequestURI)
	fmt.Println("this is main page(", g_Request, ")")
	g_Request++
}

// testpage 처리 함수
func testPage(w http.ResponseWriter, r *http.Request) {
	fmt.Println("RequestURI : ", r.RequestURI)
	fmt.Println("this is test page(", g_Request, ")")
	g_Request++
}
