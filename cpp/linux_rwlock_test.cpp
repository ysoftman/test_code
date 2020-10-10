// ysoftman
// linux RWLock test
// 컴파일시 -lpthread 사용
#include <stdio.h>

#ifdef linux
#include <unistd.h>
#include <pthread.h>

pthread_rwlock_t gRWLock;

// 읽기 용도로 호출 되는 함수
void *readfunc(void *arg)
{
	// Read Lock 은 여러 쓰레드가 동시 접근 가능
	pthread_rwlock_rdlock(&gRWLock);
	printf("readfunc threadId(%u)\n", (unsigned int)pthread_self());
	sleep(1);
	pthread_rwlock_unlock(&gRWLock);
	return (void*)0;
}

// 쓰기 용도로 호출 되는 함수
void *writefunc(void *arg)
{
	// Write Lock 은 Critical Section 처럼 동시에 하나만 접근 가능하다.
	// 모든 Read Lock 이 끝나야지 접근 가능하다.
	pthread_rwlock_wrlock(&gRWLock);
	printf("writefunc threadId(%u)\n", (unsigned int)pthread_self());
	sleep(1);
	pthread_rwlock_unlock(&gRWLock);
	return (void*)0;
}

int main()
{
	printf("this system is linux\n");
	printf("processId(%u)\n", getpid());
	pthread_rwlock_init(&gRWLock, NULL);

	const int nThreadCnt = 10;
	pthread_t readThread[nThreadCnt];
	pthread_t writeThread;
	
	for (int i=0; i<nThreadCnt; ++i)
	{
		pthread_create(&readThread[i], NULL, readfunc, NULL);
		// 쓰기 함수가 3번째로 수행되지 않고
		// 읽기 쓰레드가 모두 종료된 후 수행된다.
		if (i==3)
		{
			pthread_create(&writeThread, NULL, writefunc, NULL);
		}
	}	
	int status = 0;
	for (int i=0; i<nThreadCnt; ++i)
	{
		pthread_join(readThread[i], (void**)&status);
	}
	pthread_join(writeThread, (void**)&status);

	pthread_rwlock_destroy(&gRWLock);
	return 0;
}
#endif


