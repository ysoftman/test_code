package main

// swagg init && go run .
import (
	"encoding/json"
	"fmt"
	"gin_server/docs"
	"io"
	"log"
	"net/http"
	"time"

	"github.com/gin-gonic/gin"
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
	// default 로 생성하면 기본 로그 포맷터가 추가된 상태이다.
	//router := gin.Default()
	router := gin.New()
	router.Use(gin.LoggerWithFormatter(jsonLogFormatter))
	router.Use(gin.Recovery())
	router.GET("/ping", func(c *gin.Context) {
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
