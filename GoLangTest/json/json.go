// author : ysoftman
// encoding : utf-8
// title : json 테스트
package main

import "encoding/json"
import "fmt"

const strJson = `
{
"name":"ysoftman", 
"age":20,
"history" : 
			{"date":"20141010", "action":"dosomething"}
}
`

type JSON_DATA_INNTER struct {
	Date   string
	Action string
}

type JSON_DATA struct {

	//Name	string	// json 키값과 같은 이름의 변수를 선언하던가
	UserName string `json:"name"` // json key tag 를 명시하던가
	Age      int
	History  JSON_DATA_INNTER
}

func main() {
	fmt.Println("json test...")

	// bool 형 json 만들기
	json1, _ := json.Marshal(true)
	fmt.Println("json1 = ", string(json1))

	// int 형 json 만들기
	json2, _ := json.Marshal(123)
	fmt.Println("json2 = ", string(json2))

	// string 형 json 만들기
	json3, _ := json.Marshal("ysoftman")
	fmt.Println("json3 = ", string(json3))

	// 배열 json 만들기
	array := []string{"red", "green", "blue"}
	json4, _ := json.Marshal(array)
	fmt.Println("json4 = ", string(json4))

	// 맵 json 만들기
	obj := map[string]string{"name1": "ysoftman", "name2": "hong gil-dong"}
	json5, _ := json.Marshal(obj)
	fmt.Println("json5 = ", string(json5))

	// json 파싱
	json_data := &JSON_DATA{}
	json.Unmarshal([]byte(strJson), &json_data)
	fmt.Println("strJson = ", json_data)
	fmt.Println("strJson = ", json_data.UserName)
	fmt.Println("strJson = ", json_data.Age)
	fmt.Println("strJson = ", json_data.History.Date)
	fmt.Println("strJson = ", json_data.History.Action)
}
