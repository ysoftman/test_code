package main

import (
	"errors"
	"fmt"
	"runtime"
)

var (
	errA     = errors.New("error-a")
	errCopyA = errors.New("error-a")
	errB     = errors.New("error-b")
	errC     = errors.New("error-c")
)

type MyError struct {
	Err  error
	Mesg string
}

// errors.As 의 target 인자으로 사용하기 위해서는 error interface 를 구현해야 한다
func (me *MyError) Error() string {
	return "error:" + me.Mesg
}

func (me *MyError) CustomErrMessage() string {
	return "[custom-err-message] " + me.Mesg
}

var errLemon = &MyError{
	Err:  nil,
	Mesg: "lemon",
}

var errApple = &MyError{
	Err:  nil,
	Mesg: "apple",
}

func findMyError(err error) (*MyError, bool) {
	for err != nil {
		if e, ok := err.(*MyError); ok {
			return e, true
		}
		err = errors.Unwrap(err)
	}
	return nil, false
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
	// Is(),  As() 는 err 를 재귀적으로 unwrap 해 비교한다.
	// Is() 같은(데이터주소가 같음) 에러인지 체크
	if errors.Is(err, errA) {
		fmt.Println("--> Is errA")
	}
	if errors.Is(err, errB) {
		fmt.Println("--> Is errB")
	}
	if errors.Is(err, errC) {
		fmt.Println("--> Is errC")
	}
	if errors.Is(err, errLemon) {
		fmt.Println("--> Is errLemon")
	}
	// errApple 포인터에 err데 할당에 성공(true)하면 errApple 로 사용할 수 있다.
	// errApple, errLemon 모두 같은 타입으로 아래 2개 As 에서 true 가 된다
	if errors.As(err, &errApple) {
		fmt.Println("--> As errApple", errApple.CustomErrMessage())
	}
	if errors.As(err, &errLemon) {
		fmt.Println("--> As errLemon", errLemon.CustomErrMessage())
	}
}

func main() {
	fmt.Println(getFuncInfo())

	if errA == errCopyA {
		fmt.Println("errA == errCopyA")
	} else {
		fmt.Println("errA != errCopyA")
	}

	errAA := errA
	if errA == errAA {
		fmt.Println("errA == errAA")
	} else {
		fmt.Println("errA != errAA")
	}

	checkError(errCopyA)
	fmt.Println("----------")
	checkError(errAA)
	fmt.Println("----------")

	me := &MyError{
		Err:  a(),
		Mesg: "apple",
	}
	checkError(me)
	fmt.Println("----------")

	// wrap error 에서 MyError 찾기
	if e, ok := findMyError(me); ok {
		fmt.Println("found MyError", e)
	}
	fmt.Println("----------")

	// unwrap error
	err := me.Err
	for err != nil {
		checkError(err)
		// %w 로 wrapping 된 에러를 unwrap
		err = errors.Unwrap(err)
	}
}
