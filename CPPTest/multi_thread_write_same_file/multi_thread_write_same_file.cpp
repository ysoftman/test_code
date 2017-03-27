// ysoftman
// 파일 동시쓰기 테스트
// g++ -lpthread 로 컴파일
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

void *write_func(void *arg)
{
    int fd = open("yoon.txt",O_CREAT | O_WRONLY | O_APPEND, 0664);

    int len = 0;
    for (;len<100000;)
    {
        if (((char*)arg)[len] == '\n')
        {
                break;
        }
        ++len;
    }
    printf("len:%d\n", ++len);
    for (int i=0; i<10000; ++i)
    {
        write(fd, (char*)arg, len);
    }

    close(fd);
}

int main()
{
    printf("SSIZE_MAX : %ld\n", SSIZE_MAX);

    char buffer1[100000] = {0,};
    char buffer2[100000] = {0,};
    sprintf(buffer1, "apple_juice_ok\n");
    sprintf(buffer2, "lemon_soda_good\n");

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
