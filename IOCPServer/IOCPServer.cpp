////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// IOCP �� �׽�Ʈ�ϱ� ���� ���� ���α׷�
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <winsock2.h>

// winsock2.h �� ����ϴ� ���̺귯��
#pragma comment(lib, "ws2_32.lib")

// ���� �ִ� ����
const int MAX_LEN = 1024;
// ������ �ۼ��� ����
const int DATA_RECEIVED = 1;
const int DATA_SENT = 2;

// ���� ����
typedef struct _SocketInfo
{
	SOCKET sock;
	SOCKADDR_IN sockAddrClient;
} t_SocketInfo, *t_pSocketInfo;

// ������ ����
typedef struct _DataInfo
{
	WSAOVERLAPPED wsaOverlapped;
	WSABUF wsaBuffer;
	char buffer[MAX_LEN];
	int mode;
} t_DataInfo, *t_pDataInfo;

// io �� �����ϰ� ó���� ������
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
		// IOCP�� �ϷẸ�� ť�� ���¸� ����
		GetQueuedCompletionStatus((HANDLE)CompletionPortID, &NumOfBytesTransferred, (LPDWORD)&pSocketInfo, (LPOVERLAPPED*)&pDataInfo, INFINITE);
		
		// �ְ���� �����Ͱ� ���ٸ� ������ �ݴ´�.
		if (!NumOfBytesTransferred)
		{
			fprintf(stderr, "[socket=%d] Closed\n", pSocketInfo->sock);
			closesocket(pSocketInfo->sock);
			GlobalFree(pSocketInfo);
			GlobalFree(pDataInfo);
			continue;
		}

		// ���� ������ �ľ�
		HANDLE hThread = GetCurrentThread();
		DWORD ThreadID = GetThreadId(hThread);
		fprintf(stderr, "Current Thread ID = %d ", ThreadID);
		switch (pDataInfo->mode)
		{
			// �����͸� ���� ��
		case DATA_RECEIVED:
			fprintf(stderr, "[socket=%d] %s received\n", pSocketInfo->sock, pDataInfo->buffer);
			// ���ο� �����͸� ������.
			memset(&(pDataInfo->buffer), 0, sizeof(char)*MAX_LEN);
			strcpy_s(pDataInfo->buffer, 9, "ysoftman");
			memset(&(pDataInfo->wsaOverlapped), 0, sizeof(OVERLAPPED));
			pDataInfo->mode = DATA_SENT;
			Flags = 0;
			WSASend(pSocketInfo->sock, &(pDataInfo->wsaBuffer), 1, &NumOfBytesSent, Flags, &(pDataInfo->wsaOverlapped), NULL);
			//Sleep(10000);
			break;
			// �����͸� ������ �� ��
		case DATA_SENT:
			fprintf(stderr, "[socket=%d] %s sent\n", pSocketInfo->sock, pDataInfo->buffer);
			// ���ο� �����͸� �޴´�.
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

	// IOCP �����ϱ�
	HANDLE hIOCP;
	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// �ý��� ������ ���μ��� ���� �ľ� 2����� ������ �����
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

	// Overlap IO ������ winsock2 �� socket ����
	sockServer = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);
	// �Ϲ����� BSD socket ����
	//sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockServer == INVALID_SOCKET)
	{
		fprintf(stderr, "Invalid Socket.\n");
		return 1;
	}

	// ���Ͽ� �ּ� ���ε�
	bind(sockServer, (PSOCKADDR)&sockAddr, sizeof(SOCKADDR_IN));
	fprintf(stderr, "bind()\n");

	// ���� ����
	listen(sockServer, 5);
	fprintf(stderr, "listen()\n");

	// �̺�Ʈ ��ü ����
	WSAEVENT wsaEvent;
	wsaEvent = WSACreateEvent();
	// ���ϰ� �̺�Ʈ ��ü �����ϱ�
	WSAEventSelect(sockServer, wsaEvent, FD_ACCEPT);

	while (true)
	{
		// �̺�Ʈ ��ü�� ��ȣ�� ���������� ��ٸ���
		WSAWaitForMultipleEvents(1, &wsaEvent, FALSE, WSA_INFINITE, FALSE);
		fprintf(stderr, "Request\n");

		// ���Ͽ� ���� ��Ʈ��ũ �̺�Ʈ �ľ�
		WSANETWORKEVENTS wsaNetworkEvents;
		WSAEnumNetworkEvents(sockServer, wsaEvent, &wsaNetworkEvents);

		if (wsaNetworkEvents.lNetworkEvents & FD_ACCEPT)
		{
			SOCKET sockClient;
			SOCKADDR_IN sockAddrClient;
			int addlen = sizeof(SOCKADDR_IN);
			// ������ ����ϰ� ���� Ŭ���̾�Ʈ ���� ����
			sockClient = WSAAccept(sockServer, (SOCKADDR*)&sockAddrClient, &addlen, NULL, NULL);

			t_pSocketInfo pSocketInfo = NULL;
			t_pDataInfo pDataInfo = NULL;
			pSocketInfo = (t_pSocketInfo)GlobalAlloc(GPTR, sizeof(t_SocketInfo));
			pDataInfo = (t_pDataInfo)GlobalAlloc(GPTR, sizeof(t_DataInfo));
			pSocketInfo->sock = sockClient;
			memcpy(&pSocketInfo->sockAddrClient, &sockAddrClient, addlen);
			fprintf(stderr, "[socket=%d] Connected\n", sockClient);

			// IOCP �� ���� ���
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
