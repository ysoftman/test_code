// author : ysoftman
// encoding : utf-8
// title : chat client
package main

import (
	"fmt"
	"os"
	"net"
)

func main() {
	serveraddr := ""
	if len(os.Args) == 2 {
		serveraddr = os.Args[2]
	} else {
		serveraddr = "127.0.0.1:33333"
	}

	// 서버로 접속 시도
	con, err := net.Dial("tcp", serveraddr)
	if err != nil {
		fmt.Fprintln(os.Stderr, "[Error] "+err.Error())
		os.Exit(-1)
	}
	fmt.Println(serveraddr + " 로 접속...")

	addr := con.LocalAddr()
	fmt.Println(addr.Network())

	// 함수 리턴될때 close 될 수 있도록 defer 사용
	defer con.Close()

	// buffer := []byte("")
	buffer := make([]byte, 1024)
	for {
		go Receive(con)

		fmt.Scanf("%s\n", &buffer)

		//_, err = con.Write([]byte("aaa"))
		_, err = con.Write(buffer)
		fmt.Println("send to server.")
		if err != nil {
			fmt.Fprintln(os.Stderr, "[Error] "+err.Error())
			os.Exit(-1)
		}

		// 종료
		if string(buffer) == "quit" {
			break
		}
	}
}

// 메시지 받기
func Receive(con net.Conn) {
	buffer := make([]byte, 1024)
	cnt, _ := con.Read(buffer)
	if cnt > 0 {
		fmt.Println("[Receive] " + string(buffer[:cnt]))
	}
}
