package main

import (
	"fmt"
	"os"

	"github.com/BurntSushi/toml"
)

// https://xuri.me/toml-to-go/
type fruits struct {
	Fruits struct {
		Desc  string `toml:"desc"`
		Apple struct {
			Name         string `toml:"name"`
			Weight       int    `toml:"weight"`
			Sugarcontent int    `toml:"sugarcontent"`
		} `toml:"apple"`
		Lemon struct {
			Name         string `toml:"name"`
			Weight       int    `toml:"weight"`
			Sugarcontent int    `toml:"sugarcontent"`
		} `toml:"lemon"`
		Banana struct {
			Name         string `toml:"name"`
			Weight       int    `toml:"weight"`
			Sugarcontent int    `toml:"sugarcontent"`
		} `toml:"banana"`
	} `toml:"fruits"`
}

func parseFruits() {
	var conf fruits
	_, err := toml.DecodeFile("fruits.toml", &conf)
	if err != nil {
		fmt.Printf("can't parse...\n")
		os.Exit(1)
	}
	fmt.Printf("Fruits.Desc:%s\n", conf.Fruits.Desc)
	fmt.Printf("Fruits.Apple.Name:%s\n", conf.Fruits.Apple.Name)
	fmt.Printf("Fruits.Apple.Weight:%d\n", conf.Fruits.Apple.Weight)
	fmt.Printf("Fruits.Apple.Sugarcontent:%d\n", conf.Fruits.Apple.Sugarcontent)
	fmt.Printf("Fruits.Lemon.Name:%s\n", conf.Fruits.Lemon.Name)
	fmt.Printf("Fruits.Lemon.Weight:%d\n", conf.Fruits.Lemon.Weight)
	fmt.Printf("Fruits.Lemon.Sugarcontent:%d\n", conf.Fruits.Lemon.Sugarcontent)
	fmt.Printf("Fruits.Banana.Name:%s\n", conf.Fruits.Banana.Name)
	fmt.Printf("Fruits.Banana.Weight:%d\n", conf.Fruits.Banana.Weight)
	fmt.Printf("Fruits.Banana.Sugarcontent:%d\n", conf.Fruits.Banana.Sugarcontent)
}

type fruitsMapChild struct {
	Desc   string `toml:"desc"`
	Fruits map[string]fruit
}

type fruit struct {
	Name         string
	Weight       int
	Sugarcontent int
	AddInfo      map[string]addInfo
}

type addInfo struct {
	price int
}

func parseFruitsMapChild() {
	var conf fruitsMapChild
	if _, err := toml.DecodeFile("fruits.toml", &conf); err != nil {
		fmt.Printf("can't parse...  %s\n", err)
		return
	}
	fmt.Printf("Fruits.Desc:%s\n", conf.Desc)
	for k, v := range conf.Fruits {
		fmt.Println(k, v)
	}
	fmt.Printf("Fruits[\"apple\"].Name:%s\n", conf.Fruits["apple"].Name)
	fmt.Printf("Fruits[\"apple\"].Weight:%d\n", conf.Fruits["apple"].Weight)
	fmt.Printf("Fruits[\"apple\"].Sugarcontent:%d\n", conf.Fruits["apple"].Sugarcontent)
	fmt.Printf("Fruits[\"lemon\"].Name:%s\n", conf.Fruits["lemon"].Name)
	fmt.Printf("Fruits[\"lemon\"].Weight:%d\n", conf.Fruits["lemon"].Weight)
	fmt.Printf("Fruits[\"lemon\"].Sugarcontent:%d\n", conf.Fruits["lemon"].Sugarcontent)
	fmt.Printf("Fruits[\"banana\"].Name:%s\n", conf.Fruits["banana"].Name)
	fmt.Printf("Fruits[\"banana\"].Weight:%d\n", conf.Fruits["banana"].Weight)
	fmt.Printf("Fruits[\"banana\"].Sugarcontent:%d\n", conf.Fruits["banana"].Sugarcontent)
}
