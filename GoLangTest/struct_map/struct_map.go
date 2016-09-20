// author : ysoftman
// encoding : utf-8
// title : strut, map 테스트

package main

import "fmt"

// 구조체
type Data struct {
	a int
	b float64
	c string
}

func main() {
	// 구조체 생성(원소 설정 안함, 기본 숫자형은 0 스트링형은 nil)
	myData1 := Data{}
	fmt.Println("myData1.a = ", myData1.a, "\tmyData1.b = ", myData1.b, "\tmyData1.c = ", myData1.c)

	// 구조체 생성(모든 원소 설정)
	myData2 := Data{123, 3.141592, "ysoftman"}
	fmt.Println("myData2.a = ", myData2.a, "\tmyData2.b = ", myData2.b, "\tmyData2.c = ", myData2.c)

	// 구조체 생성(특정 원소만 설정)
	myData3 := Data{b: 123}
	fmt.Println("myData3.a = ", myData3.a, "\tmyData3.b = ", myData3.b, "\tmyData3.c = ", myData3.c)

	// 맵 생성1
	// 초기화 안된 원소의 기본값은 숫자형은 0 스트링형은 nil
	var mapData1 map[int]string
	// 맵은 사용전 make 를 해야 한다.
	mapData1 = make(map[int]string)
	mapData1[0] = "ysoftman0"
	mapData1[1] = "ysoftman1"
	for i := 0; i < 2; i++ {
		fmt.Println("mapData1[", i, "] = ", mapData1[i])
	}

	// 맵 생성2
	mapData2 := make(map[int]string)
	mapData2[0] = "yoon"
	mapData2[1] = "byoung"
	mapData2[2] = "hoon"
	mapData2[3] = "-"
	// key 값을 순서대로 가져오지는 않는다
	for key, value := range mapData2 {
		fmt.Println("mapData2[", key, "] = ", value)
	}

	// 맵 원소 지우기
	delete(mapData2, 3)
	for key, value := range mapData2 {
		fmt.Println("mapData2[", key, "] = ", value)
	}

	// 맵 생성3
	// 구조체 값
	// 맵은 사용전 make 를 해야 한다.
	mapData3 := make(map[int]Data)
	mapData3[0] = Data{0, 0.0, "string0"}
	mapData3[1] = Data{1, 1.0, "string1"}
	mapData3[2] = Data{2, 2.0, "string2"}
	mapData3[3] = Data{3, 3.0, "string3"}
	for key, value := range mapData3 {
		fmt.Println("mapData3[", key, "] = ", value)
	}

	// Go 언어 map의 값이 struct 형일대 struct 의 field 값 설정 못하는 문제가 있다.
	// 현재로선 struct 대신 *struct 으로 선언해서 사용한 경우에만 struct field 를 설정 할 수 있다.
	// 해당 이슈(https://code.google.com/p/go/issues/detail?id=3117)가 아직 해결되지 않은 상태라고 한다.
	// 자세한 내용은 http://egypt.silverkeytech.com/blogs/third-world/2013/8/you-cannot-assign-a-struct-field-off-map-directly
	// mapData3[3].a = 10
	mapData4 := make(map[int]*Data)
	mapData4[0] = &Data{0, 0.0, "string0"}
	mapData4[0].a = 10

	for key, value := range mapData4 {
		fmt.Println("mapData4[", key, "] = ", value)
	}

}
