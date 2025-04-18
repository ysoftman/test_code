package main

import (
	"context"
	"encoding/json"
	"fmt"
	"gin_server/docs"
	"io"
	"log"
	"net/http"
	"os"
	"runtime/debug"
	"strings"
	"time"

	"github.com/gin-contrib/pprof"
	"github.com/gin-gonic/gin"
	"github.com/mitchellh/mapstructure"
	swaggerfiles "github.com/swaggo/files"
	gin_swagger "github.com/swaggo/gin-swagger"
)

var (
	// 빌드시 다음과 같이 설정한다.(Makefile 참고)
	// go build -ldflags '-X "main.name=gin_server" -X "main.version=0.0.1"'
	name            string
	version         string
	build_time      string
	build_unix_time string
	git_hash        string
	server_os       string // os 로 하면 os 패키지 import 할때 겹친다.
	arch            string
)

type ServerVersion struct {
	Name          string `json:"name"`
	Version       string `json:"version"`
	BuildTime     string `json:"build_time"`
	BuildUnixTime string `json:"build_unix_time"`
	GitHash       string `json:"git_hash"`
	OS            string `json:"os"`
	Arch          string `json:"arch"`
}

type Data1 struct {
	Data1 string `json:"data1"`
	Data2 uint   `json:"data2"`
}

func makeServerVersion() ServerVersion {
	return ServerVersion{
		Name:          name,
		Version:       version,
		BuildTime:     build_time,
		BuildUnixTime: build_unix_time,
		GitHash:       git_hash,
		OS:            server_os,
		Arch:          arch,
	}
}

// GetServerVersion
//
//	@Summary	server version
//	@Schemes
//	@Description	get server version
//	@Tags			v1
//	@Accept			json
//	@Produce		json
//	@Success		200	{string}	server_version
//	@Failure		400	{string}	string	"StatusBadRequest"
//	@Failure		500	{string}	string	"StatusInternalServerError"
//	@Router			/version [get]
func GetServerVersion(c *gin.Context) {
	SetResponse(c, http.StatusOK, makeServerVersion())
}

