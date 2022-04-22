package main

import "fmt"

type Fruit struct {
	name string
	cost int
}

// call by value : struct 복사
func changeFruit1(f Fruit) {
	f.name = "apple"
	f.cost = 200
	fmt.Printf("%20s %p %#v\n", "(changeFruit1)", &f, f)
}

// call by reference : caller struct 참조
func changeFruit2(f *Fruit) {
	f.name = "orange"
	f.cost = 500
	fmt.Printf("%20s %p %#v\n", "(changeFruit2)", &f, f)
}
func main() {
	f := Fruit{"lemon", 100}
	fmt.Printf("%20s %p %#v\n", "(main)", &f, f)

	changeFruit1(f)
	fmt.Printf("%20s %p %#v\n", "(main)", &f, f)

	changeFruit2(&f)
	fmt.Printf("%20s %p %#v\n", "(main)", &f, f)
}
