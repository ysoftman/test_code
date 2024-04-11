package main

import (
	"errors"
	"fmt"
)

var errA = errors.New("error-a")
var errB = errors.New("error-b")
var errC = errors.New("error-c")

func checkError(err error) {
	fmt.Printf("err:%v\n", err)
	if errors.Is(err, errC) {
		fmt.Println("Is ErrC...", err)
	}
	if errors.Is(err, errB) {
		fmt.Println("Is ErrB...", err)
	}
	if errors.Is(err, errA) {
		fmt.Println("Is ErrA...", err)
	}
}

func main() {
	fmt.Println("print_error")

	// error 가 wrapping 되어 아래 모두 errC 를 포함하고 있다.
	checkError(c())
	checkError(b())
	checkError(a())

	fmt.Println("----------")

	// %w %w 로 사용하면 multi errors 들이 합쳐지고 마지막 한번만 wrapping 된다.
	err := a()
	unwrapErr := errors.Unwrap(err)
	checkError(unwrapErr)

	fmt.Println("----------")

	err = errA
	err = fmt.Errorf("%w, error-b", err)
	err = fmt.Errorf("%w, error-c", err)
	for err != nil {
		fmt.Println(err)
		// %w 로 wrapping 된 에러를 unwarp
		err = errors.Unwrap(err)
	}
}

func a() error {
	fmt.Println("a()")
	if err := b(); err != nil {
		return fmt.Errorf("%w %w", err, errA)
	}
	return nil
}

func b() error {
	fmt.Println("b()")
	if err := c(); err != nil {
		// wrapping error(%w) 를 사용해야 errors.Is 로 체크할 수 있다.

		return fmt.Errorf("%w %w", err, errB)
	}
	return nil
}

func c() error {
	fmt.Println("c()")
	return errC
}
