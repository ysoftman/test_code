package main

import (
	"fmt"
	"time"
)

// generic - go 1.18 부터 사용 가능
type Number interface {
	// ~를 붙이면 해당 타입을 별칭으로 사용하는 모든것을 의미
	// ex) time.Duration --> type Duration int64
	int32 | ~int64 | float32 | float64 | string
}

func add[T Number](a, b T) T {
	return a + b
}
func add2[T int | int32 | int64](a, b T) T {
	var result T
	result = a + b
	result += 10_000
	return result
}

// any 는 모든 타입을 의미 하지만 모든 타입이 + operator 가 있는것은 아니니 + 를 사용할순 없다
func add3[T any](a, b T) (T, T) {
	fmt.Println("operator + not defined on a (variable of type T constrained by any)")
	return a, b
}

type AAA struct{ A int }
type BBB struct{ A int }

func add4[T AAA | BBB](a, b int) T {
	var lemon T
	return lemon
}
func add5[T AAA | BBB](lemon T) T {
	fmt.Println("lemon:", lemon)
	// lemon.A undefined (type T has no field or method A) 컴파일 에러발생
	// https://tip.golang.org/doc/go1.18 에서 다음과 같이 제한을 풀기로 했지만..
	// The Go compiler does not support accessing a struct field x.f where x is of type parameter type even if all types in the type parameter’s type set have a field f. We may remove this restriction in a future release.
	// 관련 이슈가 많은데 꽤 오래전 부터 아직 오픈 이슈 https://github.com/golang/go/issues/51259
	// go1.22.1 에서 아직 발생함, 언제 될지 모름...
	//fmt.Println("lemon.A:", lemon.A)

	// workaround, type assertion 된 새로운 변수를 만들어서 사용
	var apple T
	switch any(lemon).(type) {
	case AAA:
		a, _ := any(lemon).(AAA)
		a.A += 111
		apple = T(a)
	case BBB:
		b, _ := any(lemon).(BBB)
		b.A += 222
		apple = T(b)
	default:
		panic(fmt.Sprintf("failed, type: %T\n", lemon))
	}
	//fmt.Println("apple.A", apple.A)
	return apple
}

func main() {
	fmt.Println("generic test...")
	fmt.Println(add(int32(1), int32(2)))
	fmt.Println(add(float32(1), float32(2)))
	fmt.Println(add(time.Duration(1), time.Duration(2)))
	fmt.Println(add("aaa", "bbb"))
	// Number 에 int 은 정의하지 않아 동작은 안됨
	fmt.Println(add2(1, 2))
	fmt.Println(add2(int(1), int(2)))
	fmt.Println(add3(1, 2))
	fmt.Println(add3(1, 2))
	// cannot infer T : 파라메터에 T 가 없어 타입을 추론할 수 없는 경우 호출시 []안에 명시하면 된다. 
	//fmt.Println(add4(1, 2))
	fmt.Println(add4[AAA](1, 2))

	aaa := AAA{A: 1000}
	fmt.Println(add5(aaa))
	bbb := BBB{A: 2000}
	fmt.Println(add5(bbb))
}
