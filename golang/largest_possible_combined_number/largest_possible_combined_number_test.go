// author : ysoftman
// encoding : utf-8
// title : largest possible combined number
// desc : 조합 가능한 숫자들 중 가장 큰 숫자 찾기 테스트
package lpcn

import "testing"

func Test_largest_possible_combined_number(t *testing.T) {
	if largest_possible_combined_number(50, 2, 1, 9) == "95021" {
		t.Log("expected.")
	} else {
		t.Error("unexpected.")
	}
	if largest_possible_combined_number(5, 50, 56) == "56550" {
		t.Log("expected.")
	} else {
		t.Error("unexpected.")
	}
	if largest_possible_combined_number(420, 42, 423) == "42423420" {
		t.Log("expected.")
	} else {
		t.Error("unexpected.")
	}
}
