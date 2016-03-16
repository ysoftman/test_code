// ysoftman
// golang 관련 이것 저것 확인 하려고
package main

import "fmt"

import "strings"
import "strconv"
import "math"
import "sort"

// InfoData : defibrillator 정보
type InfoData *struct {
	ID       int
	Name     string
	Address  string
	Phone    string
	Lon      float32
	Lat      float32
	Distance float32
}

var defibinfo map[int](InfoData)

func main() {

	defibinfo = make(map[int]InfoData)

	// input example
	// 1;Maison de la Prevention Sante;6 rue Maguelone 340000 Montpellier;;3,87952263361082;43,6071285339217
	// 2;Hotel de Ville;1 place Georges Freche 34267 Montpellier;;3,89652239197876;43,5987299452849
	// 3;Zoo de Lunaret;50 avenue Agropolis 34090 Mtp;;3,87388031141133;43,6395872778854

	DEFIB := "1;Maison de la Prevention Sante;6 rue Maguelone 340000 Montpellier;;3,87952263361082;43,6071285339217"

	// cnt := 0

	splitStr := strings.Split(DEFIB, ";")

	for key, value := range splitStr {
		fmt.Println("key:", key, "  value:", value)
	}

	// 자료구조에 담기
	// number, _ := strconv.Atoi(splitStr[0])
	// defibinfo[cnt].ID = number
	// cnt++
	// defibinfo[cnt].Name = splitStr[1]
	// cnt++
	// defibinfo[cnt].Address = splitStr[2]
	// cnt++
	// defibinfo[cnt].Phone = splitStr[3]
	// cnt++
	// var fnum float32
	// fmt.Sscanf(splitStr[0], "%f", &fnum)
	// defibinfo[cnt].Lon = fnum
	// cnt++
	// fmt.Sscanf(splitStr[0], "%f", &fnum)
	// defibinfo[cnt].Lat = fnum
	// cnt++

	// for i := 0; i < 6; i++ {
	// 	fmt.Println(defibinfo[i])
	// }

	// fmt.Fprintln(os.Stderr, "Debug messages...")
	// fmt.Println("answer") // Write answer to stdout

	fmt.Println("math.Cos(90.0):", math.Cos(90.0))
	fmt.Println("math.Sqrt(4):", math.Sqrt(4))
	fmt.Println("math.MaxFloat64:", math.MaxFloat64)
	fmt.Println("math.MaxFloat32:", math.MaxFloat32)
	fmt.Println("math.Ceil(10.5):", math.Ceil(10.5))
	fmt.Println("math.Floor(10.5):", math.Floor(10.5))
	fmt.Println("15/10=", 15/10)
	fmt.Println("float32(15)/float32(10)=", float32(15)/float32(10))

	// 문자열 -> int 변환
	number1 := "123456789"
	out1, _ := strconv.Atoi(number1)
	fmt.Println("number1:", out1)
	out1, _ = strconv.Atoi(string(number1[0]))
	fmt.Println("number1[0]:", out1)

	// 문자열 -> float 변환
	number2 := "12345,6789"
	fmt.Println("number2:", RemoveCommaAndAtoi(number2))
	fmt.Println("number2(to float):", ConvertToFloat(number2))

	// sort 테스트
	num := 10
	aaa := make([]int, num)
	for i := 0; i < 10; i++ {
		aaa[i] = i * 2
	}
	fmt.Println("aaa:", aaa)

	// 간단한 int sort
	mynumlist := []int{2, 3, 6, 45, 6, 246, 1, 12}
	fmt.Println("before sort:", mynumlist)
	sort.Ints(mynumlist)
	fmt.Println("after sort:", mynumlist)

	// sort 인터페이스 사용
	mylist := []MyData{{1}, {3}, {6}, {4}, {1}, {6}}
	fmt.Println("before sort:", mylist)
	sort.Sort(DataList(mylist))
	fmt.Println("after sort:", mylist)

	// 2차원 배열
	width := 3
	height := 3
	var arr [][]int
	arr = make([][]int, height)
	for i := 0; i < height; i++ {
		arr[i] = make([]int, width)
	}
	cnt := 0
	for i := 0; i < height; i++ {
		for j := 0; j < width; j++ {
			arr[i][j] = cnt
			cnt++
		}
	}
	fmt.Println(arr)

	// map 사용
	var mymap map[int](string)
	mymap = make(map[int]string)
	mymap[10] = "number10"
	mymap[20] = "number20"
	fmt.Println(mymap)

	// 노드 및 링크 정보를 저장
	var node map[int]nodeinfo
	node = make(map[int]nodeinfo)
	// 노드에 링크 정보 추가
	node[3] = nodeinfo{
		"node",
		[]int{1, 2},
	}   
	node[3] = nodeinfo{
		"node",
		append(node[3].links, 4),
	}
	node[1] = nodeinfo{
        "node",
        []int{3},
    }
	node[2] = nodeinfo{
        "node",
        []int{3},
    }    
	node[4] = nodeinfo{
        "node",
        []int{3},
    }    
	fmt.Println(node)
	fmt.Println(node[3])
    fmt.Println(node[1])
	fmt.Println(node[2])
    fmt.Println(node[4])
    
    // range 와 for ++ 차이
    myarr := []int{1,2,3,4,5}
    idx := 0
    // idx 가 인덱스 범위까지 증가된다.
    for idx = range myarr {
    }
    fmt.Println("for range:",idx)
    // idx 가 인덱스 범위+1까지 증가된다.   
    for idx = 0; idx<len(myarr); idx++ {
    }
    fmt.Println("for ++:",idx)

    // map struct 포인터타입으로 사용
    var node2 map[int]*nodeinfo
	node2 = make(map[int]*nodeinfo)
    node2[3] = &nodeinfo{}
    node2[3].name = "aaa"
    node2[3].links = []int{1,2}
    fmt.Println("node2", node2)
    fmt.Println("node2", node2[3])
}

type nodeinfo struct {
	name string
	links []int
}

// MyData 내용
type MyData struct {
	num int
}

// DataList 내용
type DataList []MyData

// Less sort Less 인터페이스 구현
func (receiver DataList) Less(a, b int) bool {
	if receiver[a].num < receiver[b].num {
		return true
	}
	return false
}

// Len sort Len 인터페이스 구현
func (receiver DataList) Len() int {
	return len(receiver)
}

// Swap sort Swap 인터페이스 구현
func (receiver DataList) Swap(a, b int) {
	receiver[a], receiver[b] = receiver[b], receiver[a]
}

// RemoveCommaAndAtoi : , 제거후 int 형으로 변환
func RemoveCommaAndAtoi(str string) int {
	numberSplit := strings.Split(str, ",")
	newnumber := ""
	for _, value := range numberSplit {
		newnumber += value
	}
	out, _ := strconv.Atoi(newnumber)
	return out
}

// ConvertToFloat : , 를 소수점으로 계산해서 변환
func ConvertToFloat(str string) float32 {
	numberSplit := strings.Split(str, ",")
	high := numberSplit[0]
	low := numberSplit[1]

	out1, _ := strconv.Atoi(high)
	out2, _ := strconv.Atoi(low)
	result := float32(0.0)
	result += float32(out1)

	// 소수점으로 만들기
	out3 := float32(out2)
	for out3 > 1 {
		out3 = float32(out3) / float32(10)
		// fmt.Println("out1:", out1, " out2:", out2, " out3:", out3)
	}

	result += float32(out3)
	return result
}
