package main

import (
	"errors"
	"fmt"
	"runtime"
)

var errA = errors.New("error-a")
var errB = errors.New("error-b")
var errC = errors.New("error-c")

type MyError struct {
	E string
}

// errors.As 의 target 인자으로 사용하기 위해서는 error interface 를 구현해야 한다
func (me *MyError) Error() string {
	return "error:" + me.E
}

func getFuncInfo() string {
	pc, file, line, ok := runtime.Caller(1)
	if !ok {
		return "x"
	}
	fi := runtime.FuncForPC(pc)
	if fi == nil {
		return "x"
	}
	return fmt.Sprintf("%s:%d-%s", file, line, fi.Name())
}

func a() error {
	fmt.Println(getFuncInfo())
	if err := b(); err != nil {
		return fmt.Errorf("error-a\n%w", err)
	}
	return nil
}

func b() error {
	fmt.Println(getFuncInfo())
	if err := c(); err != nil {
		// wrapping error(%w) 를 사용해야 errors.Is 로 체크할 수 있다.
		return fmt.Errorf("error-b\n%w", err)
	}
	return nil
}

func c() error {
	fmt.Println(getFuncInfo())
	return errC
}

func checkError(err error) {
	fmt.Printf("[err stack]\n%+v\n", err)
	if errors.Is(err, errC) {
		fmt.Println("--> Is errC")
	}
	if errors.Is(err, errB) {
		fmt.Println("--> Is errB")
	}
	if errors.Is(err, errA) {
		fmt.Println("--> Is errA")
	}
	// MyError 타입의 에러를 errors.As 로 검출하기
	var me *MyError
	if errors.As(err, &me) {
		fmt.Println("--> As MyError")
	}
}

func main() {
	fmt.Println(getFuncInfo())
	// error 가 wrapping 되어 errC, errB, errA 를 포함하고 있다.
	checkError(a())
	fmt.Println("----------")

	me := MyError{
		E: "lemon",
	}
	err := fmt.Errorf("%w", &me)
	err = fmt.Errorf("apple\n%w", err)
	for err != nil {
		checkError(err)
		// %w 로 wrapping 된 에러를 unwarp
		err = errors.Unwrap(err)
	}
}
