// ysoftman
// readcloser test
package main

import (
	"bytes"
	"fmt"
	"io"
	"io/ioutil"
)

func main() {
	//////////////////////////
	// bytes buffer test
	bb1 := new(bytes.Buffer)
	bb1.WriteString("ysoftman")
	// 값 복사
	bb2 := bytes.NewBuffer(bb1.Bytes())

	fmt.Println("bb1:", bb1.String())
	fmt.Println("bb2:", bb2.String())

	//////////////////////////
	// readcloser 생성 및 사용
	var rc io.ReadCloser
	rc = ioutil.NopCloser(bytes.NewBuffer(bb1.Bytes()))
	numOfBytes, err0 := rc.Read(bb1.Bytes())
	if err0 == nil {
		fmt.Println("bb1:", bb1.String(), " rc.read() numofBytes", numOfBytes)
	}
	rc.Close()

	//////////////////////////
	// io.ReadCloser 생성 (NopCloser 는 close() 처리시 nil 리턴하게 된다.)
	aa1 := ioutil.NopCloser(bytes.NewBuffer(bb1.Bytes()))

	// readadll 하면 read 시 offset 이 EOF 로 이동되어 aa 의 내용을 읽을 수 없게 된다.
	bytes1, err1 := ioutil.ReadAll(aa1)
	if err1 == nil {
		fmt.Println("aa1:", string(bytes1))
	}
	// 위에서 aa 는 close() 되서 내용이 삭제된 상태다.
	bytes2, err2 := ioutil.ReadAll(aa1)
	if err2 == nil {
		fmt.Println("aa1:", string(bytes2))
	}
	// bytes 로 새로 새로 만들어야 한다.
	aa2 := ioutil.NopCloser(bytes.NewBuffer(bytes1))
	bytes3, err3 := ioutil.ReadAll(aa2)
	if err3 == nil {
		fmt.Println("aa2:", string(bytes3))
	}

}
