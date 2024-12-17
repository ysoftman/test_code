// ysoftman
// jwt(json web token) test
// go get github.com/dgrijalva/jwt-go

// jwt 인코딩/디코딩
// https://jwt.io/

/* jwt 요청
curl -X POST 'http://localhost:55555/auth' \
-H 'Content-Type: application/json' \
-H 'authorization: eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJuYW1lIjoieXNvZnRtYW4iLCJhZ2UiOjMwfQ.DNIcy27sbrpiAwEiw6MoILzkdFNr9MQsZJoS5_Q5mUs'
*/

package main

import (
	"fmt"
	"log"
	"net/http"

	"github.com/dgrijalva/jwt-go"
)

const serverport = "55555"

type userInfo struct {
	Name string `json:"name"`
	Age  int    `json:"age"`
	// jwt.StandardClaims 가 포함되어 있어야 한다.
	jwt.StandardClaims
}

func main() {
	fmt.Println("start server...")

	// 토큰 생성해보기
	token := jwt.NewWithClaims(jwt.GetSigningMethod("HS256"), &userInfo{
		Name: "ysoftman",
		Age:  30,
	})
	tokenstring, err := token.SignedString([]byte("byounghoon"))
	if err != nil {
		log.Fatalln(err)
	}
	// jwt 토큰 구조
	// 헤더.payload(claim,내용).서명
	// eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJuYW1lIjoieXNvZnRtYW4iLCJhZ2UiOjMwfQ.DNIcy27sbrpiAwEiw6MoILzkdFNr9MQsZJoS5_Q5mUs
	fmt.Println("create tokenstring test: ", tokenstring)

	// 요청 주소에 따른 핸들러 등록
	http.HandleFunc("/auth", authPage)
	http.ListenAndServe(":"+serverport, nil)
}

// authPage 처리 함수
func authPage(w http.ResponseWriter, r *http.Request) {
	fmt.Println("RequestURI : ", r.RequestURI)

	// 요청 헤더로 부터 jwt 값 파악
	tokenString := r.Header.Get("authorization")
	fmt.Println("tokenString: ", tokenString)

	// 토큰 파싱
	token, err := jwt.Parse(tokenString, func(token *jwt.Token) (interface{}, error) {
		return []byte("byounghoon"), nil
	})
	if err != nil {
		fmt.Println("[error] ", err)
		return
	}
	// 토큰 파싱 결과
	fmt.Println("token.Header: ", token.Header)
	fmt.Println("token.Claims: ", token.Claims)
	fmt.Println("token.Valid: ", token.Valid)
}
