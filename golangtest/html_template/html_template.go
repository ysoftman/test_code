// author : ysoftman
// encoding : utf-8
// title : html template 사용 테스트
// html 영역에 값 전달시 template.HMTL
// script 영역에 값 전달시 template.JS 데이터 타입을 사용하자
package main

import "fmt"
import "os"
import "html/template"

const htmlString = `
<html>
<body>
html template 테스트입니다.

<script>
var val1 = {{.Value1}}
var val2 = {{.Value2}}
var val3 = {{.Value3}}
</script>

val1 = {{.Value1}}
val2 = {{.Value2}}
val3 = {{.Value3}}

</body>
</html>
`

type UserInfo struct {
	Value1 int

	// string 데이터 타입으로 선언하면
	// script 영역에서 quotation(") 가 붙여진다.
	// html 영역에서 html 태그가 제대로 표시 되지 않는다.
	//	value2 string
	//	value3 string

	Value2 template.JS
	Value3 template.HTML
}

var userInfo UserInfo

func main() {

	tpl, err := template.New("test_template").Parse(htmlString)
	if err != nil {
		fmt.Println("parse template error ... " + err.Error())
		return
	}

	// userinfo 설정
	userInfo.Value1 = 123456789
	userInfo.Value2 = "ysoftman"
	userInfo.Value3 = `
	have a nice day1<br>
	have a nice day2<br>
	have a nice day3<br>
	have a nice day4<br>
	`
	//html 문서 처리
	err = tpl.Execute(os.Stdout, userInfo)
	if err != nil {
		fmt.Println("execute template error ... " + err.Error())
		return
	}
}
