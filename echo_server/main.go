package main

import (
	"fmt"
	"log"
	"net/http"

	"github.com/labstack/echo"
)

func GetFile(ctx echo.Context) error {
	res := struct {
		Message string `json:"message"`
	}{
		Message: "get file(ok)",
	}
	fmt.Println("---GetFile---", res)
	return ctx.JSON(http.StatusOK, &res)
}

func main() {
	e := echo.New()
	e.GET("/file", GetFile)

	if err := e.Start("127.0.0.1:8080"); err != nil {
		log.Fatal("failed to start echo server")
	}
}
