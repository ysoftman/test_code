package hello

import (
	"fmt"
	"net/http"
)

func handlerHello(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "ysoftman first appengine test<br>")
	fmt.Fprint(w, "appengine /<br>")
}

func handlerTest(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "ysoftman first appengine test<br>")
	fmt.Fprint(w, "appengine /test<br>")
}

func init() {
	http.HandleFunc("/", handlerHello)
	http.HandleFunc("/test", handlerTest)
}
