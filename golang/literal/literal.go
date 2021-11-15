// ysoftman
// literal test
package main

import "fmt"

func main() {
	var1 := `literal test 
	lemon	apple
orange 
chocolate

`
	fmt.Println("var1", var1)

	var2 := `|
		if $aaa = $bbb {
			print "ok"
\n` + " print backquote `" + `
		}
		`
	fmt.Println("var2", var2)

}
