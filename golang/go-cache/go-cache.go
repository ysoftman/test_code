// ysoftman
// go-cache test
// go get -u "github.com/patrickmn/go-cache"
package main

import (
	"time"
	cache "github.com/patrickmn/go-cache"
	"fmt"
)

var gocache *cache.Cache

func main() {
	// 캐시 데이터 유지 기간
	defaultExpiration := time.Second * 3
	// 캐시 데이터 전체 클린업 체크 간격
	cleanupInterval := time.Minute * 10
	gocache = cache.New(defaultExpiration, cleanupInterval)

	key := "key1"
	value := "ysoftman_data"
	setCache(key, value, defaultExpiration)
	getCache(key)
	getCache(key)

	fmt.Println("wait for ", defaultExpiration, " sec")
	time.Sleep(defaultExpiration)
	// 3 초후면 캐시 데이터 만료
	getCache(key)
}

func setCache(key, value string, expiration time.Duration) {
	gocache.Set(key, value, expiration)
	fmt.Println("go-cache set (", key, ",", value, ")")
}

func getCache(key string) string {
	out, found := gocache.Get(key)
	if found {
		fmt.Println("go-cache get (", key, ") = ", out)
		return out.(string)
	}
	fmt.Println("not found (", key, ") data")
	return ""
}
