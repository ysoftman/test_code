// ysoftman
// Thread test
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#include <process.h>
CRITICAL_SECTION cs;
#endif

static int nCount = 0;

#ifdef _WIN32
int job() {
    // 다른 thread 가 사용중이라면 작업을 마칠때까지 대기한다.
    EnterCriticalSection(&cs);

    nCount++;
    Sleep(50);
    printf("Thread(%d) Count = %d\n", GetCurrentThreadId(), nCount);

    LeaveCriticalSection(&cs);

    if (nCount >= 100) {
        return 1;
    }
    return 0;
}

unsigned int __stdcall Thread1(void *param) {
    for (;;) {
        if (job() == 1) {
            break;
        }
        Sleep(10);
    }
    _endthread();
    return 0;
}
unsigned int __stdcall Thread2(void *param) {
    for (;;) {
        if (job() == 1) {
            break;
        }
        Sleep(10);
    }
    _endthread();
    return 0;
}
#endif

int main() {
#ifdef _WIN32
    // critical_section 초기화
    InitializeCriticalSection(&cs);

    SYSTEM_INFO SystemInfo;
    GetSystemInfo(&SystemInfo);
    int NumOfProcessors = SystemInfo.dwNumberOfProcessors;
    int NumOfThread     = NumOfProcessors * 2;
    printf("NumOfProcessors = %d\n", NumOfProcessors);
    printf("NumOfThread = %d\n", NumOfThread);

    HANDLE hThreads[2];
    UINT   ThreadID;

    DWORD  tick_start;
    DWORD  tick_end;

    // 처리시간 파악
    tick_start  = GetTickCount();

    hThreads[0] = (HANDLE)_beginthreadex(NULL, 0, Thread1, (void *)1, 0, &ThreadID);
    hThreads[1] = (HANDLE)_beginthreadex(NULL, 0, Thread2, (void *)2, 0, &ThreadID);

    // 모든 쓰레드가 종료될때까지 기다린다.
    WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);
    printf("Result Count = %d\n", nCount);

    tick_end = GetTickCount();
    printf("Elapsed = %ld\n", tick_end - tick_start);

#endif

    return 0;
}
