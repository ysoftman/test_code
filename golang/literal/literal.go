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

	var num int
	num = 1000000
	fmt.Println("num", num)
	// For readability, an underscore character _ may appear after a base prefix or between successive digits; such underscores do not change the literal's value.
	num = 1_000_000
	fmt.Println("num", num)
	num = 1000_000
	fmt.Println("num", num)
	// e or E followed by an optional sign and decimal digits
	num = 1e6
	fmt.Println("num", num)
	num = 1e6
	fmt.Println("num", num)
}
