package main

import "fmt"

func main() {
	func() {
		// string 은 변경불가능하기때문에 byte 슬라이스로 변환해서 변경하도록한다.
		str := "ysoftman"
		fmt.Printf("str: %s\n", str)
		// str[0] = 'a' // 스트링은 변경 불가능하기 때문에 컴파일 에러(strings are immutable) 발생
		strslice := []byte(str)
		fmt.Println("strslice:", strslice, "len:", len(strslice))
		fmt.Printf("strslice = %s\n", strslice)
		strslice[0] = 'Y'
		strslice[len(strslice)-1] = 'N'
		fmt.Println("strslice[0]: 'Y'")
		fmt.Println("strslice[len(strslice)-1]: 'N'")
		fmt.Printf("strslice: %s\n", strslice)
		str = string(strslice)
		fmt.Printf("str: string(strslice), str: %s\n", str)
	}()

}
