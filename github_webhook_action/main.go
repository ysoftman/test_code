package main

import (
	"flag"
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"strings"

	"github.com/BurntSushi/toml"
	"github.com/gin-gonic/gin"
	"github.com/go-resty/resty/v2"
	"github.com/google/go-github/github"
	"github.com/rs/zerolog"
	"google.golang.org/appengine/v2"
	appenginelog "google.golang.org/appengine/v2/log"
)

type configTOML struct {
	Name   string `toml:"Name"`
	Server struct {
		Port             int    `toml:"Port"`
		LogLevel         string `toml:"LogLevel"`
		LogIsJsonFormat  bool   `toml:"LogIsJsonFormat"`
		WebhookSecretKey string `toml:"WebhookSecretKey"`
	} `toml:"server"`
	Action struct {
		API struct {
			Enable      bool   `toml:"Enable"`
			URL         string `toml:"URL"`
			Auth        string `toml:"Auth"`
			Mothod      string `toml:"Mothod"`
			RequestBody string `toml:"RequestBody"`
		} `toml:"api"`
	} `toml:"action"`
}

var buildtime string
var conf configTOML
var logger zerolog.Logger

func CreateLogger(logLevelString string, isJson bool) {
	logLevel, _ := zerolog.ParseLevel(logLevelString)
	var writer io.Writer
	if isJson {
		writer = os.Stdout
	} else {
		writer = zerolog.ConsoleWriter{Out: os.Stdout}
	}
	logger = zerolog.New(writer).With().Timestamp().Logger().Level(logLevel)
}
func main() {
	serverType := flag.String("servertype", "gae", "noraml|gae(google app engin)")
	flag.Parse()
	log.Println("servertype :", *serverType)
	toml.DecodeFile("config.toml", &conf)
	CreateLogger(conf.Server.LogLevel, conf.Server.LogIsJsonFormat)
	logger.Info().Msg("github_webhook_action")
	if *serverType == "normal" {
		// 일반 서버 환경으로 운영시
		r := gin.New()
		v1 := r.Group("/v1")
		{
			v1.GET("/version", ginHandlerVersion)
			v1.POST("/webhook", ginHandlerGithubWebhook)
		}
		r.Run(fmt.Sprintf(":%v", conf.Server.Port))
	} else if *serverType == "gae" {
		// GAE(google app engine) 환경으로 운영시
		http.HandleFunc("/", handlerIndex)
		http.HandleFunc("/v1/version", handlerVersion)
		http.HandleFunc("/v1/webhook", handlerWebhook)
		appengine.Main()
	}
}

func handlerIndex(w http.ResponseWriter, r *http.Request) {
	ctx := appengine.NewContext(r)
	appenginelog.Infof(ctx, "/ 요청 처리")
	out := `
# github webhook action
github webhook 을 받아 필요한 액션을 테스트하는 하는 서버입니다.

# app engine 으로 운영
https://github-webhook-action.appspot.com/v1/webhook/

# github
https://github.com/ysoftman/test_code/tree/master/github_webhook_action
`
	fmt.Fprintln(w, out)
}
func handlerVersion(w http.ResponseWriter, r *http.Request) {
	ctx := appengine.NewContext(r)
	appenginelog.Infof(ctx, "/version 요청 처리")
	fmt.Fprintln(w, buildtime)
}
func handlerWebhook(w http.ResponseWriter, r *http.Request) {
	ctx := appengine.NewContext(r)
	appenginelog.Infof(ctx, "/webhook 요청 처리")
	githubWebhook(r)
}

func ginHandlerVersion(gc *gin.Context) {
	logger.Info().Str("handler", "ginHandlerVersion").Msg("requst")
	gc.JSON(http.StatusOK, buildtime)
}
func ginHandlerGithubWebhook(gc *gin.Context) {
	logger.Info().Str("handler", "ginHandlerGithubWebhook").Msg("requst")
	githubWebhook(gc.Request)
}

func githubWebhook(req *http.Request) {
	payload, err1 := github.ValidatePayload(req, []byte(conf.Server.WebhookSecretKey))
	if err1 != nil {
		logger.Error().Err(err1).Msg("failed ValidatePayload")
		return
	}
	event, err2 := github.ParseWebHook(github.WebHookType(req), payload)
	if err2 != nil {
		logger.Error().Err(err2).Msg("failed ParseWebHook")
		return
	}
	webhookType := github.WebHookType(req)
	logger.Info().Msgf("github WebHookType:%v", webhookType)
	switch event := event.(type) {
	case *github.CommitCommentEvent:
		githubCommitCommentEvent(event)
	case *github.PushEvent:
		githubPushEvent(event)
	case *github.PullRequestEvent:
		githubPullRequestEvent(event)
	case *github.PullRequestReviewEvent:
		githubPullRequestReviewEvent(event)
	case *github.PullRequestReviewCommentEvent:
		githubPullRequestReviewCommentEvent(event)
	default:
		logger.Info().Msgf("github WebHookType:%v", webhookType)
	}
}
func githubCommitCommentEvent(event *github.CommitCommentEvent) {
	msg := fmt.Sprintf("[CommitComment-%v] sender:%v comment:%v link:%v",
		event.GetAction(),
		event.Sender.GetName(),
		event.GetComment(),
		event.Comment.HTMLURL)
	sendMessage(msg)
}
func githubPushEvent(event *github.PushEvent) {
	msg := fmt.Sprintf("[Push-%v] sender:%v pusher:%v link:%v",
		*event.HeadCommit.Message,
		event.Sender.GetName(),
		event.Pusher.GetName(),
		event.Repo.GetHTMLURL())
	sendMessage(msg)
}
func githubPullRequestEvent(event *github.PullRequestEvent) {
	msg := fmt.Sprintf("[PullRequest-%v] sender:%v number:%v link:%v",
		event.GetAction(),
		event.Sender.GetName(),
		event.GetNumber(),
		*event.PullRequest.HTMLURL)
	sendMessage(msg)
}
func githubPullRequestReviewEvent(event *github.PullRequestReviewEvent) {
	msg := fmt.Sprintf("[PullRequestReview-%v] sender:%v review:%v link:%v",
		event.GetAction(),
		event.Sender.GetName(),
		event.GetReview().String(),
		event.GetReview().GetHTMLURL())
	sendMessage(msg)
}
func githubPullRequestReviewCommentEvent(event *github.PullRequestReviewCommentEvent) {
	msg := fmt.Sprintf("[PullRequestReviewComment-%v] sender:%v comment:%v link:%v",
		event.GetAction(),
		event.Sender.GetName(),
		event.Comment.String(),
		event.GetComment().GetURL())
	sendMessage(msg)
}
func sendMessage(msg string) {
	logger.Info().Msgf("msg:%v", msg)
	if !conf.Action.API.Enable {
		logger.Info().Msg("action api disabled")
		return
	}
	client := resty.New()
	reqBody := struct {
		Field1  string
		Message string
	}{
		"aaa",
		msg,
	}
	req := client.R().SetHeader("Accept", "application/json").SetBody(&reqBody).SetAuthToken(conf.Action.API.Auth)
	var resp *resty.Response
	var err error
	if strings.ToLower(conf.Action.API.Mothod) == "post" {
		resp, err = req.Post(conf.Action.API.URL)
	} else if strings.ToLower(conf.Action.API.Mothod) == "get" {
		resp, err = req.SetQueryParams(map[string]string{
			"param1": "apple",
			"param2": "lemon"}).Get(conf.Action.API.URL)
	}
	if err != nil {
		logger.Info().Msg(err.Error())
	}
	logger.Info().Msgf("resp:%v", resp)
}
