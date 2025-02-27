package main

import (
	"bytes"
	"io"
	"log"
	"mime/multipart"
	"net/http"
	"net/http/httptest"
	"os"
	"path/filepath"
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestUpload(t *testing.T) {
	sqldb = NewDB()
	defer sqldb.sqlDB.Close()
	log.Println("connected db")

	cache = NewCache()
	log.Println("created cache")

	w := httptest.NewRecorder()

	rBody := &bytes.Buffer{}
	writer := multipart.NewWriter(rBody)
	file, err := os.Open("cars.csv")
	assert.Equal(t, err, nil)
	part, err := writer.CreateFormFile("filename", filepath.Base(file.Name()))
	assert.Equal(t, err, nil)
	io.Copy(part, file)
	writer.Close()

	r, _ := http.NewRequest(http.MethodGet, "http://", rBody)
	r.Header.Add("Content-Type", writer.FormDataContentType())
	// fmt.Printf("===request=== %#v", r)
	uploadData(w, r)

	resp := w.Result()

	assert.Equal(t, resp.StatusCode, http.StatusOK)
	defer resp.Body.Close()
	data, err := io.ReadAll(resp.Body)
	if err != nil {
		t.Errorf("error to be nil, got %v", err)
	}
	assert.Contains(t, string(data), "file is inserted")
}

func TestQuery(t *testing.T) {
	sqldb = NewDB()
	defer sqldb.sqlDB.Close()
	log.Println("connected db")

	cache = NewCache()
	log.Println("created cache")

	w := httptest.NewRecorder()
	rBody := bytes.NewBufferString("select * from ds_cars")
	r, _ := http.NewRequest(http.MethodPost, "http://", rBody)
	// fmt.Printf("===request=== %#v", r)
	queryData(w, r)

	resp := w.Result()
	assert.Equal(t, resp.StatusCode, http.StatusOK)
	defer resp.Body.Close()
	data, err := io.ReadAll(resp.Body)
	// log.Println("====", string(data))
	if err != nil {
		t.Errorf("error to be nil, got %v", err)
	}
	assert.Contains(t, string(data), "44,0,33,4169,7424,8082")
}
