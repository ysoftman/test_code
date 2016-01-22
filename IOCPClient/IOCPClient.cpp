////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// IOCP 를 테스트하기 위한 클라이언트 프로그램
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <winsock2.h>

// winsock2.h 가 사용하는 라이브러리
#pragma comment(lib, "ws2_32.lib")

// 버퍼 최대 길이
const int MAX_LEN = 1024;

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage : %s IP PORT\n", argv[0]);
		return 1;
	}
	
	SOCKET sock = INVALID_SOCKET;
	SOCKADDR_IN sockAddr;
	// 서버 주소 설정(테스트 127.0.0.1 5555)
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(argv[1]);
	sockAddr.sin_port = htons(atoi(argv[2]));
	fprintf(stderr, "ip = %d port = %d\n", ntohl(sockAddr.sin_addr.s_addr), ntohs(sockAddr.sin_port));

	int ret = 0;

	WSADATA wsaData;
	// 윈속 2.2 버전 사용
	ret = WSAStartup(MAKEWORD(2, 2), &wsaData); 
	if (ret != 0)
	{
		fprintf(stderr, "WSAStartup() Failed.\n");
		return 1;
	}
	// Overlap IO 가능한 winsock2 로 socket 생성
	//sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);
	// 일반적인 BSD socket 생성
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		fprintf(stderr, "Invalid Socket.\n");
		return 1;
	}

	// 접속시도
	ret = connect(sock, (LPSOCKADDR)&sockAddr, sizeof(sockAddr));
	if (ret == SOCKET_ERROR)
	{
		fprintf(stderr, "Socket Error\n");
		return 1;
	}
	fprintf(stderr, "Connected...\n");

	while (true)
	{
		// 보내기
		char buffer[MAX_LEN] = "YoonByoungHoon";
		send(sock, buffer, strlen(buffer), 0);
		fprintf(stderr, "[socket=%d] %s sent\n", sock, buffer);
		
		// 받기
		memset(buffer, 0, sizeof(char)*MAX_LEN);
		recv(sock, buffer, sizeof(char)*MAX_LEN, 0);
		fprintf(stderr, "[socket=%d] %s received\n", sock, buffer);
		
		Sleep(1000);
	}

	closesocket(sock);
	fprintf(stderr, "closesocket()\n");
	WSACleanup();
	fprintf(stderr, "WSACleanup()\n");
}
