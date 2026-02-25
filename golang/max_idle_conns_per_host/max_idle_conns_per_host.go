// ysoftman
// time_wait 제거 테스트
package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"time"
)

var (
	targetServer = "http://localhost:55555"
	myClient     *http.Client
)

func init() {
	// http transport.go 에서는
	// MaxIdleConns = 100
	// MaxIdleConnsPerHost = 2
	// 으로 기본 설정되어 100개의 idle 연결 사용할 수 있지만
	// 호스트 1개당 idle 연결 재사용은 2개로 제한된다.
	// 그래서 호스트 1개에 여러개의 요청을 보내야 하는 경우
	// 비효율적으로 time_wait 상태의 소켓들을 사용할 수 없다.
	// 위 설정을 변경하기 위해서 커스텀 Transport 를 만들어야 된다.
	// 커스텀 Transport 는 재사용되니 최초 한번만 설정해야 한다.
	defaultTransportPointer, ok := http.DefaultTransport.(*http.Transport)
	if !ok {
		panic("[error] http.DefaultTransport != *http.Transport")
	}
	defaultTransport := *defaultTransportPointer
	defaultTransport.MaxIdleConns = 100
	defaultTransport.MaxIdleConnsPerHost = 100
	myClient = &http.Client{Transport: &defaultTransport, Timeout: 1000 * time.Millisecond}
}

func main() {
	if len(os.Args) > 1 {
		fmt.Println("os.Args[1]:", os.Args[1])
		targetServer = os.Args[1]
	}
	go startWebServer()

	// 웹서버에 부하를 줘서 time_wait(서버의 접속 끊김 ack를 기다리는 상태) 를 만든다.
	// Linux 환경에서 모니터링
	// watch -n 1 'netstat -nato | grep -i time_wait'
	// 윈도우 WSL(Windows Subsystem for Linux) 환경에서 모니터링
	// watch -n 1 '/mnt/c/Windows/System32/NETSTAT.EXE -nato | grep -i time_wait'
	for i := 0; i < 10; i++ {
		// 기본 Client 사용시 time_wait 상태가 줄어들지 않고 새로 생성되는 것을 알 수 있다.
		// go startClientReq(i)

		// myClient(커스텀 클라이언트)를 사용하면 time_wait 재사용되어 사라진다.
		// 프로그램이 끝나면 10개는 time_wait 로 되어 있는건 프로그램이 끝나서 서버 응답을 못받아 time_wait 상태로가 유지되고, 60초(커널에 하드코딩된 time_wait 만료시간) 후 사라진다.
		go startCustomClientReq(i)
	}

	time.Sleep(10 * time.Second)
}

var receiveCnt int

func startWebServer() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		time.Sleep(100 * time.Millisecond)
		w.WriteHeader(http.StatusOK)
		_, err := w.Write([]byte("hahaha~"))
		if err == nil {
			receiveCnt++
			fmt.Println("Server (", receiveCnt, ") RequestURI : ", r.RequestURI)
		}
	})
	http.ListenAndServe(":55555", nil)
}

func startClientReq(jobNum int) {
	reqCnt := 0
	for {
		resp, err := http.Get(targetServer)
		if err != nil {
			log.Println(err.Error())
			panic(err.Error())
		}
		reqCnt++
		var bodyBytes []byte
		bodyBytes, err = io.ReadAll(resp.Body)
		if err == nil {
			fmt.Println("Client (", jobNum, "-", reqCnt, ")", string(bodyBytes))
		}
		// resp.Body 는 다음 http 연결(소켓)에 재사용되기 때문에 devNull 로 만들어야 한다.
		io.Copy(io.Discard, resp.Body)
		resp.Body.Close()
	}
}

func startCustomClientReq(jobNum int) {
	reqCnt := 0

	for {
		resp, err := myClient.Get(targetServer)
		if err != nil {
			log.Println(err.Error())
			panic(err.Error())
		}
		reqCnt++
		var bodyBytes []byte
		bodyBytes, err = io.ReadAll(resp.Body)
		if err == nil {
			fmt.Println("Client (", jobNum, "-", reqCnt, ")", string(bodyBytes))
		}
		// resp.Body 는 다음 http 연결(소켓)에 재사용되기 때문에 devNull 로 만들어야 한다.
		io.Copy(io.Discard, resp.Body)
		resp.Body.Close()
	}
}
