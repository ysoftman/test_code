package main

import (
	"errors"
	"log"

	"github.com/dgraph-io/ristretto"
)

type MyCache struct {
	cache     *ristretto.Cache
	cacheKeys map[string][]string
}

var cache *MyCache

func NewCache() *MyCache {
	cc, err := ristretto.NewCache(&ristretto.Config{
		NumCounters: 10_000_000, // 10M, LFU(Least-frequently used), num of access frequency information
		// MaxCost:     1 << 30, // cache total capacity, maximum cost of cache (107374182Bytes=1GiB).
		// MaxCost:     1 << 20 * 10, // (10485760Bytes=10MiB)
		MaxCost:     1 << 20, // (1048576Bytes=1MiB)
		BufferItems: 64,      // number of keys per Get buffer.
		OnEvict: func(item *ristretto.Item) {
			log.Println("[OnEvict]", item)
		},
		OnReject: func(item *ristretto.Item) {
			log.Println("[OnReject]", item)
		},
		// OnExit: func(val interface{}) {
		// 	log.Println("[OnExit]", val)
		// },
	})
	if err != nil {
		panic(err)
	}
	// log.Println(cc.MaxCost())
	ckeys := make(map[string][]string, 0)
	return &MyCache{
		cache:     cc,
		cacheKeys: ckeys,
	}
}

func (cc *MyCache) Set(key, val, tbName string) {
	cc.cache.Set(key, val, 0)
	cc.cache.Wait()
	cc.cacheKeys[tbName] = append(cc.cacheKeys[tbName], key)
	log.Printf("set cache, cacheKeys: %#v\n", cc.cacheKeys[tbName])
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
