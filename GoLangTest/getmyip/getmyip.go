// ysoftman
// ip 파악하기
package main

import (
	"fmt"
	"net"
)

func main() {
	myip := myip()
	fmt.Println("myip :", myip)
}
func myip() string {
	addrs, err := net.InterfaceAddrs()
	if err != nil {
		panic(err)
	}
	// all
	// for i, addr := range addrs {
	// 	fmt.Printf("%d %v\n", i, addr)
	// }

	// only ip4 type
	firstip := ""
	for _, addr := range addrs {
		if ipnet, ok := addr.(*net.IPNet); ok && !ipnet.IP.IsLoopback() {
			if ipnet.IP.To4() != nil {
				// 첫번째 ip 를 사용
				if len(firstip) == 0 {
					firstip = ipnet.IP.String()
				}
				fmt.Println(ipnet.IP.String())
			}
		}
	}
	return firstip
}
