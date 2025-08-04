// ysoftman
// pipe 사용 테스트
// pipe 는 커널에 생성되며 파일 디스크립터로 표현된다.
// 커널에 생성된 파이프는 여러 프로세서에서 파일 디스크립터로 사용 할 수 있다.
// 기본 파일 쓰기에 사용되는 PIPE_BUF 는 4096 으로 고정되어 있다.
// ulimit -a 에서 pipe size (512 bytes, -p) 8  = 512*8  (변경하지 못함)
#include <fcntl.h>  // linux 환경에서만 가능
#include <stdio.h>
#include <unistd.h>

#define MAX_SIZE 100000

int main() {
    // pipe() 시스템 호출로 파이프 생성
    // pipe() 는 2개의 정수 배열을 파라미터로 받는다.
    // fd[0] => 파이프에서 read 용
    // fd[1] => 파이프에 write 용
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return -1;
    }

    // fd[0], f[1] 은 파이프 하나에 대한 read/write 용도로 같은 크기를 가진다.
    fprintf(stdout, "fd[0] F_GETPIPE_SZ size: %d\n", fcntl(fd[0], F_GETPIPE_SZ));
    fprintf(stdout, "fd[1] F_GETPIPE_SZ size: %d\n", fcntl(fd[1], F_GETPIPE_SZ));

    // fcntl 로 F_SETPIPE_SZ 의 크기를 늘려 주지 않으면 64k(65536)까지만 atomic 쓰기가 가능하다.
    // F_SETPIPE_SZ -> Linux 2.6.35 부터 사용 가능하다.
    // F_SETPIPE_SZ 크기는 설정한 값보다 크게 설정될 수 있다. 65536 의 2,4,8,16 배로 버퍼가
    // 설정된다. 최대 제한 크기 /proc/sys/fs/pipe-max-size 에 명시되어 있다.
    fcntl(fd[0], F_SETPIPE_SZ, MAX_SIZE);

    fprintf(stdout, "fd[0] F_GETPIPE_SZ size: %d\n", fcntl(fd[0], F_GETPIPE_SZ));
    fprintf(stdout, "fd[1] F_GETPIPE_SZ size: %d\n", fcntl(fd[1], F_GETPIPE_SZ));

    int  fdes        = open("yoon.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    char LF          = '\n';
    char w           = 'c';
    char r[MAX_SIZE] = {
        0,
    };
    for (int i = 0; i < MAX_SIZE - 1; ++i) {
        // 파이프에 쓰기
        write(fd[1], &w, 1);
        fprintf(stdout, "%d bytes write\n", i);
    }
    write(fd[1], &LF, 1);

    // 파이프 내용 모두 읽어와 파일에 쓰기
    read(fd[0], &r, MAX_SIZE);
    write(fdes, &r, MAX_SIZE);

    close(fdes);

    close(fd[0]);
    close(fd[1]);

    return 0;
}
