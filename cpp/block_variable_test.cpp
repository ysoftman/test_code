// ysoftman
// 지역변수에 대해서 알아보려고
// 제어문 블럭안의 변수 할당은 블럭안에서만 유효
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int i = 0;
    while (i <= 100) {
        int j = 1;
        i++;
    }
    //	j = 3;
    return 0;
}
