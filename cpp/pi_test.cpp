// ysoftman
// PI(원주율) 구하기 방법 1
#include <stdio.h>

// CWI Dik T. Winter가 작성한 것으로 pi를 십진수 800자리까지 계산
int a = 10000, b, c = 2800, d, e, f[2801], g;

int main() {
    for (; b - c;) {
        f[b++] = a / 5;
    }
    for (; d = 0, g = c * 2; c -= 14, printf("%.4d", e + d / a), e = d % a) {
        for (b = c; d += f[b] * a, f[b] = d % --g, d /= g--, --b; d *= b);
    }

    return 0;
}
