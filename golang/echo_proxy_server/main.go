/*
# echo golang web framework 의 proxy 사용시 upstream 을 ingress domain 을 사용하면 404 not found 응답 이슈가 발생했다.

# echo proxy 사용 예시 참고
# https://echo.labstack.com/cookbook/reverse-proxy/

# 같은 localhost 로 업스트림 설정하면 문제가 없다.
http://localhost:8080 -> http://localhost:8081 (upstream local)

# ingress domain 으로 업스트림을 설정하면 404 응답을 받는다.
http://localhost:8080 -> http://ysoftman.dev:8081 (upstream ingress)
404 Not Found

# nginx pod 에 로그를 보면 다음과 같은 메시지나 기록된다.
# 호스트가 ysoftman.dev 로 되어야 할것 같은데, localhost 로 파악돼 pod 까지 요청이 전달되지 않는다.
Skipping metric for host not being served" host="localhost"

# 해결 방법
# 프록시 설정전 다음과 같이 핸들러를 등록하고 request host 를 ysoftman.dev 로 설정하면 ysoftman.dev 로 부터 200 OK 응답을 받는다.
*/

package main

import (
	"net/http"
	"net/url"

	// ModifyResponse 사용을 위해선 echo v4 가 필요
	"github.com/labstack/echo/v4"
	"github.com/labstack/echo/v4/middleware"
)

func main() {
	url, _ := url.Parse("http://ysoftman.dev:8081")
	e := echo.New()
	g := e.Group("/test")

	// 프록시 설정 전 request host 를 upstream host 로 변경
	g.Use(func(next echo.HandlerFunc) echo.HandlerFunc {
		return func(c echo.Context) error {
			c.Request().Host = url.Host
			return next(c)
		}
	})

	// set proxy upstream
	proxyTargets := []*middleware.ProxyTarget{
		{
			URL: url,
		},
	}
	g.Use(middleware.ProxyWithConfig(middleware.ProxyConfig{
		Balancer: middleware.NewRoundRobinBalancer(proxyTargets),
		ModifyResponse: func(resp *http.Response) error {
			return nil
		},
	}))
}
