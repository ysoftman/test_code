////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// linux RWLock test
// �����Ͻ� -lpthread ���
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#ifdef linux
#include <unistd.h>
#include <pthread.h>

pthread_rwlock_t gRWLock;

// �б� �뵵�� ȣ�� �Ǵ� �Լ�
void *readfunc(void *arg)
{
	// Read Lock �� ���� �����尡 ���� ���� ����
	pthread_rwlock_rdlock(&gRWLock);
	printf("readfunc threadId(%u)\n", (unsigned int)pthread_self());
	sleep(1);
	pthread_rwlock_unlock(&gRWLock);
	return (void*)0;
}

// ���� �뵵�� ȣ�� �Ǵ� �Լ�
void *writefunc(void *arg)
{
	// Write Lock �� Critical Section ó�� ���ÿ� �ϳ��� ���� �����ϴ�.
	// ��� Read Lock �� �������� ���� �����ϴ�.
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
		// ���� �Լ��� 3��°�� ������� �ʰ�
		// �б� �����尡 ��� ����� �� ����ȴ�.
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


