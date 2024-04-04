package main

import (
	"fmt"
	"net/http"
	"strings"

	"github.com/BurntSushi/toml"
	"github.com/gin-gonic/gin"
	"github.com/go-resty/resty/v2"
	"github.com/google/go-github/github"
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
		v1.POST("/webhook", githubWebhook)
	}
}

var buildtime string

func version(gc *gin.Context) {
	gc.JSON(http.StatusOK, buildtime)
}

func githubWebhook(gc *gin.Context) {
	secretKey := []byte{}
	payload, err1 := github.ValidatePayload(gc.Request, secretKey)
	if err1 != nil {
		return
	}
	event, err2 := github.ParseWebHook(github.WebHookType(gc.Request), payload)
	if err2 != nil {
		return
	}
	webhookType := github.WebHookType(gc.Request)
	fmt.Println("github WebHookType:", webhookType)
	switch event := event.(type) {
	case *github.CommitCommentEvent:
		githubCommitCommentEvent(event)
	case *github.PullRequestEvent:
		githubPullRequestEvent(event)
	case *github.PullRequestReviewEvent:
		githubPullRequestReviewEvent(event)
	case *github.PullRequestReviewCommentEvent:
		githubPullRequestReviewCommentEvent(event)
	default:
		fmt.Println("github WebHookType:", webhookType)
	}
}

func githubCommitCommentEvent(event *github.CommitCommentEvent) {
	msg := fmt.Sprintf("[%v] sender:%v comment:%v link:%v",
		event.GetAction(),
		event.Sender.GetName(),
		event.GetComment(),
		event.Comment.HTMLURL)
	sendMessage(msg)
}
func githubPullRequestEvent(event *github.PullRequestEvent) {
	msg := fmt.Sprintf("[%v] sender:%v number:%v link:%v",
		event.GetAction(),
		event.Sender.GetName(),
		event.GetNumber(),
		event.PullRequest.URL)
	sendMessage(msg)
}
func githubPullRequestReviewEvent(event *github.PullRequestReviewEvent) {
	msg := fmt.Sprintf("[%v] sender:%v review:%v link:%v",
		event.GetAction(),
		event.Sender.GetName(),
		event.GetReview().String(),
		event.GetReview().GetHTMLURL())
	sendMessage(msg)
}
func githubPullRequestReviewCommentEvent(event *github.PullRequestReviewCommentEvent) {
	msg := fmt.Sprintf("[%v] sender:%v review:%v link:%v",
		event.GetAction(),
		event.Sender.GetName(),
		event.Comment.String(),
		event.GetComment().GetURL())
	sendMessage(msg)
}
func sendMessage(msg string) {
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
	}
	fmt.Println("resp:", resp)
}
