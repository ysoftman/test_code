// ysoftman
// goconvey 로 테스트하가

// 섪치
// go get github.com/smartystreets/goconvey
// goconvey 웹 실행(_test.go 파일 위치에서)
// $GOPATH/bin/goconvey
// goconvey 모니터링
// http://localhost:8080
package a

import "testing"

// import . 명시하면 패키지의 export 된 모든 identifier 에 대해 qualifier 없이 액세스 가능
// import _ 명시하면 패키지의 초기화 사이드 이펙트만 반영
// import   "lib/math"         math.Sin
// import m "lib/math"         m.Sin
// import . "lib/math"         Sin
// import _ "lib/math"
import . "github.com/smartystreets/goconvey/convey"

func TestMYTest1(t *testing.T) {

	Convey("x=1", t, func() {
		x := 1
		Convey("x증가", func() {
			x++
			Convey("x는 2와 같아야 한다.", func() {
				So(x, ShouldEqual, 2)
			})
		})
	})

	Convey("x=100", t, func() {
		x := 100
		Convey("x!=101", func() {
			So(x, ShouldNotEqual, 101)
		})
		Convey("x==100", func() {
			So(x, ShouldNotEqual, 101)
		})
	})

}
