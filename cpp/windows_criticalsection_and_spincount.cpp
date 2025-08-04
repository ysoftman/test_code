// ysoftman
// InitializeCriticalSectionAndSpinCount 사용하기
// 릴리즈 빌드로 테스트 하기
#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500

#include <Windows.h>
#include <process.h>
CRITICAL_SECTION g_cs;

int              g_num = 1;
void             common_job(char *caller) {
    EnterCriticalSection(&g_cs);

    // printf("caller(%s), g_num = %d\n", caller, g_num);
    g_num++;

    LeaveCriticalSection(&g_cs);
}
unsigned int WINAPI thread1(void *param) {
    int i = 0;
    while (i < 100000000) {
        // printf("%s \n", __FUNCTION__);
        common_job(__FUNCTION__);
        i++;
    }
    return 0;
}

unsigned int WINAPI thread2(void *param) {
    int i = 0;
    while (i < 100000000) {
        // printf("%s \n", __FUNCTION__);
        common_job(__FUNCTION__);
        i++;
    }
    return 0;
}
#endif

int main() {
#if defined(_WIN32) || defined(_WIN64)

    printf("InitializeCriticalSectionAndSpinCount 테스트\n");

    // 일반적인 criticalsection 초기화(CRITICAL_SECTION 구조체의 SpinCount = 0)
    // InitializeCriticalSection(&g_cs);

    // spin count 명시한 criticalsection 초기화
    // 윈도우 XP 이상에서만 지원
    // http://msdn.microsoft.com/ko-kr/library/windows/desktop/ms683476(v=vs.85).aspx
    // Initializes a critical section object and sets the spin count for the critical section.
    // When a thread tries to acquire a critical section that is locked, the thread spins: it enters
    // a loop which iterates spin count times, checking to see if the lock is released. If the lock
    // is not released before the loop finishes, the thread goes to sleep to wait for the lock to be
    // released. 동기화 상황에서 쓰레드가 바로 wait 상태로 되지 않고 spin count 만큼 lock 이
    // 풀렸는지 체크하여 criticalsection 에 접근 시도한다. 만약 spin count 만큼 돌아도 lock 풀리지
    // 않으면 대기 wait 상태로 변경되어 lock 풀릴때까지 기다린다. 유저모드의 criticalsection 가 wait
    // 상태로 변경된는것은 커널모드로 전환되는 것으로 시간 비용이 발생된다. 멀티코어 환경에서는
    // 상황에 따라 spin count 로 쓰레드가 wait 상태로 되기전에 criticalsection 을 획득한 경우 성능이
    // 향상되지만 반대로 spin count 내에 lock 이 풀리지 않으면 spin count 만큼 성능이 느려진다.
    InitializeCriticalSectionAndSpinCount(&g_cs, 4000);

    HANDLE hThreads[2];

    UINT   nThread1ID = 0;
    UINT   nThread2ID = 0;

    DWORD  tick_start;
    DWORD  tick_end;

    // 처리시간 파악
    tick_start  = GetTickCount();

    hThreads[0] = (HANDLE)_beginthreadex(NULL, 0, thread1, (void *)"arg", 0, &nThread1ID);
    hThreads[1] = (HANDLE)_beginthreadex(NULL, 0, thread2, (void *)"arg", 0, &nThread2ID);

    // 모든 쓰레드가 종료될때까지 기다린다.
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
