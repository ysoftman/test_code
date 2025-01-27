// ysoftman
// linux 데몬 테스트 프로그램
#ifdef linux
#include <stdio.h>
#include <unistd.h>

int main() {
    // fork() 는 복사본(자식) 프로세스를 만들어, 결국 2개의 프로세스가 생성기게 된다.
    // 에러가 없을 경우,
    // fork() 는 원본 프로세스에게는 복사본 프로세스의 ID를 리턴하고, 복사본 프로세스에게는 0을
    // 리턴한다.
    int pid = fork();
    switch (pid) {
        case -1:
            fprintf(stderr, "fork filed.\n");
            break;
            // 복사본(자식) 프로세스의 경우 계속 작업 수행(데몬 프로세스로 작동)
        case 0:
            fprintf(stderr, "fork succeed.\n");
            break;
            // 원본(부모) 프로세스의 경우 프로그램 종료
        default:
            fprintf(stderr, "child process id : %d\n", pid);
            return 0;
    }

    // 복사본(자식) 프로세스는 작업을 수행한다.
    int count = 0;
    while (1) {
        fprintf(stderr, "ysoftmand count=%d\n", count++);
        // 2초간의 딜레이
        sleep(2);
    }
    return 0;
}
#endif
