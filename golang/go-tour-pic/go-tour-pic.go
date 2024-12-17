// author : ysoftman
// encoding : utf-8
// title : go-tour-pic 예제
package main

// code.google.com/p/go-tour/pic 는 다운로드 되지 않는다.
// tour.golang.org 온라인에서 실행할것
import "code.google.com/p/go-tour/pic"

func Pic(dx, dy int) [][]uint8 {
	result := make([][]uint8, dy)

	for y := 0; y < dy; y++ {
		result[y] = make([]uint8, dx)
		for x := 0; x < dx; x++ {
			result[y][x] = uint8(x ^ y)
			// result[y][x] = uint8((x+y)/2)
			// result[y][x] = uint8(x*y)
		}
	}
	return result
}

func main() {
	pic.Show(Pic)
}
