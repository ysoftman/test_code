// ysoftman
// ASCII 코드 출력
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // ASCII 출력
    int number;
    for (number = 0; number < 128; number++) {
        printf("%d -> %c\n", number, number);
    }
    return 0;
}
