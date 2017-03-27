// ysoftman
// 파일 동시쓰기 테스트
// g++ -lpthread 로 컴파일
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

const int MAX_LEN = 100000;

void *write_func(void *arg)
{
    int fd = open("yoon.txt",O_CREAT | O_WRONLY | O_APPEND, 0664);

    int len = 0;
    for (;len<MAX_LEN;)
    {
        if (((char*)arg)[len] == '\n')
        {
                break;
        }
        ++len;
    }
    printf("len:%d\n", ++len);
    for (int i=0; i<100; ++i)
    {
        write(fd, (char*)arg, len);
    }

    close(fd);
}

int main()
{
    printf("SSIZE_MAX : %ld\n", SSIZE_MAX);

    char buffer1[MAX_LEN] = {0,};
    char buffer2[MAX_LEN] = {0,};

    for (int i=0; i < MAX_LEN/10-1; ++i) strcat(buffer1, "OOOOOOOOOO");
    strcat(buffer1, "\n");

    for (int i=0; i < MAX_LEN/10-1; ++i) strcat(buffer2, "XXXXXXXXXX");
    strcat(buffer2, "\n");

    int status;
    pthread_t pth[2];
    pthread_create(&pth[0], NULL, write_func, (void*)&buffer1);
    pthread_create(&pth[1], NULL, write_func, (void*)&buffer2);

    pthread_join(pth[0], (void**)&status);
    printf("thread1 finish. status:%d\n", status);
    pthread_join(pth[1], (void**)&status);
    printf("thread2 finish. status:%d\n", status);

    return 0;
}
