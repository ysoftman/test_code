// ysoftman
// html tokenizer test

package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"os"
	"path/filepath"

	"golang.org/x/net/html"

	"github.com/labstack/gommon/log"
)

func main() {
	if len(os.Args) != 2 {
		_, splitfile := filepath.Split(os.Args[0])
		fmt.Printf("(ex) %s %s\n", splitfile, "http://www.json.org")
		return
	}
	resp, err := http.Get("http://www.json.org")
	if err != nil {
		log.Error(err.Error())
		os.Exit(1)
	}
	fmt.Println("resp -------------------------")
	fmt.Println(resp)
	fmt.Println("resp.body to string -------------------------")
	// resp.Body 는 io.ReadCloser 타입으로 한번 읽으면 close 되어 재사용할 수 없다.
	bodybtyes, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatal("can't read resp.Body")
	}
	bodystring := string(bodybtyes)
	fmt.Println(bodystring)

	// 위에서 ReadAll 로 resp.Body 를 읽어 close 되어 다시 사용할수 없어 재요청
	resp, err = http.Get("http://www.json.org")
	if err != nil {
		log.Error(err.Error())
		os.Exit(1)
	}
	fmt.Println("parse resp.body -------------------------")
	htmltok, _ := html.Parse(resp.Body)
	traverseHTML(htmltok)
}

func traverseHTML(node *html.Node) {
	prefix := ""
	if node.Type == html.ElementNode {
		prefix = "ELEMENT"
	} else if node.Type == html.CommentNode {
		prefix = "COMMENT"
	} else if node.Type == html.DoctypeNode {
		prefix = "DOC"
	} else if node.Type == html.ErrorNode {
		prefix = "ERROR"
	} else if node.Type == html.TextNode {
		prefix = "TEXT"
	}
	fmt.Println("[" + prefix + "]" + node.Data)
	for child := node.FirstChild; child != nil; child = child.NextSibling {
		traverseHTML(child)
	}
}
