// author : ysoftman
// encoding : utf-8
// desc : echo web framework test
package main

import (
	"net/http"

	"github.com/labstack/echo"
	"github.com/labstack/echo/middleware"
)

func main() {
	// create echo instance
	e := echo.New()

	// use middleware
	e.Use(middleware.Logger())
	e.Use(middleware.Recover())

	// route
	e.GET("/", root_path)

	// start
	e.Start("127.0.0.1:1234")

}

func root_path(c echo.Context) error {
	return c.String(http.StatusOK, "response root path contents")
}
