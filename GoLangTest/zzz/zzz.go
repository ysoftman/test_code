// ysoftman
// golang 관련 이것 저것 확인 하려고
package main

import "fmt"

import "strings"

import "math"

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

}

