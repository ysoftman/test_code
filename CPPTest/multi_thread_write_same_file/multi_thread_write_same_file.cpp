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

struct thread_args {
    int fd;
    char buffer[MAX_LEN+2];
    thread_args() {
        fd = 0;
        memset(buffer, 0, MAX_LEN+2);
    }
};


// 파일 쓰기 작업
void *write_func(void *arg)
{
    // newline 기준 길이 파악
    int len = 0;
    for (;len<MAX_LEN;)
    {
        if (((char*)((thread_args*)(arg))->buffer)[len] == '\n')
        {
            break;
        }
        ++len;
    }
    printf("len:%d\n", ++len);
    for (int i=0; i<10; ++i)
    {
        write(((thread_args*)(arg))->fd, (char*)((thread_args*)(arg))->buffer, len);
    }
}

int main()
{
    printf("SSIZE_MAX : %ld\n", SSIZE_MAX);

    int fd = open("yoon.txt",O_CREAT | O_WRONLY | O_APPEND, 0664);

    // 데이터 준비
    thread_args th_arg1;
    thread_args th_arg2;

    th_arg1.fd = fd;
    th_arg2.fd = fd;

    for (int i=0; i < MAX_LEN/10; ++i) strcat(th_arg1.buffer, "OOOOOOOOOO");
    strcat(th_arg1.buffer, "\n");

    for (int i=0; i < MAX_LEN/10; ++i) strcat(th_arg2.buffer, "XXXXXXXXXX");
    strcat(th_arg2.buffer, "\n");

    // 멀티 쓰레드로 파일 하나에 동시 쓰기
    int status;
    pthread_t pth[2];
    pthread_create(&pth[0], NULL, write_func, (void*)&th_arg1);
    pthread_create(&pth[1], NULL, write_func, (void*)&th_arg2);

    pthread_join(pth[0], (void**)&status);
    printf("thread1 finish. status:%d\n", status);
    pthread_join(pth[1], (void**)&status);
    printf("thread2 finish. status:%d\n", status);


    close(fd);

    return 0;
}
