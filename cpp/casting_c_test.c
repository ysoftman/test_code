// ysoftman
// C casting
// gcc -std=c99 casting_c_test.c && a.out
#include <stdio.h>

int main() {
    long long lNumber = 123456789123456789;
    const int CONST_NUMBER = 123;
    double fNumber = 3.141592;
    char szStr[10] = "ysoftman";
    for (int i = 0; i < 10; ++i) {
        printf("%c\n", szStr[i]);
    }
    int nNumber = 0;

    printf("lNumber = %lld\n", lNumber);
    printf("CONST_NUMBER = %d\n", CONST_NUMBER);
    printf("fNumber = %f\n", fNumber);
    printf("szStr = %s\n", szStr);
    printf("nNumber = %d\n", nNumber);
    printf("\n");

    // C : 무조건 캐스팅됨
    nNumber = (int)lNumber;
    printf("nNumber = %d\n", nNumber);
    nNumber = (int)CONST_NUMBER;
    printf("nNumber = %d\n", nNumber);
    nNumber = (int)fNumber;
    printf("nNumber = %d\n", nNumber);
    nNumber = (int)szStr;
    printf("nNumber = %d\n", nNumber);
    printf("\n");

    return 0;
}
