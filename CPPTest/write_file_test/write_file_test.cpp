// ysoftman
// write 동시에 파일 쓰기 테스트
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>  // linux 환경에서만 가능

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stdout, "argc != 2\n");
        exit(1);
    }
    fprintf(stdout, "argv[1] == %s\n", argv[1]);
    fprintf(stdout, "max pipe size: %d\n", PIPE_BUF);
    fprintf(stdout, "max pipe size: %d\n", F_GETPIPE_SZ);

    return 1;
    int fd = open("yoon.txt", O_WRONLY | O_CREAT | O_EXCL, 0644);
    //fcntl(fd, F_SETPIPE_SZ, 1024*1024);

    fprintf(stdout, "Theoretical max size: %ld\n", F_GETPIPE_SZ);

    char temp[1024*1024] = {0, };
    for (int i=0; i<1024*1024; ++i)
    {
        temp[i] = *argv[1];
    }

    for (int i=0; i<10; ++i)
    {
        write(fd, temp, 1024*1024);
    }
    close(fd);

    return 0;
}
