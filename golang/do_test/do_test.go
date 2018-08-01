// author : ysoftman
// encoding : utf-8
// title : testing 테스트
// desc :
// 테스트 대상 파일명은 _test.go 로 끝나야하고, 함수명은 TestX(Test대문자)로 시작해야 한다.
// go test -v 파일명.go 로 전체 TestXXX 함수들 테스트
// go test -v -run 함수명 으로 특정 함수(들)만 테스트
// assert 기능 사용을 위한 패키지 추가
// go get github.com/stretchr/testify
package testSomething

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestPrint1(t *testing.T) {

	actual1 := 300
	actual2 := 300
	expected := 500

	if actual1+actual2 > expected {
		t.Logf("기대한대로 값이 나옴, 성공")
	} else {
		t.Errorf("실패")
	}
}

func TestPrint2(t *testing.T) {
	actual1 := 100
	actual2 := 200
	expected := 100

	// testify 패키지 사용
	assert.NotEqual(t, actual1+actual2, expected)
	assert.Equal(t, actual1+actual2, 300)
}
