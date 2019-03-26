// caddy plugin 개발 테스트
// caddy 의 거의 모든 기능(지시자)는 플러그인으로 만들어져 있고 caddy 컴파일시 추가된다.
// 소스에 함께 들어 있는 기본 플러그인들은 /mholt/caddy/caddyhttp 에 있으니 참고
// https://github.com/mholt/caddy/wiki/Extending-Caddy
package ysoftmandirective

import (
	"fmt"

	"github.com/mholt/caddy"
)

func init() {
	// 플러그인에 종류에 따라 그에 맞는 Register 를 사용한다.

	// // register a "generic" plugin, like a directive or middleware
	// caddy.RegisterPlugin("name", myPlugin)

	// // register a plugin that can load the Caddyfile when Caddy starts
	// caddy.RegisterCaddyfileLoader("name", myLoader)

	// // register a plugin that implements an entire server type
	// // for use with Caddy
	// caddy.RegisterServerType("name", myServerType)

	// // register a function that runs when Caddy emits events
	// caddy.RegisterEventHook("eventName", myHookFn)

	// // register a cluster plugin
	// caddy.RegisterClusterPlugin("name", constructorFn)

	// // add a function that wraps listeners for the HTTP server
	// // (it's more common for a directive to call this rather than a standalone plugin)
	// httpserver.AddListenerMiddleware(myListenerMiddleware)

	// 플러그인 이름 및 동작 함수 설정
	caddy.RegisterPlugin("ysoftmandirective", caddy.Plugin{
		ServerType: "http",
		Action:     setup,
	})
}

// 지시자의 값을 처리한다.
func setup(c *caddy.Controller) error {
	for c.Next() { // skip the directive name
		if !c.NextArg() { // expect at least one value
			return c.ArgErr() // otherwise it's an error
		}
		value := c.Val() // use the value
		fmt.Println("ysoftmandirective plugin value : ", value)
	}
	return nil
}
