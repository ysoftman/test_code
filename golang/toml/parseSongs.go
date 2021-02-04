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
	// 파일로 부터 파싱
	_, err := toml.DecodeFile("./config/songs.toml", &songs)
	if err != nil {
		fmt.Printf("can't parse...\n")
		os.Exit(1)
	}

	fmt.Println("songs")
	for idx, val := range songs.Song {
		fmt.Println(idx, "->", val)
	}
}
