// ysoftman
// minify test
// go get -u "github.com/tdewolff/minify"

package main

import (
	"fmt"

	"github.com/tdewolff/minify"
	"github.com/tdewolff/minify/css"
	"github.com/tdewolff/minify/html"
	"github.com/tdewolff/minify/js"
)

func main() {
	originaldata := `
	<html>
	
	<body>
	
	  <script>

		alert( 'Hello, world!' );

	  </script>

	</body>
	
	</html>
	`

	fmt.Println("[originaldata]")
	fmt.Println(originaldata)

	mini := minify.New()
	// css, html, javascript 각각에 대한 minify 함수 설정
	mini.AddFunc("text/css", css.Minify)
	mini.AddFunc("text/html", html.Minify)
	mini.AddFunc("text/javascript", js.Minify)
	minified, err := mini.String("text/javascript", originaldata)
	if err != nil {
		panic(err)
	}
	defer func() {
		recover()
	}()

	fmt.Println("[minified]")
	fmt.Println(minified)
}
