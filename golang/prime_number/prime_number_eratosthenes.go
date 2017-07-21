// author : ysoftman
// encoding : utf-8
// title : Sieve of Eratosthenes(에라토스테네스의 체) 방법으로 소수 구하기
// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
// https://ko.wikipedia.org/wiki/%EC%97%90%EB%9D%BC%ED%86%A0%EC%8A%A4%ED%85%8C%EB%84%A4%EC%8A%A4%EC%9D%98_%EC%B2%B4
package main

import "fmt"

func prime_number_by_eratosthenes(num int, prime_number *[]int) {
	if num < 2 {
		return
	}
	// 소수가 될 수 있는 후보 숫자들
	candidate_number := make([]bool, num+1)

	// 처음엔 모두 소수라고 취급
	for i := 2; i <= num; i++ {
		candidate_number[i] = true
	}

	// i*i 까지만 검사하면 됨
	for i := 2; i*i <= num; i++ {
		if candidate_number[i] == true {
			// i 의 배수만큼에 해당하는 숫자는 소수가 아님
			for j := i * i; j <= num; j += i {
				candidate_number[j] = false
			}
		}
	}
	// 배수로 체크되지 않는 숫자가 결국 소수가 됨
	for i := 0; i <= num; i++ {
		if candidate_number[i] == true {
			*prime_number = append(*prime_number, i)
		}
	}

}

func main() {
	//	prime_number := make([]int, 0, 0)
	prime_number := []int{}
	prime_number_by_eratosthenes(100, &prime_number)

	fmt.Println("[Prime number]")
	// 찾은 소수 출력
	for _, v := range prime_number {
		fmt.Println(v)
	}
	fmt.Println("cnt = ", len(prime_number))
}
