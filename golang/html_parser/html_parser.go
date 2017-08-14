// ysoftman
// html tokenizer test

package main

import (
	"fmt"
	"net/http"
	"os"
	"path/filepath"

	"github.com/labstack/gommon/log"
	"golang.org/x/net/html"
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
	fmt.Println("parse body -------------------------")
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
