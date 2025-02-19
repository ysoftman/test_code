package main

import (
	"net/http"
	"net/http/httptest"
	"testing"

	"github.com/gin-gonic/gin"
	"github.com/stretchr/testify/assert"
)

func TestGINResponse(t *testing.T) {
	w := httptest.NewRecorder()
	c, _ := gin.CreateTestContext(w)
	c.JSON(http.StatusOK, "OK")
	assert.Equal(t, http.StatusOK, w.Code)
	assert.Equal(t, "\"OK\"", w.Body.String())

	w = httptest.NewRecorder()
	c, _ = gin.CreateTestContext(w)
	errResponse := struct {
		ErrorCode int    `json:"error_code"`
		ErrMsg    string `json:"error_message"`
	}{}
	c.JSON(http.StatusNotFound, errResponse)
	assert.Equal(t, http.StatusNotFound, w.Code)
	assert.Equal(t, "{\"error_code\":0,\"error_message\":\"\"}", w.Body.String())
}

func Test_makeServerVersion(t *testing.T) {
	tests := []struct {
		name string
		want ServerVersion
	}{
		{
			name: "makeServerVersion",
			want: ServerVersion{},
		},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			assert.Equal(t, tt.want, makeServerVersion())
		})
	}
}

func TestGetServerVersion(t *testing.T) {
	type args struct {
		c *gin.Context
	}
	tests := []struct {
		name string
		args args
	}{
		// TODO: Add test cases.
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			GetServerVersion(tt.args.c)
		})
	}
}

func TestPostData(t *testing.T) {
	type args struct {
		c *gin.Context
	}
	tests := []struct {
		name string
		args args
	}{
		// TODO: Add test cases.
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			PostData(tt.args.c)
		})
	}
}

func TestCheckReq(t *testing.T) {
	tests := []struct {
		name string
	}{
		{
			name: "CheckReq",
		},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			assert.NotNil(t, CheckReq())
		})
	}
}

func Test_timeoutMiddleware2(t *testing.T) {
	tests := []struct {
		name string
	}{
		{
			name: "timeoutMiddleware2",
		},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			assert.NotNil(t, timeoutMiddleware2())
		})
	}
}
