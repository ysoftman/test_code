// ysoftman
// 파일 동시쓰기 테스트
// g++ -lpthread 로 컴파일
// 테스트 해보기 X 와 O 가 같은 라인에 존재하는지 체크
// g++ -lpthread multi_thread_write_same_file.cpp && rm -f yoon*.txt && ./a.out && grep XO yoon*.txt && grep OX yoon*.txt
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

const int THREAD_CNT = 1;
const int MAX_LEN = 100000;

struct thread_args {
    int fd;
    FILE *fp;
    char buffer[MAX_LEN+1];
    thread_args() {
        fd = 0;
        fp = NULL;
        memset(buffer, 0, MAX_LEN+1);
    }
};


// 파일 쓰기 작업
void *write_func(void *arg)
{
    // newline 기준 길이 파악
    int len = 0;
    for (;len<MAX_LEN+1;)
    {
        if (((char*)((thread_args*)(arg))->buffer)[len] == '\n')
        {
            break;
        }
        ++len;
    }
    printf("len:%d\n", ++len);
    for (int i=0; i<1; ++i)
    {
        write(((thread_args*)(arg))->fd, (char*)((thread_args*)(arg))->buffer, len);
        // fprintf(((thread_args*)(arg))->fp, "%s", (char*)((thread_args*)(arg))->buffer);
    }

    pthread_exit((void *) 0);
}

int main()
{
    printf("SSIZE_MAX : %ld\n", SSIZE_MAX);

    FILE *fp = fopen("yoon.txt", "a");
    int fd = open("yoon2.txt",O_CREAT | O_WRONLY | O_APPEND, 0664);

    // 데이터 준비
    thread_args th_arg1;
    thread_args th_arg2;

    th_arg1.fd = fd;
    th_arg2.fd = fd;
    th_arg1.fp = fp;
    th_arg2.fp = fp;

    // for (int i=0; i < MAX_LEN/10; ++i) strcat(th_arg1.buffer, "OOOOOOOOOO");
    memset(th_arg1.buffer, 0x4F, MAX_LEN);
    strcat(th_arg1.buffer, "\n");

    // for (int i=0; i < MAX_LEN/10; ++i) strcat(th_arg2.buffer, "XXXXXXXXXX");
    memset(th_arg2.buffer, 0x58, MAX_LEN);
    strcat(th_arg2.buffer, "\n");

    // 멀티 쓰레드로 파일 하나에 동시 쓰기
    int status;
    pthread_t pth[THREAD_CNT];
    for (int i=0; i<THREAD_CNT; i++)
    {
        if (i%2==0)
        {
            pthread_create(&pth[i], NULL, write_func, (void*)&th_arg1);
        }
        else
        {
            pthread_create(&pth[i], NULL, write_func, (void*)&th_arg2);
        }
    }


    for (int i=0; i<THREAD_CNT; i++)
    {
        pthread_join(pth[i], (void**)&status);
        printf("thread[%d] finish. status:%d\n", i, status);
    }

    close(fd);
    fclose(fp);

    return 0;
}

