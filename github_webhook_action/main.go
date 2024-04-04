package main

import (
	"fmt"
	"net/http"
	"strings"

	"github.com/BurntSushi/toml"
	"github.com/gin-gonic/gin"
	"github.com/go-resty/resty/v2"
)

type configTOML struct {
	Name   string `toml:"Name"`
	Server struct {
		Port int `toml:"Port"`
	} `toml:"server"`
	Action struct {
		API struct {
			URL         string `toml:"URL"`
			Auth        string `toml:"Auth"`
			Mothod      string `toml:"Mothod"`
			RequestBody string `toml:"RequestBody"`
		} `toml:"api"`
	} `toml:"action"`
}

var conf configTOML

func main() {
	fmt.Println("github_webhook_action")
	toml.DecodeFile("config.toml", &conf)
	r := gin.New()
	router(r)
	r.Run(fmt.Sprintf(":%v", conf.Server.Port))
}

func router(ge *gin.Engine) {
	v1 := ge.Group("/v1")
	{
		v1.GET("/version", version)
		v1.POST("/webhook", githubWehook)
	}
}

var buildtime string

func version(gc *gin.Context) {
	gc.JSON(http.StatusOK, buildtime)
}

func githubWehook(gc *gin.Context) {
	client := resty.New()
	reqBody := struct {
		Field1 string
	}{
		"aaa",
	}
	req := client.R().SetHeader("Accept", "application/json").SetQueryParams(map[string]string{
		"param1": "apple",
		"param2": "lemon",
	}).SetBody(&reqBody).SetAuthToken(conf.Action.API.Auth)
	var resp *resty.Response
	var err error
	if strings.ToLower(conf.Action.API.Mothod) == "post" {
		resp, err = req.Post(conf.Action.API.URL)
	} else if strings.ToLower(conf.Action.API.Mothod) == "get" {
		resp, err = req.Get(conf.Action.API.URL)
	}
	if err != nil {
		fmt.Println(err.Error())
		gc.JSON(http.StatusInternalServerError, nil)
	}
	fmt.Println("resp:", resp)
	gc.JSON(http.StatusOK, nil)
}
