package hello

import (
	"fmt"
	"net/http"
)

func init() {
	http.HandleFunc("/", handler)
}
func handler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "ysoftman first appengine test<br>")
	fmt.Fprint(w, "hello world<br>")
}
