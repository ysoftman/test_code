// ysoftman
// write 동시에 파일 쓰기 테스트
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>  // linux 환경에서만 가능

#define MAX_SIZE 1024*1024

int pipe_write_test()
{
    //////////////////////
    // 파이프로 쓰기
    int buf[2];
    char c = 'c';
    if (pipe(buf) == -1)
    {
        perror("pipe");
        return -1;
    }
    // fcntl 로 F_SETPIPE_SZ 의 크기를 늘려 주지 않으면 64k(65535)까지만 atomic 쓰기가 가능하다.
    // F_SETPIPE_SZ -> Linux 2.6.35 사용 가능
    fcntl(buf[0], F_SETPIPE_SZ, MAX_SIZE);
    
    for (int i = 1; i < MAX_SIZE; ++i)
    {
        write(buf[1], &c, 1);
        fprintf(stderr, "%d bytes write\n", i);
    }
    // 4096 으로 고정되어 있다.
    // ulimint -a 에서 pipe size (512 bytes, -p) 8  = 512*8  (변경하지 못함)
    fprintf(stdout, "PIPE_BUF size: %d\n", PIPE_BUF);
    // MAX_SIZE 만큼 설정되어 있음
    fprintf(stdout, "F_GETPIPE_SZ size: %d\n", fcntl(buf[1], F_GETPIPE_SZ));
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        pipe_write_test();
        fprintf(stdout, "argc != 2\n");
        exit(1);
    }
    fprintf(stdout, "argv[1] == %s\n", argv[1]);
    

    //////////////////////
    // 파일로 쓰기
    // 테스트 해보기
    // g++ write_file_test.cpp
    // rm yoon.txt 
    // ./a.out 1 & ./a.out 2 & ./a.out 3  
    int fd = open("yoon.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
            
    fprintf(stdout, "fd:%d 1.F_GETPIPE_SZ size: %d\n", fd, fcntl(fd, F_GETPIPE_SZ));
   
    fcntl(fd, F_SETPIPE_SZ, MAX_SIZE);

    fprintf(stdout, "fd:%d 2.F_GETPIPE_SZ size: %d\n", fd, fcntl(fd, F_GETPIPE_SZ));

    char temp[100000] = {0, };
    int i = 0;
    for (i=0; i<99999; ++i)
    {
        temp[i] = *argv[1];
    }
    temp[99999] = '\n';

    for (i=0; i<5; ++i)
    {
        write(fd, temp, 100000);
    }
    close(fd);

    return 0;
}
