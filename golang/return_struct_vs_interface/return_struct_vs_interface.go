package main

import "fmt"

type Apple interface {
	GetName() string
	ForApple() string
}
type Lemon interface {
	GetName() string
	ForLemon() string
}

type Fruit struct {
	Name string
}

// https://go.dev/wiki/CodeReviewComments#interfaces
// interface 는 사용하는 쪽 패키지다, 구현하는쪽 패키지가 아니다.
// 리턴을 struct 타입은 명확하고 리팩토링에 용이하다
// func NewFruit(name, color string) Lemon {
func NewFruit(name string) *Fruit {
	return &Fruit{
		Name: name,
	}
}
func (f *Fruit) GetName() string {
	return f.Name
}
func (f *Fruit) ForApple() string {
	return "red"
}
func (f *Fruit) ForLemon() string {
	return "yellow"
}
func (f *Fruit) SomethingForFruit() string {
	return "something for fruit"
}

func main() {
	fmt.Println("-----")
	// 사용하는 쪽에서 interface 로 필요한 것만 구별한다.
	var apple Apple = NewFruit("apple")
	fmt.Println(apple.GetName())
	fmt.Println(apple.ForApple())
	//fmt.Println(apple.ForLemon())  // lemon interface 또는 fruit struct 만 가능

	fmt.Println("-----")
	var lemon Lemon = NewFruit("lemon")
	fmt.Println(lemon.GetName())
	//fmt.Println(lemon.ForApple()) // apple interface 또는 fruit struct 만 가능
	fmt.Println(lemon.ForLemon())

	fmt.Println("-----")
	fruit := NewFruit("apple")
	fmt.Println(fruit.GetName())
	fmt.Println(fruit.ForApple())
	fmt.Println(fruit.ForLemon())
	fmt.Println(fruit.SomethingForFruit())
}
