// author : ysoftman
// encoding : utf-8
// title : slack api 테스트

package main

import (
	"fmt"

	"github.com/nlopes/slack"
)

func main() {
	fmt.Println("slack api test")
	// slack token 명시
	// 실제 토큰을 명시해서 github 로 공개되니 slack 에서 보안상 해당 토큰을 disable 처리한다고 메일이 온다.
	slackapi := slack.New("aaaaaaaaa")

	// 그룹파악
	groups, err := slackapi.GetGroups(false)
	if err != nil {
		fmt.Printf("%s\n", err)
		return
	}
	for _, g := range groups {
		fmt.Printf("group_id: %s group_name: %s\n", g.ID, g.Name)
	}
}
