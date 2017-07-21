// ysoftman
// go chart test
// go get "github.com/wcharczuk/go-chart"
package main

import (
	"bytes"
	"fmt"
	"log"
	"net/http"

	"os"

	"github.com/wcharczuk/go-chart"
)

func drawChart(res http.ResponseWriter, req *http.Request) {
	pie := chart.PieChart{
		Width:  512,
		Height: 512,
		Values: []chart.Value{
			{Value: 5, Label: "Blue"},
			{Value: 5, Label: "Green"},
			{Value: 4, Label: "Gray"},
			{Value: 4, Label: "Orange"},
			{Value: 3, Label: "Deep Blue"},
			{Value: 3, Label: "??"},
			{Value: 1, Label: "!!"},
		},
	}

	res.Header().Set("Content-Type", "image/png")
	err := pie.Render(chart.PNG, res)
	if err != nil {
		fmt.Printf("Error rendering pie chart: %v\n", err)
	}

	// 파일로도 만들기 만들기
	buffer := bytes.NewBuffer([]byte{})
	err = pie.Render(chart.PNG, buffer)
	if err != nil {
		log.Fatal(err)
	}
	fo, err := os.Create("output.png")
	if err != nil {
		panic(err)
	}
	if _, err := fo.Write(buffer.Bytes()); err != nil {
		panic(err)
	}
}

func main() {
	http.HandleFunc("/", drawChart)
	log.Fatal(http.ListenAndServe(":8080", nil))
}
