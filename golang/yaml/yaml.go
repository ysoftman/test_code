// ysoftman
// yaml test
package main

import (
	"fmt"
	"log"

	"gopkg.in/yaml.v2"
)

func main() {
	yamlData := struct {
		AA string `yaml:"aa"`
		BB []int  `yaml:"bb"`
	}{
		AA: "aaaa",
		BB: []int{1, 2, 3, 4, 6},
	}
	mYaml, err := yaml.Marshal(&yamlData)
	if err != nil {
		log.Fatal("err=> ", err)
	}
	fmt.Println(string(mYaml))

	// indent 는 space 를 사용해야 한다.
	// found a tab character that violates indentation
	yamlStr := `
name: ysoftman
aa:
   favorites: ["lemon", "apple", "orange"]
`

	fmt.Println(yamlStr)

	data := make(map[interface{}]interface{})
	if err := yaml.Unmarshal([]byte(yamlStr), &data); err != nil {
		log.Fatal("err => ", err)
	}
}
