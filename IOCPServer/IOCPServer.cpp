////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// IOCP 를 테스트하기 위한 서버 프로그램
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <winsock2.h>

// winsock2.h 가 사용하는 라이브러리
#pragma comment(lib, "ws2_32.lib")

// 버퍼 최대 길이
const int MAX_LEN = 1024;
// 데이터 송수신 상태
const int DATA_RECEIVED = 1;
const int DATA_SENT = 2;

// 소켓 정보
typedef struct _SocketInfo
{
	SOCKET sock;
	SOCKADDR_IN sockAddrClient;
} t_SocketInfo, *t_pSocketInfo;

// 데이터 정보
typedef struct _DataInfo
{
	WSAOVERLAPPED wsaOverlapped;
	WSABUF wsaBuffer;
	char buffer[MAX_LEN];
	int mode;
} t_DataInfo, *t_pDataInfo;

// io 를 감시하고 처리할 쓰레드
DWORD WINAPI WorkerThread(LPVOID CompletionPortID)
{
	t_pSocketInfo pSocketInfo;
	t_pDataInfo pDataInfo;
	DWORD NumOfBytesTransferred = 0;
	DWORD NumOfBytesSent = 0;
	DWORD NumOfBytesReceived = 0;
	DWORD Flags = 0;

	while (true)
	{
		// IOCP의 완료보고 큐의 상태를 감시
		GetQueuedCompletionStatus((HANDLE)CompletionPortID, &NumOfBytesTransferred, (LPDWORD)&pSocketInfo, (LPOVERLAPPED*)&pDataInfo, INFINITE);
		
		// 주고받은 데이터가 업다면 소켓을 닫는다.
		if (!NumOfBytesTransferred)
		{
			fprintf(stderr, "[socket=%d] Closed\n", pSocketInfo->sock);
			closesocket(pSocketInfo->sock);
			GlobalFree(pSocketInfo);
			GlobalFree(pDataInfo);
			continue;
		}

		// 현재 쓰레드 파악
		HANDLE hThread = GetCurrentThread();
		DWORD ThreadID = GetThreadId(hThread);
		fprintf(stderr, "Current Thread ID = %d ", ThreadID);
		switch (pDataInfo->mode)
		{
			// 데이터를 수신 후
		case DATA_RECEIVED:
			fprintf(stderr, "[socket=%d] %s received\n", pSocketInfo->sock, pDataInfo->buffer);
			// 새로운 데이터를 보낸다.
			memset(&(pDataInfo->buffer), 0, sizeof(char)*MAX_LEN);
			strcpy_s(pDataInfo->buffer, 9, "ysoftman");
			memset(&(pDataInfo->wsaOverlapped), 0, sizeof(OVERLAPPED));
			pDataInfo->mode = DATA_SENT;
			Flags = 0;
			WSASend(pSocketInfo->sock, &(pDataInfo->wsaBuffer), 1, &NumOfBytesSent, Flags, &(pDataInfo->wsaOverlapped), NULL);
			//Sleep(10000);
			break;
			// 데이터를 보내고 난 후
		case DATA_SENT:
			fprintf(stderr, "[socket=%d] %s sent\n", pSocketInfo->sock, pDataInfo->buffer);
			// 새로운 데이터를 받는다.
			memset(&(pDataInfo->buffer), 0, sizeof(char)*MAX_LEN);
			memset(&(pDataInfo->wsaOverlapped), 0, sizeof(OVERLAPPED));
			pDataInfo->mode = DATA_RECEIVED;
			Flags = 0;
			WSARecv(pSocketInfo->sock, &(pDataInfo->wsaBuffer), 1, &NumOfBytesReceived, &Flags, &(pDataInfo->wsaOverlapped), NULL);
			break;
		}
	}

	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage : %s IP PORT\n", argv[0]);
		return 1;
	}

	SOCKET sockServer = INVALID_SOCKET;
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

	// IOCP 생성하기
	HANDLE hIOCP;
	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// 시스템 정보로 프로세스 개수 파악 2배수의 쓰레드 만들기
	SYSTEM_INFO	SystemInfo;
	GetSystemInfo(&SystemInfo);
	int NumOfThread = SystemInfo.dwNumberOfProcessors * 2;
	HANDLE hThread;
	DWORD ThreadID;
	for (int i=0; i<NumOfThread; i++)
	{
		hThread = CreateThread(NULL, 0, WorkerThread, hIOCP, 0, &ThreadID);
		if (hThread == NULL)
		{
			return 1;
		}
		CloseHandle(hThread);
		fprintf(stderr, "CreateThread() Thread ID = %d\n", ThreadID);
	}
	fprintf(stderr, "System Processor = %d Create Threads = %d\n", SystemInfo.dwNumberOfProcessors, NumOfThread);

	// Overlap IO 가능한 winsock2 로 socket 생성
	sockServer = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);
	// 일반적인 BSD socket 생성
	//sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockServer == INVALID_SOCKET)
	{
		fprintf(stderr, "Invalid Socket.\n");
		return 1;
	}

	// 소켓에 주소 바인딩
	bind(sockServer, (PSOCKADDR)&sockAddr, sizeof(SOCKADDR_IN));
	fprintf(stderr, "bind()\n");

	// 리슨 상태
	listen(sockServer, 5);
	fprintf(stderr, "listen()\n");

	// 이벤트 객체 생성
	WSAEVENT wsaEvent;
	wsaEvent = WSACreateEvent();
	// 소켓과 이벤트 객체 연결하기
	WSAEventSelect(sockServer, wsaEvent, FD_ACCEPT);

	while (true)
	{
		// 이벤트 객체가 신호을 받을때까지 기다리기
		WSAWaitForMultipleEvents(1, &wsaEvent, FALSE, WSA_INFINITE, FALSE);
		fprintf(stderr, "Request\n");

		// 소켓에 대한 네트워크 이벤트 파악
		WSANETWORKEVENTS wsaNetworkEvents;
		WSAEnumNetworkEvents(sockServer, wsaEvent, &wsaNetworkEvents);

		if (wsaNetworkEvents.lNetworkEvents & FD_ACCEPT)
		{
			SOCKET sockClient;
			SOCKADDR_IN sockAddrClient;
			int addlen = sizeof(SOCKADDR_IN);
			// 접속을 허용하고 접속 클라이언트 소켓 생성
			sockClient = WSAAccept(sockServer, (SOCKADDR*)&sockAddrClient, &addlen, NULL, NULL);

			t_pSocketInfo pSocketInfo = NULL;
			t_pDataInfo pDataInfo = NULL;
			pSocketInfo = (t_pSocketInfo)GlobalAlloc(GPTR, sizeof(t_SocketInfo));
			pDataInfo = (t_pDataInfo)GlobalAlloc(GPTR, sizeof(t_DataInfo));
			pSocketInfo->sock = sockClient;
			memcpy(&pSocketInfo->sockAddrClient, &sockAddrClient, addlen);
			fprintf(stderr, "[socket=%d] Connected\n", sockClient);

			// IOCP 에 소켓 등록
			CreateIoCompletionPort((HANDLE)sockClient, hIOCP, (DWORD)pSocketInfo, 0);

			memset(&(pDataInfo->wsaOverlapped), 0, sizeof(OVERLAPPED));
			memset(&(pDataInfo->buffer), 0, sizeof(char)*MAX_LEN);
			pDataInfo->wsaBuffer.len = MAX_LEN;
			pDataInfo->wsaBuffer.buf = pDataInfo->buffer;
			pDataInfo->mode = DATA_RECEIVED;
			
			DWORD Flags = 0;
			DWORD NumOfBytesReceived = 0;

			WSARecv(sockClient, &(pDataInfo->wsaBuffer), 1, &NumOfBytesReceived, &Flags, &(pDataInfo->wsaOverlapped), NULL);
		}
	}

	WSACleanup();

	return 0;
}
