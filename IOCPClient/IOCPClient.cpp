////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// IOCP �� �׽�Ʈ�ϱ� ���� Ŭ���̾�Ʈ ���α׷�
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <winsock2.h>

// winsock2.h �� ����ϴ� ���̺귯��
#pragma comment(lib, "ws2_32.lib")

// ���� �ִ� ����
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
	// ���� �ּ� ����(�׽�Ʈ 127.0.0.1 5555)
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(argv[1]);
	sockAddr.sin_port = htons(atoi(argv[2]));
	fprintf(stderr, "ip = %d port = %d\n", ntohl(sockAddr.sin_addr.s_addr), ntohs(sockAddr.sin_port));

	int ret = 0;

	WSADATA wsaData;
	// ���� 2.2 ���� ���
	ret = WSAStartup(MAKEWORD(2, 2), &wsaData); 
	if (ret != 0)
	{
		fprintf(stderr, "WSAStartup() Failed.\n");
		return 1;
	}
	// Overlap IO ������ winsock2 �� socket ����
	//sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);
	// �Ϲ����� BSD socket ����
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		fprintf(stderr, "Invalid Socket.\n");
		return 1;
	}

	// ���ӽõ�
	ret = connect(sock, (LPSOCKADDR)&sockAddr, sizeof(sockAddr));
	if (ret == SOCKET_ERROR)
	{
		fprintf(stderr, "Socket Error\n");
		return 1;
	}
	fprintf(stderr, "Connected...\n");

	while (true)
	{
		// ������
		char buffer[MAX_LEN] = "YoonByoungHoon";
		send(sock, buffer, strlen(buffer), 0);
		fprintf(stderr, "[socket=%d] %s sent\n", sock, buffer);
		
		// �ޱ�
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
