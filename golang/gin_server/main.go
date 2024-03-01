package main

// swagg init && go run .
import (
	"fmt"
	"gin_server/docs"
	"net/http"
	"time"

	swaggerfiles "github.com/swaggo/files"
	ginSwagger "github.com/swaggo/gin-swagger"

	"github.com/gin-gonic/gin"
)

type ServerVersion struct {
	Name      string `json:"Name"`
	Version   string `json:"Version"`
	BuildTime string `json:"BuildTime"`
}

// @Summary server version
// @Schemes
// @Description get server version
// @Tags v1
// @Accept json
// @Produce json
// @Success 200 {string} server_version
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
	}
	// swag init to generate/update ./docs
	r.GET("/swagger/*any", ginSwagger.WrapHandler(swaggerfiles.Handler))
	r.Run()
}
