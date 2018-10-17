// ysoftman
// ip 파악하기
package main

import (
	"fmt"
	"net"
)

func main() {
	fmt.Println("-- local ip --")
	myip := myip()
	fmt.Println("myip :", myip)
	fmt.Println()
	fmt.Println("-- dns lookup --")
	dnsLookup("google.com")
	dnsLookup("naver.com")
	dnsLookup("210.89.164.90")
	dnsLookup("daum.com")
	fmt.Println()
	fmt.Println("--- split host port")
	ipstr := "10.10.10.10:9999"
	host, _ := splitHostPort(ipstr)
	checkIPVersion(host)
	ipstr = "[10:10:10::1]:9999"
	host, _ = splitHostPort(ipstr)
	checkIPVersion(host)
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

func dnsLookup(dns string) {
	fmt.Println("dns:", dns)
	ips, err := net.LookupIP(dns)
	if err != nil {
		fmt.Printf("LookupIP Error : %v\n", err)
		return
	}
	for _, ip := range ips {
		fmt.Println(ip)
	}
}

func checkIPVersion(ipstr string) string {
	addr, err := net.ResolveIPAddr("ip", ipstr)
	if err != nil {
		fmt.Println(err)
		return ""
	}
	ipversion := "unknown"
	if addr.IP.To4() != nil {
		ipversion = "IPv4"
	} else if addr.IP.To16() != nil {
		ipversion = "IPv6"
	}
	fmt.Println(ipversion)
	return ipversion
}

func splitHostPort(ipstr string) (host, port string) {
	fmt.Println(ipstr)
	host, port, err := net.SplitHostPort(ipstr)
	if err != nil {
		fmt.Println(err)
		return "", ""
	}
	fmt.Println(host)
	fmt.Println(port)

	return host, port
}
