// ysoftman
// 자신의 ip 주소 얻어오기
#include <stdio.h>
#include <string>

using namespace std;

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

string GetIPAddress()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	PHOSTENT hostinfo;
	char hostname[50];
	char ipaddr[50];
	memset(hostname, 0, sizeof(hostname));
	memset(ipaddr, 0, sizeof(ipaddr));

	int nError = gethostname(hostname, sizeof(hostname));
	if (nError == 0)
	{
		hostinfo = gethostbyname(hostname);
		// ip address 파악
		strcpy(ipaddr, inet_ntoa(*(struct in_addr *)hostinfo->h_addr_list[0]));
	}

	WSACleanup();

	return ipaddr;
}
#endif

int main()
{
#ifdef _WIN32
	string strIP = GetIPAddress();
	printf("ipaddress = %s\n", strIP.c_str());
#endif
	return 0;
}
