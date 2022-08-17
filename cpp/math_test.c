// ysoftman
// math 빌드시 m(math) library 를 링크해야 한다.
// gcc math_test.c -lm && ./a.out
#include <stdio.h>

// 헤더 추가하는 방법
// #include <math.h>
// 헤더 추가 없이 시그니처를 명시하는 방법(.c 인경우만)
// double sin(double x);
double sin();
int main()
{
    float i = 0;
    for (;;)
    {
        i++;
        printf("%f\n", sin(i));
        if (i == 10)
        {
            break;
        }
    }
    return 0;
}
