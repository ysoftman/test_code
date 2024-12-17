// author : ysoftman
// encoding : utf-8
// title : largest possible combined number
// desc : 조합 가능한 숫자들 중 가장 큰 숫자 찾기
package lpcn

import (
	"fmt"
	"strconv"
)

func largest_possible_combined_number(args ...int) string {
	// 큰 숫자가 될 수 있는 경우로 args 정렬하기
	for i := 0; i < len(args); i++ {

		for k := 0; k < len(args)-1; k++ {

			num1, _ := strconv.Atoi(strconv.Itoa(args[k]) + strconv.Itoa(args[k+1]))
			num2, _ := strconv.Atoi(strconv.Itoa(args[k+1]) + strconv.Itoa(args[k]))
			if num1 < num2 {
				temp := args[k]
				args[k] = args[k+1]
				args[k+1] = temp
			}
			// for debug
			for _, v := range args {
				fmt.Printf("%d ", v)
			}
		}
		// for debug
		fmt.Println("")
	}

	// 정렬된 숫자를 이어보면 가장 큰 숫자가 된다.
	str_cur_num := ""
	for _, v := range args {
		str_cur_num += strconv.Itoa(v)
	}
	fmt.Println(str_cur_num)

	return str_cur_num
}