// PostData
//
//	@Summary	post data
//	@Schemes
//	@Description	post data test
//	@Tags			v1
//	@Accept			json
//	@Produce		json
//	@Param			data	body		Data1	true	"requested data"
//	@Success		200		{string}	string	"OK"
//	@Failure		400		{string}	string	"StatusBadRequest"
//	@Failure		500		{string}	string	"StatusInternalServerError"
//	@Router			/data1 [post]
func PostData(c *gin.Context) {
	data, err := io.ReadAll(c.Request.Body)
	if err != nil {
		SetResponse(c, http.StatusBadRequest, nil)
		return
	}
	result := Data1{}
	if err := json.Unmarshal(data, &result); err != nil {
		SetResponse(c, http.StatusBadRequest, nil)
		return
	}
	SetResponse(c, http.StatusOK, result)
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

//	func timeoutMiddleware1() gin.HandlerFunc {
//	   tm := 500 * time.Millisecond
//	   return timeout.New(
//	       timeout.WithTimeout(tm),
//	       timeout.WithHandler(func(c *gin.Context) {
//	           c.Next()
//	       }),
//	       timeout.WithResponse(func(c *gin.Context) {
//	           SetResponse(c, http.StatusRequestTimeout, gin.H{
//	               "message": "timeout",
//	           })
//	       }),
//	   )
//	}
func timeoutMiddleware2() gin.HandlerFunc {
	timeout := 500 * time.Millisecond
	return func(c *gin.Context) {
		if strings.HasPrefix(c.Request.URL.Path, "/debug/pprof") {
			return
		}

		ctx, cancel := context.WithTimeout(c.Request.Context(), timeout)
		defer cancel()
		c.Request = c.Request.WithContext(ctx)
		finish := make(chan struct{}, 1)
		panicChan := make(chan any, 1)
		go func() {
			// 채널 보내기 후 닫을 수 있도록 보장
			// 부모에서 close 채널하지 않는 이유는
			// 타임아웃 발생으로 부모가 더 빨리 종료되는 경우
			// 채널이 닫힌 상태에서 채널로 보내기가 시도될 수 있기 때문.
			// 참고로 채널이 닫힌 후에도 receive 는 가능.
			defer func() {
				close(panicChan)
				close(finish)
			}()
			func(c *gin.Context) {
				defer func() {
					if r := recover(); r != nil {
						// plain text 로 출력시
						debug.PrintStack()
						// json 으로 출력시
						panicLog := make(map[string]string)
						panicLog["error"] = fmt.Sprintf("%v", r)
						panicLog["stack"] = fmt.Sprintf("[debug.Stack] begin\n%s\n[debug.Stack] end\n", string(debug.Stack()))
						panicJson, err := json.Marshal(panicLog)
						if err != nil {
							fmt.Fprintln(os.Stderr, "marshaling panic log failed:", err)
						} else {
							fmt.Fprintln(os.Stderr, string(panicJson))
						}
						panicChan <- r
					}
				}()
				c.Next()
			}(c)
			finish <- struct{}{}
		}()

		select {
		// case <-time.After(timeout):
		//    fmt.Println("timeout")
		case p := <-panicChan:
			panic(p)
		case <-finish:
			fmt.Println("finish")
			Response(c)
		case <-c.Request.Context().Done():
			err := c.Request.Context().Err()
			if err == nil || err.Error() == "" {
				return
			}
			// context.DeadlineExceeded
			// context.Canceled
			SetResponse(c, http.StatusRequestTimeout, gin.H{
				"message": err.Error(),
			})
			Response(c)
		}
	}
}

const GinResponse = "GinResponse"

type GinResponseData struct {
	Status int
	Object any
}

// 응답하고 finish 채널로 완료  신호를 보내기 전에 timeout 이 발생하면 응답이 중복될 수 있어 응답 데이터 설정만하고 실제 timeout middleware 에서 응답을 주도록 한다.
func SetResponse(c *gin.Context, code int, obj any) {
	resp := GinResponseData{
		Status: code,
		Object: obj,
	}
	c.Set(GinResponse, resp)
}

func Response(c *gin.Context) {
	if respVal, exist := c.Get(GinResponse); exist {
		resp, ok := respVal.(GinResponseData)
		if !ok {
			fmt.Println("invalid GinResponseData type")
			return
		}
		c.JSON(resp.Status, resp.Object)
	}
}

func main() {
	fmt.Println("gin server... ")
	fmt.Println(makeServerVersion())
	// gin.SetMode(gin.ReleaseMode)
	// gin.DisableConsoleColor()

	// json log format
	jsonLogFormatter := func(param gin.LogFormatterParams) string {
		if param.Latency > time.Minute {
			param.Latency = param.Latency.Truncate(time.Second)
		}
		p := struct {
			// Request   *http.Request
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
		// param.Request = nil
		out, err := json.Marshal(p)
		if err != nil {
			log.Fatal(err)
		}
		return string(out) + "\n"
	}
	// default(기본 미들웨어가 포함되어 있음) 로 생성하면 기본 로그 포맷터가 추가된 상태이다.
	// router := gin.Default()
	router := gin.New()
	pprof.Register(router, "/debug/pprof")
	router.Use(gin.LoggerWithFormatter(jsonLogFormatter))
	router.Use(gin.Recovery())
	router.Use(CheckReq())
	// router.Use(timeoutMiddleware1())
	router.Use(timeoutMiddleware2())
	router.GET("/ping", func(c *gin.Context) {
		if v, ok := c.Get("key1"); ok {
			fmt.Println("key1:", v)
		}
		if v, ok := c.Get("mydata"); ok {
			// mydata 원래 structure 를 모른다고 가정하고 비슷한 struct 로 담아보자.
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
		// time.Sleep(900 * time.Millisecond)

		SetResponse(c, http.StatusOK, gin.H{
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
	router.GET("/swagger/*any", gin_swagger.WrapHandler(swaggerfiles.Handler))
	_ = router.Run()
}
