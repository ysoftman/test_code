// author : ysoftman
// encoding : utf-8
// title : chat server

package main

import (
	"fmt"
	"os"
	"net"
)

const (
	default_ip   string = "127.0.0.1"
	default_port string = "33333"
)

func main() {
	fmt.Println("Chat Server...")

	server_ip := ""
	server_port := ""
	if len(os.Args) == 3 {
		server_ip = os.Args[1]
		server_port = os.Args[2]
	} else {
		server_ip = default_ip
		server_port = default_port
	}

	fmt.Println(server_ip + ":" + server_port + " 로 서버를 생성합니다.")

	// tcp addr 생성
	tcpaddr, err := net.ResolveTCPAddr("tcp", server_ip+":"+server_port)
	if err != nil {
		fmt.Fprintln(os.Stderr, "[Error] "+err.Error())
		os.Exit(-1)
	}
	fmt.Println("Chat Server Address(TCP) created.")

	// tcp 리스너 생성
	listener, err := net.ListenTCP("tcp", tcpaddr)
	if err != nil {
		fmt.Fprintln(os.Stderr, "[Error] "+err.Error())
		os.Exit(-1)
	}
	fmt.Println("Chat Server Listener(TCP) created.")

	// 리스닝...
	for {
		con, err := listener.Accept()
		if err != nil {
			fmt.Fprintln(os.Stderr, "Error "+err.Error())
			continue
		}

		// 클라이언트 요청당 별도의 쓰레드로 처리
		go dispatcher_client_request(con)

	}

	listener.Close()

	fmt.Println("Chat Server Listener Closed...")
}

// 클라이언트 패킷 디스패처
func dispatcher_client_request(con net.Conn) {
	fmt.Println("dispatcher_client_request")

	// 함수 리턴될때 close 될 수 있도록 defer 사용
	defer con.Close()

	buffer := make([]byte, 1000)
	for {
		cnt, err := con.Read(buffer)
		if err != nil {
			return
		}
		// 클라 메시지 출력
		fmt.Printf("[client message %d read] %s\n", cnt, string(buffer[:cnt]))

	}
	// 클라에 응답 보내기
	con.Write([]byte("Server Response"))
}
