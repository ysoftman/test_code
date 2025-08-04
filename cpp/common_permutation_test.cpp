// ysoftman
// Common Permutation
// 두개의 문자열의 공통적으로 만들수 있는 부분 문자열 중 가장 긴 문자열 출력하기
#include <stdio.h>
#include <string.h>

#define min(x, y) ((x) < (y) ? (x) : (y))

int main() {
    char        *s;
    char         str1[100];
    char         str2[100];

    unsigned int cnt1[256];
    unsigned int cnt2[256];

    unsigned int i, j;

    printf("Common Permutation\n");

    while (1) {
        printf("\nFirst String (0 to Exit): ");
        scanf("%s", str1);

        if (strcmp(str1, "0") == 0) {
            printf("\n\nExit...\n");
            break;
        }

        printf("\nSecond String : ");
        scanf("%s", str2);

        // 초기화
        for (i = 0; i < 256; i++) {
            cnt1[i] = cnt2[i] = 0;
        }

        for (s = str1; *s; s++) {
            cnt1[*s]++;
        }
        for (s = str2; *s; s++) {
            cnt2[*s]++;
        }

        for (i = 0; i < 256; i++) {
            for (j = 0; j < min(cnt1[i], cnt2[i]); j++) {
                // printf("%d", j);
                putchar((char)i);
            }
        }
        printf("\n");
    }
    return 0;
}
