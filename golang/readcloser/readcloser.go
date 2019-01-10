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
	// 일반 슬라이스에서 할당은 참조고 copy 를 해야지만 복사가 된다.
	// https://blog.golang.org/go-slices-usage-and-internals
	a := []byte{}
	a = append(a, 1, 2, 3, 4, 5)
	fmt.Println("a:", a)
	b := a
	c := a[0:]
	d := make([]byte, 10, 10)
	copy(d, a)
	a[2] = 10
	a[3] = 11
	a[4] = 12
	fmt.Println("a:", a)
	fmt.Println("b:", b)
	fmt.Println("c:", c)
	fmt.Println("d:", d)

	//////////////////////////
	// bytes buffer test
	bb1 := new(bytes.Buffer)
	bb1.WriteString("ysoftman")
	// 값 복사
	// 엄밀히 말하면 bytes.Buffer []buf 는 슬라이스라서 copy 를 쓰지 않으면 복사되지 않고 참조된다.
	// 하지만 Buffer.buf 를 직접 인덱싱할수 없어 bb1 을 조작하더라도 bb1 의 offset 이 변경되는것이지
	// 실제 데이터값 바뀌는것이 아니기 때문에 bb2, bb2 각각의 슬라이스 stuct offset 은 유지되어 영향을 받지 않는다.
	bb2 := bytes.NewBuffer(bb1.Bytes())
	bb3 := bb1.Bytes()

	bb1.Reset()
	fmt.Println("bb1:", bb1.String())
	fmt.Println("bb2:", bb2.String())
	fmt.Println("bb3:", string(bb3))

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
