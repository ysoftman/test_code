// ysoftman
// 대문자 알파벳 하나가 입력 되었을 때 문자를 배열하여
// 입력된 문자를 그래픽으로 표현하는 출력을 생성 => BANNER
#include <stdio.h>
#include <string.h>

// 코드에 맞게 출력하기
void Draw(char *code) {
    int i;
    int j;
    int k;

    // 첫번째 값은 라인 수
    for (i = 0; i < code[0]; i++) {
        // 두번재 값부터는 라인마다 출력할 X 표시하기
        for (j = 1; j < 20; j++) {
            if (code[j] == '\0') {
                break;
            }

            // 찍을 문자
            if (code[j] == 'x') {
                // 몇개나 찍을 것인가?
                for (k = 0; k < code[j + 1]; k++) {
                    printf("x");
                }
            }
            if (code[j] == 'b') {
                for (k = 0; k < code[j + 1]; k++) {
                    printf(" ");
                }
            }
        }

        printf("\n");
    }
}

// 코드 초기화
void InitCode(char *code) {
    int i;

    for (i = 0; i < 20; i++) {
        code[i] = '\0';
    }
}

int main() {
    char code[20];
    char str;
    printf("\nInput Character I: ");
    scanf("%c", &str);

    switch (str) {
        case 'I':
            code[0] = 3;    // 라인 수
            code[1] = 'x';  // 찍을 문자
            code[2] = 9;    // 몇개나 찍을 것인가?
            Draw(code);
            InitCode(code);
            code[0] = 6;
            code[1] = 3;
            code[2] = 'b';
            code[3] = 3;
            code[4] = 'x';
            code[5] = 3;
            code[7] = 'b';
            Draw(code);
            InitCode(code);
            code[0] = 3;
            code[1] = 'x';
            code[2] = 9;
            Draw(code);
            InitCode(code);
            break;
    }
    return 0;
}
