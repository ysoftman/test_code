package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

// go test -v ./log_test.go

func TestAAA(t *testing.T) {
	actual := "lemon"
	expected := "lemon"
	assert.Equal(t, expected, actual)

	// 테스트를 더이상 진행하지 않고 종료(exit:1)한다.
	// t.Fatal("ysoftman")

	actual = "apple"
	assert.Equal(t, expected, actual)

	actual = "lemon"
	assert.Equal(t, expected, actual)
}
