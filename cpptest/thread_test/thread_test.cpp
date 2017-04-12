////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Thread test
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#include <process.h>
CRITICAL_SECTION cs;
#endif

static int nCount = 0;

#ifdef _WIN32
int job()
{
	// �ٸ� thread �� ������̶�� �۾��� ��ĥ������ ����Ѵ�.
	EnterCriticalSection(&cs);
	
	nCount++;
	Sleep(50);
	printf("Thread(%d) Count = %d\n", GetCurrentThreadId(), nCount);

	LeaveCriticalSection(&cs);

	if (nCount >= 100)
	{
		return 1;
	}
	return 0;
}

unsigned int __stdcall Thread1(void* param)
{
	for (;;)
	{
		if (job() == 1)
		{
			break;
		}
		Sleep(10);
	}
	_endthread();
	return 0;
}
unsigned int __stdcall Thread2(void* param)
{
	for (;;)
	{
		if (job() == 1)
		{
			break;
		}
		Sleep(10);
	}
	_endthread();
	return 0;
}
#endif

void main()
{
#ifdef _WIN32
	// critical_section �ʱ�ȭ
	InitializeCriticalSection(&cs);

	SYSTEM_INFO	SystemInfo;
	GetSystemInfo(&SystemInfo);
	int NumOfProcessors = SystemInfo.dwNumberOfProcessors;
	int NumOfThread = NumOfProcessors*2;
	printf("NumOfProcessors = %d\n", NumOfProcessors);
	printf("NumOfThread = %d\n", NumOfThread);

	HANDLE hThreads[2];
	UINT ThreadID;

	DWORD tick_start;
	DWORD tick_end;

	// ó���ð� �ľ�
	tick_start = GetTickCount();

	hThreads[0] = (HANDLE)_beginthreadex(NULL, 0, Thread1, (void*)1, 0, &ThreadID);
	hThreads[1] = (HANDLE)_beginthreadex(NULL, 0, Thread2, (void*)2, 0, &ThreadID);

	// ��� �����尡 ����ɶ����� ��ٸ���.
	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);
	printf("Result Count = %d\n", nCount);
	
	tick_end = GetTickCount();
	printf("Elapsed = %ld\n", tick_end - tick_start);

#endif
}

