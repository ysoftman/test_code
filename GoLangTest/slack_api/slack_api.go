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
	slackapi := slack.New("xoxp-3061993574-55243284818-92053298579-c89480262eead7a26906ef3eb38befda")

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
