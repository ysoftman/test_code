////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 리눅스(kernel 2.4 이상) EPOLL 기능 사용 클라이언트 테스트
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

const int MAX_LEN = 1024;

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage(example) : TestEPOLLClient 127.0.0.1 9999\n");
		return 0;
	}
	int sock = 0;
	struct sockaddr_in sockAddr;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(argv[1]);
	sockAddr.sin_port = htons(atoi(argv[2]));
	fprintf(stderr, "ip = %d port = %d\n", ntohl(sockAddr.sin_addr.s_addr), ntohs(sockAddr.sin_port));

	int ret = 0;
	// 소켓 생성
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == -1)
	{
		fprintf(stderr, "socket() error\n");
	}
	// 접속시도
	ret = connect(sock, (struct sockaddr *)&sockAddr, sizeof(sockAddr));
	if (ret < 0)
	{
		fprintf(stderr, "connect() error\n");
		return 1;
	}
	fprintf(stderr, "connected...\n");

	while (1)
	{
		// 보내기
		char buffer[MAX_LEN];
		strcpy(buffer, "YoonByoungHoon");
		send(sock, buffer, strlen(buffer), 0);
		fprintf(stderr, "[socket=%d] %s sent\n", sock, buffer);

		// 받기
		memset(buffer, 0, sizeof(char) * MAX_LEN);
		recv(sock, buffer, sizeof(char) * MAX_LEN, 0);
		fprintf(stderr, "[socket=%d] %s received\n", sock, buffer);

		// 초단위
		sleep(1);
	}

	closesocket(sock);
	fprintf(stderr, "closesocket()\n");

	return 0;
}
