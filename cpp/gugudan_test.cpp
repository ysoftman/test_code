// ysoftman
// 구구단 입력 받아 출력(1 ~ 9 숫자만)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int num1, num2;
    char ch;

    // 출력할 단 입력 받기
    while (1) {
        printf("Input Number: ");
        if ((ch = getchar()) != 0) {
            if (ch >= 49 && ch <= 57) {
                printf("Input number is %d\n", ch - 48);
                num1 = ch - 48;
                break;
            } else {
                printf("Input number1 Again\n");
            }
        }
    }

    for (num2 = 1; num2 <= 10; num2++) {
        printf("%2d * %2d = %2d\n", num1, num2, num1 * num2);
    }
    return 0;
}
