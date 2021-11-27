package main

import (
	"errors"
	"log"

	"github.com/dgraph-io/ristretto"
)

type MyCache struct {
	cache     *ristretto.Cache
	cacheKeys []string
}

var cache *MyCache

func NewCache() *MyCache {
	cc, err := ristretto.NewCache(&ristretto.Config{
		NumCounters: 1e7,     // number of keys to track frequency of (10M).
		MaxCost:     1 << 30, // maximum cost of cache (1GB).
		BufferItems: 64,      // number of keys per Get buffer.
	})
	if err != nil {
		panic(err)
	}
	log.Println(cc.MaxCost())
	return &MyCache{
		cache: cc,
	}
}

func (cc *MyCache) Set(key, val string) {
	cc.cache.Set(key, val, 0)
	cc.cache.Wait()
	cc.cacheKeys = append(cc.cacheKeys, key)
	log.Printf("set cache, cacheKeys: %#v\n", cc.cacheKeys)
}

func (cc *MyCache) Get(key string) (interface{}, error) {
	value, found := cc.cache.Get(key)
	if !found {
		err := errors.New("missing cache key => " + key)
		log.Println(err)
		return nil, err
	}
	// fmt.Println(value)
	return value, nil
}

func (cc *MyCache) Del(key string) {
	cc.cache.Del(key)
	log.Printf("cache(%v) is deleted", key)
}
