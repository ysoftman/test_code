// ysoftman
// 자리수 숫자 파싱
#include <stdio.h>

int main()
{
    int n = 1230560;
    int temp = n;
    int digit_cnt = 1;
    while (temp >= 10)
    {
        temp /= 10;
        ++digit_cnt;
    }
    printf("n = %d, digit_cnt(%d)\n", n, digit_cnt);
    for (int i = 0; i < digit_cnt; ++i)
    {
        printf("%d ", n % 10);
        n /= 10;
    }
    printf("\n");
    return 0;
}
