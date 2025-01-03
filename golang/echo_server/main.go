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

	"github.com/labstack/echo/v4"
	"github.com/labstack/echo/v4/middleware"
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
	return ctx.File("sample.txt")
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
	// return ctx.Inline("sample.txt", "resp_sample_inline.txt")
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
	return ctx.Attachment("sample.txt", "save_sample.txt")
}

func UploadFile(ctx echo.Context) error {
	// dstfilename := ctx.QueryParam("dstfilename")
	p := message.NewPrinter(message.MatchLanguage("en"))

	p.Println("(uploadfile) MultipartForm()")
	// MultipartForm 내용 파악
	// os.TempDir($TMPDIR 없으면 /tmp)위치에 multipart-3000453554 형식으로 임시파일로 다운로드 받는다.
	// 파일 다운로드는 전송중인 데이터를 on the fly 로 바로 파일로 쓰기 때문에
	// watch -n 1 dust -c $TMPDIR 로 확인해보면 임시 파일이 늘어나는것을 확인할 수 있다.(추후 자동 삭제)
	// 추가로 echo MultipartForm() 코드를 확인해본 결과
	// echo MultipartForm() 에서는 golang http > request > ParseMultipartForm(32MB메모리크기) 호출
	// ParseMultipartForm > ReadForm > readForm > ... 파일 크기가 32MB 보다 크면 os.CreateTemp("", "multipart-") 수행
	form, err := ctx.MultipartForm()
	if err != nil {
		return err
	}

	// form 내용 살펴보기
	fmt.Println("-----")
	for k, v := range form.File {
		p.Println(k)
		for i := 0; i < len(v); i++ {
			p.Println(v[i].Filename)
		}
	}
	fmt.Println("-----")
	for _, v := range form.Value {
		p.Println(v)
		for i := 0; i < len(v); i++ {
			p.Println(v[i])
		}
	}

	fmt.Println("-----")
	p.Println("(uploadfile) form.File[\"upload\"]")
	// "upload 이름으로 업로드되는 파일 파악"
	files := form.File["upload"]
	for _, file := range files {
		src, err := file.Open()
		if err != nil {
			return err
		}
		defer src.Close()
		p.Printf("(uploadfile) open file: %v\n", file.Filename)

		dst, err := os.Create(filepath.Join("./", file.Filename+".dst.tmp"))
		if err != nil {
			return err
		}
		defer dst.Close()
		var written int64
		if written, err = io.Copy(dst, src); err != nil {
			return err
		}
		p.Printf("(uploadfile) written bytes: %d\n", written)
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
