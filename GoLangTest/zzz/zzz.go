// ysoftman
// golang 관련 이것 저것 확인 하려고
package main

import "fmt"

import "strings"
import "strconv"
import "math"
import "sort"
import "os"
import "container/list"

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
	myarr := []MyData{{1}, {3}, {6}, {4}, {1}, {6}}
	fmt.Println("before sort:", myarr)
	sort.Sort(DataList(myarr))
	fmt.Println("after sort:", myarr)

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
		append(node[3].node, 4),
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

	// map struct 포인터타입으로 사용
	var node2 map[int]*nodeinfo
	node2 = make(map[int]*nodeinfo)
	node2[3] = &nodeinfo{}
	node2[3].name = "aaa"
	node2[3].node = []int{1, 2}
	fmt.Fprintln(os.Stderr, "node2", node2)
	// fmt.Println("node2", node2)
	fmt.Fprintln(os.Stderr, "node2[3]", node2[3])
	// fmt.Println("node2[3]", node2[3])

	// float int 처리 테스트
	op1 := 2
	op2 := 5
	fmt.Printf("op1:%v %f\n", op1, float32(op1))
	fmt.Printf("op2:%v %f\n", op2, float32(op2))
	fmt.Printf("op2-op1:%v %f\n", op2-op1, float32(op2-op1))
	fmt.Printf("op2/op1:%v %f\n", op2/op1, float32(op2/op1))
	fmt.Printf("op2/op1:%v %f\n", op2/op1, float32(op2)/float32(op1))

	// list 컨테이너 테스트
	mylist := list.New()
	mylist.PushBack("aaa")
	mylist.PushBack(111)
	el := mylist.PushFront(123)
	mylist.InsertBefore(222, el)
	// fmt.Println(mylist)
	for iter := mylist.Front(); iter != nil; iter = iter.Next() {
		fmt.Println(iter.Value)
	}

	// 숫자스트링 파악 테스트
	phonenumber := "0101234567"
	for i := 0; i < len(phonenumber); i++ {
		n, _ := strconv.Atoi(string(phonenumber[i]))
		fmt.Println(n)
	}
}

type nodeinfo struct {
	name string
	node []int
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
