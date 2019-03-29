package main

import (
	"fmt"
	"os"

	"github.com/BurntSushi/toml"
)

// https://xuri.me/toml-to-go/
type Songs struct {
	Song []struct {
		Name     string `toml:"name"`
		Duration string `toml:"duration"`
	} `toml:"song"`
}

func parseSongs() {
	var songs Songs
	// 파일로 부터 파싱해서 conf 로 저장하기
	_, err := toml.DecodeFile("songs.toml", &songs)
	if err != nil {
		fmt.Printf("can't parse...\n")
		os.Exit(1)
	}

	fmt.Println("songs")
	for idx, val := range songs.Song {
		fmt.Println(idx, "->", val)
	}
}
