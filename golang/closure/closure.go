// ysoftman
// closure test
package main

import "fmt"

func count() func() int {
	cnt := 0
	// 내부함수(클로저)에서 cnt 변수를 참조하여 count() 함수가 종료되어서 클로저에서 cnt 값은 유지된다.
	return func() int {
		cnt++
		return cnt
	}
}
func main() {
	fmt.Println("Closure test")

	// count() 호출해서 클로저 함수 인스터를 caller 에 할당
	caller := count()

	for i := 0; i < 10; i++ {
		// caller 변수로 클로저를 호출하면
		// 클로저 내부의 cnt 변수가 유지되는것을 알 수 있다.
		fmt.Println(caller())
	}
}
