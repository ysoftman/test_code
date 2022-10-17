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
	// 파일 내용 출력
	return ctx.File("resp_sample.txt")
	// 이미지면 inline 처럼 동작
	// return ctx.File("xelloss.jpg")
	// binary 파일이면 브라우저에서는 attachment 처럼 동작
	// return ctx.Inline("ysoftman_100MB.tmp", "resp_sample_inline.txt")
}

func GetFileInline(ctx echo.Context) error {
	res := Response{
		Message: "get file(ok)",
	}
	fmt.Println("---GetFileInline---", res)
	// 브라우저에서 파일을 실행하거,미리보기할 수 있는지 체크한다. 아니면 attachment 처럼 동작
	// 텍스파일이면 파일 내용이 브라우저에 보인다.
	// return ctx.Inline("resp_sample.txt", "resp_sample_inline.txt")
	// 이미지이면 이미지가 브라우저에 보인다.
	return ctx.Inline("xelloss.jpg", "xellos.jpg")
	// binary 파일이면 브라우저에서는 attachment 처럼 동작한다.
	// return ctx.Inline("ysoftman_100MB.tmp", "resp_sample_inline.txt")
}

func GetFileAttachment(ctx echo.Context) error {
	res := Response{
		Message: "get file(ok)",
	}
	fmt.Println("---GetFileAttachment---", res)
	// 브라우저에서 http://localhost:8080/file-attachment 요청하면 파일 저장 팝업이 뜬다.
	return ctx.Attachment("resp_sample.txt", "save_resp_sample.txt")
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
	e.GET("/file-inline", GetFileInline)
	e.GET("/file-attachment", GetFileAttachment)
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
