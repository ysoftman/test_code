// ysoftman
// binaryserach, mergesort 등의 mid 위치 계산 유의 사항
// https://ai.googleblog.com/2006/06/extra-extra-read-all-about-it-nearly.html
#include <stdio.h>

int main()
{
    // 4byte int 범위 -2,147,483,648 to 2,147,483,647
    int left = 2000000000;
    int right = 2000000010;
    printf("left:%d  right:%d\n", left, right);
    // 심플하게 생각하면 다음과 같이 중간 위치를 구하려고 하지만
    // left + right 가 int 데이터 범위를 넘어 overflow 발생 음수값이 된다.
    // 이 값을 2로 나누면 역시 음수 값으로 올바른 중간 위치가 아니다.
    printf("(left + right) / 2   : %d\n", (left + right) / 2);

    // 다음과 같은 방식으로 overflow 를 방지한다.
    // left 기준으로 right - left 차이의 중간 값을 더하면 데이터 범위내에서 계산된다.
    printf("left + ((right - left) / 2)  : %d\n", left + ((right - left) / 2));
    // unsinged 로 큰 범위에서 계산해도 된다.
    printf("((unsigned int)left + (unsigned int)right) >> 1;  : %d\n", ((unsigned int)left + (unsigned int)right) >> 1);
    return 0;
}
