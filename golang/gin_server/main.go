package main

// swagg init && go run .
import (
	"encoding/json"
	"fmt"
	"gin_server/docs"
	"io"
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
	r := gin.Default()
	r.GET("/ping", func(c *gin.Context) {
		c.JSON(http.StatusOK, gin.H{
			"message": "pong",
		})
	})
	docs.SwaggerInfo.BasePath = "/api/v1"
	v1 := r.Group("/api/v1")
	{
		v1.GET("/version", GetServerVersion)
		v1.POST("/data1", PostData)
	}
	// swag init to generate/update ./docs
	r.GET("/swagger/*any", ginSwagger.WrapHandler(swaggerfiles.Handler))
	r.Run()
}
