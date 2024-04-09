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
