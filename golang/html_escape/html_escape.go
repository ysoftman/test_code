// ysoftman
// html escape, unescape

package main

import (
	"html"
	"log"
)

func main() {
	a := "ysoftman's <> 111 & 222 @ 333 ok"
	log.Println(a)
	a = html.EscapeString(a)
	log.Println(a)
	a = html.UnescapeString(a)
	log.Println(a)
}
