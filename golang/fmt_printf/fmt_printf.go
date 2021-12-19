package main

import "fmt"

func main() {
	// https://pkg.go.dev/fmt
	// %v	the value in a default format, when printing structs, the plus flag (%+v) adds field names
	// %#v	a Go-syntax representation of the value
	// %T	a Go-syntax representation of the type of the value
	// %%	a literal percent sign; consumes no value
	// %t	the word true or false
	// %b	base 2
	// %c	the character represented by the corresponding Unicode code point
	// %d	base 10
	// %o	base 8
	// %O	base 8 with 0o prefix
	// %q	a single-quoted character literal safely escaped with Go syntax.
	// %x	base 16, with lower-case letters for a-f
	// %X	base 16, with upper-case letters for A-F
	// %U	Unicode format: U+1234; same as "U+%04X"
	// %s	the uninterpreted bytes of the string or slice
	// %q	a double-quoted string safely escaped with Go syntax
	// %x	base 16, lower-case, two characters per byte
	// %X	base 16, upper-case, two characters per byte
	// %p	(slice) address of 0th element in base 16 notation, with leading 0x
	// %p	(pointer) base 16 notation, with leading 0x
	boolean := true
	fmt.Println("----- [boolean] -----")
	fmt.Printf("%%T: %T\n", boolean)
	fmt.Printf("%%t: %t\n", boolean)
	fmt.Printf("%%#v: %#v\n", boolean)
	fmt.Printf("%%p: %p\n", &boolean)
	fmt.Printf("%%v: %v\n", boolean)

	num := 12
	fmt.Println("----- [number] -----")
	fmt.Printf("%%T: %T\n", num)
	fmt.Printf("%%#v: %#v\n", num)
	fmt.Printf("%%p: %p\n", &num)
	fmt.Printf("%%v: %v\n", num)
	fmt.Printf("%%d: %d\n", num)
	fmt.Printf("%%b: %b\n", num)
	fmt.Printf("%%o: %o\n", num)
	fmt.Printf("%%O: %O\n", num)
	fmt.Printf("%%x: %x\n", num)
	fmt.Printf("%%X: %X\n", num)
	fmt.Printf("%%U: %U\n", num)

	pt := &num
	fmt.Println("----- [pointer] -----")
	fmt.Printf("%%T: %T\n", pt)
	fmt.Printf("%%T: %T\n", *pt)
	fmt.Printf("%%v: %v\n", pt)
	fmt.Printf("%%v: %v\n", &pt)
	fmt.Printf("%%v: %v\n", *pt)

	str := "lemon가나"
	fmt.Println("----- [string] -----")
	fmt.Printf("%%#v: %#v\n", str)
	fmt.Printf("%%p: %p\n", &str)
	fmt.Printf("%%v: %v\n", str)
	fmt.Printf("%%s: %s\n", str)
	fmt.Printf("%%q: %q\n", str)
}
