package main

import (
	"fmt"
	"log"
	"net/http"
	"strconv"
	"sync"
	"time"

	"github.com/PuerkitoBio/goquery"
)

var fineDustMsg = ""

func main() {
	fineDustMsg = fineDustSearch()
	watchingDust()
}

func watchingDust() {
	var wg sync.WaitGroup
	wg.Add(1)
	go func() {
		defer wg.Done()
		for {
			select {
			case <-time.After(10 * time.Second):
				fineDustMsg = fineDustSearch()
			}
		}
	}()

	wg.Wait()
}

// 다음 검색으로 미세먼지 파악하기
// 현재 지역의 미세먼지 정보는 javascript 로 파싱할 수 없어, 경기 지역만 본다.
func fineDustSearch() string {
	// Request the HTML page.
	res, err := http.Get("https://search.daum.net/search?w=tot&ie=UTF-8&q=%EB%AF%B8%EC%84%B8%EB%A8%BC%EC%A7%80")
	if err != nil {
		log.Fatal(err)
	}
	defer res.Body.Close()
	if res.StatusCode != 200 {
		errmsg := "status code error: (" + strconv.Itoa(res.StatusCode) + ")" + res.Status
		log.Fatal(errmsg)
		return errmsg
	}

	// Load the HTML document
	doc, err := goquery.NewDocumentFromReader(res.Body)
	if err != nil {
		log.Fatal(err)
	}

	// #airPollutionNColl > div.coll_cont > div > div.wrap_whole > div.cont_map.bg_map > div.map_region > ul > li.city_03 > a > span
	titregion := ""
	screenout := ""
	txtstate := ""
	selector := "#airPollutionNColl div.coll_cont div div.wrap_whole div.cont_map.bg_map div.map_region ul  li.city_03 a"
	doc.Find(selector).Each(func(i int, s *goquery.Selection) {
		titregion = s.Find("em.tit_region").Text()
		screenout = s.Find("span.screen_out").Text()
		txtstate = s.Find("span.txt_state").Text()
		// fmt.Printf("%d: %s %s %s\n", i, titregion, screenout, txtstate)
	})
	msg := titregion + "지역 미세먼지는 " + screenout + "(" + txtstate + ")" + " 입니다.\n"
	fmt.Print(msg)
	return msg
}
