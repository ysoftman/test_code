// ysoftman
// PI(원주율) 구하기 방법 2
// 위 프로그램을 개정한 것으로 16276 자리를 계산
#include <stdio.h>

int a = 1e4, b, c = 56980, d, e, f[56980], g, h, i;

int main() {
    for (; b = c, c -= 14; i = printf("%04d", e + d / a), e = d % a) {
        while (g = --b * 2) {
            d    = h * b + a * (i ? f[b] : a / 5);
            h    = d / --g;
            f[b] = d % g;
        }
    }

    return 0;
}
