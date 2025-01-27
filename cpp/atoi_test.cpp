// ysoftman
// atoi() 만들기
#include <stdio.h>

int main() {
    char str[20] = "11020482278";
    char *pValue = str;

    long Result = 0;

    // 첫번째부터 0 까지 숫자 하나씩 변환
    while (*pValue != '\0') {
        // 전에 변환된 값은 자리수를 올리고 여기에 대상 ASCII ()값 - ASCII 0(48) 을 뺀 값을 더한다.
        Result = (Result * 10) + (*pValue - '0');
        pValue++;
    }
    fprintf(stdout, "Result = %ld\n", Result);
    return 0;
}
