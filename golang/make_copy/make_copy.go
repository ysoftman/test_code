// ysoftman
// slice make copy 테스트
package main

import "fmt"

type innerData struct {
	number int
	str    string
}
type myData struct {
	name   string
	inData []innerData
}

func main() {

	val1 := []string{"lemon", "apple", "orange"}
	val2 := []string{}
	fmt.Println("val1:", val1)
	fmt.Println("val2:", val2)

	// make 하지 않으면 복사 되지 않는다.
	copy(val2, val1)
	fmt.Println("val2:", val2)

	// make 된 크기만큼 복사된다.
	val2 = make([]string, 2)
	copy(val2, val1)
	fmt.Println("val2:", val2)
	val2 = make([]string, len(val2))
	copy(val2, val1)
	fmt.Println("val2:", val2)

	// make 로 초기화해 다시 복사
	val3 := []string{"aaa", "bb"}
	val2 = make([]string, len(val3))
	copy(val2, val3)
	fmt.Println("val2:", val2)

	// struct 복사
	mydata1 := make([]myData, 2)
	mydata1[0].name = "first"
	mydata1[0].inData = []innerData{{1, "a"}, {2, "b"}}
	mydata1[1].name = "second"
	mydata1[1].inData = []innerData{{3, "c"}}
	mydata2 := make([]myData, 2)
	copy(mydata2, mydata1)
	fmt.Printf("mydata1: %+v\n", mydata1)
	fmt.Printf("mydata2: %+v\n", mydata2)

}
