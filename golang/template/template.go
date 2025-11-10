// author : ysoftman
// encoding : utf-8
// title : template 사용 테스트

package main

import (
	"fmt"
	"html/template"
	"os"

	sprig "github.com/go-task/slim-sprig"
)

const htmlTemplate = `
<html>
<body>
html template 테스트입니다.

{{- /*
이건 주석~
이런 template 부분들이 기본적으로 하나의 공백라인으로 렌더링 된다.
{{-공백 은 이전까지 공백(탭,뉴라인) trim
공백-}}  은 이후의 공백(탭,뉴라인) trim
*/ -}}

{{if ne .Message ""}}
	{{ .Message }}
{{end}}

{{if .HasApple}}
	apple
{{end}}

{{ if not .HasApple }}
	(tab)banana
    (space*4)banana
{{ end }}
{{- if not .HasApple -}}
	(tab)banana
    (space*4)banana
{{- end }}

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

const sprigTemplate = `
--- use spring template ---
--- https://github.com/Masterminds/sprig ---
{{/* sprig 패키지를 사용하면 다음과 같은 pipeline function 을 사용할 수 있다. */}}
{{- .Message}}
blabla
{{.Message  | trim | upper | repeat 5}}
{{.Message  | trim | indent 4}}
`

type UserInfo struct {
	Value1 int

	// string 데이터 타입으로 선언하면
	// script 영역에서 quotation(") 가 붙여진다.
	// html 영역에서 html 태그가 제대로 표시 되지 않는다.
	//	value2 string
	//	value3 string

	// html 영역에 값 전달시 template.HTML
	// script 영역에 값 전달시 template.JS 데이터 타입을 사용하자
	Value2 template.JS
	Value3 template.HTML

	HasApple bool

	Message string
}

var userInfo UserInfo

func main() {
	tpl, err := template.New("test_template").Parse(htmlTemplate)
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
	userInfo.HasApple = false
	userInfo.Message = "     ysoftman"

	// html 문서 처리
	err = tpl.Execute(os.Stdout, userInfo)
	if err != nil {
		fmt.Println("execute template error ... " + err.Error())
		return
	}

	// sprig template
	sprigTpl, err := template.New("sprig_test_template").Funcs(sprig.FuncMap()).Parse(sprigTemplate)
	if err != nil {
		fmt.Println("parse sprig template error ... " + err.Error())
		return
	}
	err = sprigTpl.Execute(os.Stdout, userInfo)
	if err != nil {
		fmt.Println("execute sprig template error ... " + err.Error())
		return
	}
}
