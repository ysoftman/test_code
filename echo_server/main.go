// author : ysoftman
// encoding : utf-8
// desc : echo web framework test
package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"path/filepath"

	"github.com/labstack/echo"
	"github.com/labstack/echo/middleware"
	"golang.org/x/text/message"
)

type Response struct {
	Message string `json:"message"`
}

func GetFile(ctx echo.Context) error {
	res := Response{
		Message: "get file(ok)",
	}
	fmt.Println("---GetFile---", res)
	return ctx.JSON(http.StatusOK, &res)
}

func UploadFile(ctx echo.Context) error {
	dstfilename := ctx.QueryParam("dstfilename")
	p := message.NewPrinter(message.MatchLanguage("en"))

	// MultipartForm 내용 파악
	form, err := ctx.MultipartForm()
	if err != nil {
		return err
	}

	// "upload 이름으로 업로드되는 파일 파악"
	files := form.File["upload"]
	for _, file := range files {
		src, err := file.Open()
		if err != nil {
			return err
		}
		defer src.Close()
		dst, err := os.Create(filepath.Join("./", dstfilename))
		if err != nil {
			return err
		}
		defer dst.Close()
		var written int64
		if written, err = io.Copy(dst, src); err != nil {
			return err
		}
		p.Printf("(uploadfile) written bytes: %d", written)
	}
	res := Response{
		Message: "upload file(ok)",
	}
	return ctx.JSON(http.StatusOK, &res)
}
func main() {
	e := echo.New()

	// use middleware
	e.Use(middleware.Logger())
	e.Use(middleware.Recover())

	e.GET("/file", GetFile)
	e.POST("/file", UploadFile)

	// route
	e.GET("/", root_path)

	if err := e.Start("127.0.0.1:8080"); err != nil {
		log.Fatal("failed to start echo server")
	}
}

func root_path(c echo.Context) error {
	return c.String(http.StatusOK, "response root path contents")
}
