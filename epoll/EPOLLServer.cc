/*
////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ������(kernel 2.4 �̻�) EPOLL ��� ��� ���� �׽�Ʈ
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

const int MAX_LEN = 1024;
const int EPOLL_SIZE = 10;

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage(example) : TestEPOLLServer 127.0.0.1 9999\n");
		return 0;
	}
	// EPOLL_SIZE ��ŭ �̺�Ʈ ũ�� �����
	struct epoll_event *pEvents;
	pEvents = (struct epoll_event*)malloc(sizeof(*pEvents)*EPOLL_SIZE);
	// epoll FileDescriptor ����
	int fdEpoll = epoll_create(50);
	if (fdEpoll < 0)
	{
		fprintf(stderr, "epoll_create() error\n");
		return 1;
	}

	int sockServer = 0;
	struct sockaddr_in sockAddr;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(argv[1]);
	sockAddr.sin_port = htons(atoi(argv[2]));
	fprintf(stderr, "ip = %d port = %d\n", ntohl(sockAddr.sin_addr.s_addr), ntohs(sockAddr.sin_port));
	
	// ���� ����
	sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockServer == -1)
	{
		fprintf(stderr, "socket() error\n");
		return 1;
	}
	fprintf(stderr, "socket() ok\n");

	int ret = 0;
	// ���ε�
	ret = bind(sockServer, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
	if (ret == -1)
	{
		fprintf(stderr, "bind() error\n");
		return 1;
	}
	fprintf(stderr, "bind() ok\n");
	// ����
	ret = listen(sockServer, 5);
	if (ret == -1)
	{
		fprintf(stderr, "listen() error\n");
		return 1;
	}
	fprintf(stderr, "listen() ok\n");

	// EPOLLIN(�б�) �̺�Ʈ�� ����
	pEvents->events = EPOLLIN;
	// ó�� �����ʹ� ��� ������ ������������ ����
	pEvents->data.fd = sockServer;
	// ���������� ���� ����(sockServer)�� epoll �̺�Ʈ Ǯ�� �߰��ñ�� ����� pEvents �� �����Ѵ�.
	epoll_ctl(fdEpoll, EPOLL_CTL_ADD, sockServer, pEvents);
	int i = 0;
	int NumOfEvents = 0;
	char buffer[MAX_LEN];
	while (1)
	{
		fprintf(stderr, "epoll_wait() ...\n");
		// epoll �̺�Ʈ Ǯ���� �̺�Ʈ�� �Ͼ������ ��ٸ���.
		NumOfEvents = epoll_wait(fdEpoll, pEvents, EPOLL_SIZE, -1);
		fprintf(stderr, "events occur!\n");
		if (NumOfEvents == -1)
		{
			fprintf(stderr, "epoll_wait() error\n");
		}
		// �߻��� �̺�Ʈ ��ŭ ������ ���鼭 ó���Ѵ�.
		for (i=0; i<NumOfEvents; i++)
		{
			// ��� ������ ���� ���Ͽ��� �̺�Ʈ�� �߻��ϸ�
			if (pEvents[i].data.fd == sockServer)
			{
				// accpet �ϰ� Ŭ���̾�Ʈ�� ���� ������ �����.
				int sockClient = 0;
				struct sockaddr_in sockClientAddr;
				int szClient = sizeof(sockClientAddr);
				sockClient = accept(sockServer, (struct sockaddr*)&sockClientAddr, &szClient);
				fprintf(stderr, "accept()\n");
				// �б� �̺�Ʈ�� �߻��ߴٰ� �����Ѵ�.
				pEvents->events = EPOLLIN;
				// �б� �̺�Ʈ�� filedescriptor �� sockClient�� �����Ѵ�.
				pEvents->data.fd = sockClient;
				// sockClient �� epoll �̺�Ʈ Ǯ�� �߰���Ų��.
				epoll_ctl(fdEpoll, EPOLL_CTL_ADD, sockClient, pEvents);
			}
			// ��������� Ŭ���̾�Ʈ ���Ͽ��� �̺�Ʈ�� �߻��ϸ�
			else
			{
				memset(buffer, 0, sizeof(char)*MAX_LEN);
				// ������Ͽ��� ���۷� ������ �о� ����
				int n = read(pEvents[i].data.fd, buffer, MAX_LEN);
				// �о�� �����Ͱ� ������
				if (n <= 0)
				{
					// epoll Ǯ���� ���� ������ �����ϰ�
					epoll_ctl(fdEpoll, EPOLL_CTL_DEL, pEvents[i].data.fd, pEvents);
					// ���� ������ �ݴ´�.
					close(pEvents[i].data.fd);
					fprintf(stderr, "close socket(%d)\n", pEvents[i].data.fd);
				}
				// �о�� �����Ͱ� ������
				else
				{
					// ����ϰ�
					fprintf(stderr, "[socket=%d] %s received\n", pEvents[i].data.fd, buffer);
					// �����͸� ������.
					memset(buffer, 0, sizeof(char)*MAX_LEN);
					strcpy(buffer, "ysoftman");
					send(pEvents[i].data.fd, buffer, sizeof(char)*MAX_LEN, 0);
					fprintf(stderr, "[socket=%d] %s sent\n", pEvents[i].data.fd, buffer);
				}
			}
		}
	}
	free(pEvents);
	closesocket(sockServer);
	close(fdEpoll);
	return 0;
}
//*/
