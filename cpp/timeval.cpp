// ysoftman
// timeval 구조체 테스트
#include <stdio.h>
#include <sys/time.h>

int main() {
    printf("timeval structure test\n");
    timeval tv;
    // get current time to tv
    gettimeofday(&tv, NULL);
    // epoch time seconds
    printf("tv.sec:%ld\n", tv.tv_sec);
    // epoch time micro seconds
    printf("tv.usec:%ld\n", tv.tv_usec);

    return 0;
}
