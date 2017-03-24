// ysoftman
// write 동시에 파일 쓰기 테스트
// 테스트 해보기
// g++ write_file_test.cpp
// rm yoon.txt
// ./a.out 1 & ./a.out 2 & ./a.out 3
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

	// 기존 함수에 추가
    int fd = open("yoon.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    
    // fcntl(fd, F_SETPIPE_SZ, 1024*1024);

    fprintf(stdout, "Theoretical max size: %ld\n", F_GETPIPE_SZ);

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

