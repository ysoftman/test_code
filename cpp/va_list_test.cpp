// ysoftman
// 가변인자(variadic arguments)를 통한 printf() 함수 구현
#include <stdarg.h>
#include <stdio.h>

// ... 는 가변인자뜻한다.
void TestPrintf(const char *format, ...) {
    // va_list 는 char* 로 선언되어 있다.
    va_list args;
    // 가변인자 리스트의 첫번째를 args로 위치시킨다.
    va_start(args, format);
    // format 에 맞게 arg 리스트를 출력한다.
    vfprintf(stdout, format, args);
    // args 를 0 으로 리셋한다.
    va_end(args);
}

int main() {
    int  a = 10, b = 20;
    char pTemp[] = "YoonByoungHoon";
    TestPrintf("%d %d %s\n", a, b, pTemp);

    return 0;
}
