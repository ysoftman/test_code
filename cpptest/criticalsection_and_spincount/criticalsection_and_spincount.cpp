////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// InitializeCriticalSectionAndSpinCount ����ϱ�
// ������ ����� �׽�Ʈ �ϱ�
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500

#include <Windows.h>
#include <process.h>
CRITICAL_SECTION g_cs;

int g_num = 1;
void common_job(char *caller)
{
	EnterCriticalSection(&g_cs);
	
	//printf("caller(%s), g_num = %d\n", caller, g_num);
	g_num++;

	LeaveCriticalSection(&g_cs);
}
unsigned int WINAPI thread1(void *param)
{
	int i = 0;
	while (i < 100000000)
	{
		//printf("%s \n", __FUNCTION__);
		common_job(__FUNCTION__);
		i++;
	}
	return 0;
}

unsigned int WINAPI thread2(void *param)
{
	int i = 0;
	while (i < 100000000)
	{
		//printf("%s \n", __FUNCTION__);
		common_job(__FUNCTION__);
		i++;
	}
	return 0;
}
#endif

int main()
{
#if defined(_WIN32) || defined(_WIN64)

	printf("InitializeCriticalSectionAndSpinCount �׽�Ʈ\n");

	// �Ϲ����� criticalsection �ʱ�ȭ(CRITICAL_SECTION ����ü�� SpinCount = 0)
	//InitializeCriticalSection(&g_cs);

	// spin count ����� criticalsection �ʱ�ȭ
	// ������ XP �̻󿡼��� ����
	// http://msdn.microsoft.com/ko-kr/library/windows/desktop/ms683476(v=vs.85).aspx
	// Initializes a critical section object and sets the spin count for the critical section.
	// When a thread tries to acquire a critical section that is locked, the thread spins: it enters a loop which iterates spin count times, checking to see if the lock is released.
	// If the lock is not released before the loop finishes, the thread goes to sleep to wait for the lock to be released.
	// ����ȭ ��Ȳ���� �����尡 �ٷ� wait ���·� ���� �ʰ� spin count ��ŭ lock �� Ǯ�ȴ��� üũ�Ͽ� criticalsection �� ���� �õ��Ѵ�.
	// ���� spin count ��ŭ ���Ƶ� lock Ǯ���� ������ ��� wait ���·� ����Ǿ� lock Ǯ�������� ��ٸ���.
	// ��������� criticalsection �� wait ���·� ����ȴ°��� Ŀ�θ��� ��ȯ�Ǵ� ������ �ð� ����� �߻��ȴ�.
	// ��Ƽ�ھ� ȯ�濡���� ��Ȳ�� ���� spin count �� �����尡 wait ���·� �Ǳ����� criticalsection �� ȹ���� ��� ������ ��������
	// �ݴ�� spin count ���� lock �� Ǯ���� ������ spin count ��ŭ ������ ��������.
	InitializeCriticalSectionAndSpinCount(&g_cs, 4000);


	HANDLE hThreads[2];

	UINT nThread1ID = 0;
	UINT nThread2ID = 0;


	DWORD tick_start;
	DWORD tick_end;

	// ó���ð� �ľ�
	tick_start = GetTickCount();

	hThreads[0] = (HANDLE)_beginthreadex(NULL, 0, thread1, (void*)"arg", 0, &nThread1ID);
	hThreads[1] = (HANDLE)_beginthreadex(NULL, 0, thread2, (void*)"arg", 0, &nThread2ID);
	
	// ��� �����尡 ����ɶ����� ��ٸ���.
	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

	tick_end = GetTickCount();
	printf("g_num = %d\n", g_num);
	printf("Elapsed = %ld\n", tick_end - tick_start);

	DeleteCriticalSection(&g_cs);

#else
	printf("this system is not windows.\n");
#endif
	return 0;

}


