// ysoftman
// Difference between ++i and i++
#include <stdio.h>

int main() {
    const int max = 5;
    int       i   = 0;

    // 전위, 후위 증가 연산자의 결과는 같다
    printf("for 문에서 i++ 사용\n");
    for (int i = 0; i < max; i++) {
        printf("%2d", i);
    }
    printf("\n");

    i = 0;
    printf("for 문에서 ++i 사용\n");
    for (int i = 0; i < max; ++i) {
        printf("%2d", i);
    }
    printf("\n");

    i = 0;
    printf("i : %2d\n", i);
    printf("++i : %2d\n", ++i);
    i = 0;
    // 후위 증가는 현재 변수값을 다른 변수에 저장 후 현재 변수를 증가시키고 다른 변수를 리턴한다.
    // temp = i;
    // i = i + 1;
    // return temp;
    // 보통 성능 향상을 위해서 for 루프내에선 ++i 로 전위 증가를 사용한다.
    printf("i++ : %2d\n", i++);
    printf("i : %2d\n", i);

    return 0;
}
