package main

import (
	"context"
	"encoding/json"
	"fmt"
	"gin_server/docs"
	"io"
	"log"
	"net/http"
	"time"

	"github.com/gin-contrib/timeout"
	"github.com/gin-gonic/gin"
	"github.com/mitchellh/mapstructure"
	swaggerfiles "github.com/swaggo/files"
	ginSwagger "github.com/swaggo/gin-swagger"
)

type ServerVersion struct {
	Name      string `json:"Name"`
	Version   string `json:"Version"`
	BuildTime string `json:"BuildTime"`
}

type Data1 struct {
	Data1 string `json:"data1"`
	Data2 uint   `json:"data2"`
}

// @Summary server version
// @Schemes
// @Description get server version
// @Tags v1
// @Accept json
// @Produce json
// @Success 200 {string} server_version
// @Failure 400 {string} string "StatusBadRequest"
// @Failure 500 {string} string "StatusInternalServerError"
// @Router /version [get]
func GetServerVersion(c *gin.Context) {
	ver := ServerVersion{
		Name:    "gin_server",
		Version: "0.0.1",
		//BuildTime: time.Now().Format("20060202150405"),
		BuildTime: time.Now().String(),
	}
	c.JSON(http.StatusOK, ver)
}

// @Summary post data
// @Schemes
// @Description post data test
// @Tags v1
// @Accept json
// @Produce json
// @Param data body Data1 true "requested data"
// @Success 200 {string} string "OK"
// @Failure 400 {string} string "StatusBadRequest"
// @Failure 500 {string} string "StatusInternalServerError"
// @Router /data1 [post]
func PostData(c *gin.Context) {
	data, err := io.ReadAll(c.Request.Body)
	if err != nil {
		c.JSON(http.StatusBadRequest, nil)
		return
	}
	result := Data1{}
	if err := json.Unmarshal([]byte(data), &result); err != nil {
		c.JSON(http.StatusBadRequest, nil)
		return
	}
	result.Data1 = "updated by server"
	result.Data2 = 10
	c.JSON(http.StatusOK, result)
}

type MyData struct {
	key1 int
	key2 string
}

func CheckReq() gin.HandlerFunc {
	return func(c *gin.Context) {
		c.Set("key1", "lemon")
		c.Set("mydata", MyData{111, "ysoftman"})
		fmt.Println("check Request")
	}
}

func timeoutMiddleware1() gin.HandlerFunc {
	tm := 500 * time.Millisecond
	return timeout.New(
		timeout.WithTimeout(tm),
		timeout.WithHandler(func(c *gin.Context) {
			c.Next()
		}),
		timeout.WithResponse(func(c *gin.Context) {
			c.JSON(http.StatusRequestTimeout, gin.H{
				"message": "timeout",
			})
		}),
	)
}
func timeoutMiddleware2() gin.HandlerFunc {
	timeout := 500 * time.Millisecond
	return func(c *gin.Context) {
		ctx, cancel := context.WithTimeout(c.Request.Context(), timeout)
		defer cancel()
		c.Request = c.Request.WithContext(ctx)
		finish := make(chan struct{}, 1)
		panicChan := make(chan interface{}, 1)
		go func() {
			func(c *gin.Context) {
				defer func() {
					if p := recover(); p != nil {
						panicChan <- p
					}
				}()
				c.Next()
			}(c)
			finish <- struct{}{}
		}()

		select {
		//case <-time.After(timeout):
		//    fmt.Println("timeout")
		case p := <-panicChan:
			panic(p)
		case <-finish:
			fmt.Println("finish")
		case <-c.Request.Context().Done():
			err := c.Request.Context().Err()
			if err == nil || err.Error() == "" {
				return
			}
			//context.DeadlineExceeded
			//context.Canceled
			c.JSON(http.StatusRequestTimeout, gin.H{
				"message": err.Error(),
			})
		}
	}
}

func main() {
	fmt.Println("gin server... ")
	//gin.SetMode(gin.ReleaseMode)
	//gin.DisableConsoleColor()

	// json log format
	var jsonLogFormatter = func(param gin.LogFormatterParams) string {
		if param.Latency > time.Minute {
			param.Latency = param.Latency.Truncate(time.Second)
		}
		p := struct {
			//Request   *http.Request
			TimeStamp time.Time
			// StatusCode is HTTP response code.
			StatusCode int
			// Latency is how much time the server cost to process a certain request.
			Latency time.Duration
			// ClientIP equals Context's ClientIP method.
			ClientIP string
			// Method is the HTTP method given to the request.
			Method string
			// Path is a path the client requests.
			Path string
			// ErrorMessage is set if error has occurred in processing the request.
			ErrorMessage string
			// isTerm shows whether gin's output descriptor refers to a terminal.
			isTerm bool
			// BodySize is the size of the Response Body
			BodySize int
			// Keys are the keys set on the request's context.
			Keys map[string]any
		}{
			TimeStamp:    param.TimeStamp,
			StatusCode:   param.StatusCode,
			Latency:      param.Latency,
			ClientIP:     param.ClientIP,
			Method:       param.Method,
			Path:         param.Path,
			ErrorMessage: param.ErrorMessage,
			Keys:         param.Keys,
		}
		param.Request = nil
		out, err := json.Marshal(p)
		if err != nil {
			log.Fatal(err)
		}
		return string(out) + "\n"
	}
	// default(기본 미들웨어가 포함되어 있음) 로 생성하면 기본 로그 포맷터가 추가된 상태이다.
	//router := gin.Default()
	router := gin.New()
	router.Use(gin.LoggerWithFormatter(jsonLogFormatter))
	router.Use(gin.Recovery())
	router.Use(CheckReq())
	//router.Use(timeoutMiddleware1())
	router.Use(timeoutMiddleware2())
	router.GET("/ping", func(c *gin.Context) {
		if v, ok := c.Get("key1"); ok {
			fmt.Println("key1:", v)
		}
		if v, ok := c.Get("mydata"); ok {
			// mydata 원래 strcutre 를 모른다고 가정하고 비슷한 struct 로 담아보자.
			mydata2 := struct {
				key1 int
				key2 string
				key3 string
			}{}
			if err := mapstructure.Decode(v, &mydata2); err == nil {
				fmt.Println("decoded:", v)
			}
		}
		// timeout 발생해보자.
		//time.Sleep(900 * time.Millisecond)

		c.JSON(http.StatusOK, gin.H{
			"message": "pong",
		})
	})
	docs.SwaggerInfo.BasePath = "/api/v1"
	v1 := router.Group("/api/v1")
	{
		v1.GET("/version", GetServerVersion)
		v1.POST("/data1", PostData)
	}
	// swag init to generate/update ./docs
	router.GET("/swagger/*any", ginSwagger.WrapHandler(swaggerfiles.Handler))
	router.Run()
}
