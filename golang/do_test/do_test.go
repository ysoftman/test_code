// author : ysoftman
// encoding : utf-8
// title : testing 테스트
// desc : go test -v -run 함수명 으로 특정 함수만 테스트
//		go test -v 파일명.go 로 전체 TestXXX 함수들 테스트
//		참고로 liteide 에선 Ctrl + t)
// caution : .go 파일 이름에 testing 이 존재하면 [no test files] 가 발생하여,
//		 테스트코드가 실행되지 않음
package test_something

import "testing"

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
	if actual1+actual2 > expected {
		t.Logf("기대한대로 값이 나옴, 성공")
	} else {
		t.Errorf("실패")
	}
}
