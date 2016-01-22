/*
////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 리눅스(kernel 2.4 이상) EPOLL 기능 사용 서버 테스트
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
	// EPOLL_SIZE 만큼 이벤트 크기 만들기
	struct epoll_event *pEvents;
	pEvents = (struct epoll_event*)malloc(sizeof(*pEvents)*EPOLL_SIZE);
	// epoll FileDescriptor 생성
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
	
	// 소켓 생성
	sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockServer == -1)
	{
		fprintf(stderr, "socket() error\n");
		return 1;
	}
	fprintf(stderr, "socket() ok\n");

	int ret = 0;
	// 바인딩
	ret = bind(sockServer, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
	if (ret == -1)
	{
		fprintf(stderr, "bind() error\n");
		return 1;
	}
	fprintf(stderr, "bind() ok\n");
	// 리슨
	ret = listen(sockServer, 5);
	if (ret == -1)
	{
		fprintf(stderr, "listen() error\n");
		return 1;
	}
	fprintf(stderr, "listen() ok\n");

	// EPOLLIN(읽기) 이벤트를 감지
	pEvents->events = EPOLLIN;
	// 처음 데이터는 듣기 상태의 서버소켓으로 설정
	pEvents->data.fd = sockServer;
	// 리슨상태의 서버 소켓(sockServer)을 epoll 이벤트 풀에 추가시기며 결과는 pEvents 에 적용한다.
	epoll_ctl(fdEpoll, EPOLL_CTL_ADD, sockServer, pEvents);
	int i = 0;
	int NumOfEvents = 0;
	char buffer[MAX_LEN];
	while (1)
	{
		fprintf(stderr, "epoll_wait() ...\n");
		// epoll 이벤트 풀에서 이벤트가 일어날때까지 기다린다.
		NumOfEvents = epoll_wait(fdEpoll, pEvents, EPOLL_SIZE, -1);
		fprintf(stderr, "events occur!\n");
		if (NumOfEvents == -1)
		{
			fprintf(stderr, "epoll_wait() error\n");
		}
		// 발생한 이벤트 만큼 루프를 돌면서 처리한다.
		for (i=0; i<NumOfEvents; i++)
		{
			// 듣기 상태의 서버 소켓에서 이벤트가 발생하면
			if (pEvents[i].data.fd == sockServer)
			{
				// accpet 하고 클라이언트와 연결 소켓을 만든다.
				int sockClient = 0;
				struct sockaddr_in sockClientAddr;
				int szClient = sizeof(sockClientAddr);
				sockClient = accept(sockServer, (struct sockaddr*)&sockClientAddr, &szClient);
				fprintf(stderr, "accept()\n");
				// 읽기 이벤트가 발생했다고 설정한다.
				pEvents->events = EPOLLIN;
				// 읽기 이벤트의 filedescriptor 는 sockClient로 설정한다.
				pEvents->data.fd = sockClient;
				// sockClient 를 epoll 이벤트 풀에 추가시킨다.
				epoll_ctl(fdEpoll, EPOLL_CTL_ADD, sockClient, pEvents);
			}
			// 연결상태의 클라이언트 소켓에서 이벤트가 발생하면
			else
			{
				memset(buffer, 0, sizeof(char)*MAX_LEN);
				// 연결소켓에서 버퍼로 데이터 읽어 오기
				int n = read(pEvents[i].data.fd, buffer, MAX_LEN);
				// 읽어온 데이터가 없으면
				if (n <= 0)
				{
					// epoll 풀에서 연결 소켓을 제거하고
					epoll_ctl(fdEpoll, EPOLL_CTL_DEL, pEvents[i].data.fd, pEvents);
					// 연결 소켓을 닫는다.
					close(pEvents[i].data.fd);
					fprintf(stderr, "close socket(%d)\n", pEvents[i].data.fd);
				}
				// 읽어온 데이터가 있으면
				else
				{
					// 출력하고
					fprintf(stderr, "[socket=%d] %s received\n", pEvents[i].data.fd, buffer);
					// 데이터를 보낸다.
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
