// ysoftman
// cpu 사용률 테스트를 위한 단순 더하기
#include <stdio.h>

int main() {
    long long i;
    for (i = 0; i < 100000000000; i++) {
        if (i % 100000000 == 0) {
            printf("i = %lld\n", i);
        }
    }
    printf("i = %lld\n", i);

    return 0;
}
