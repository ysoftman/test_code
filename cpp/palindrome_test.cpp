// ysoftman
// Palindrome
#include <stdio.h>
#include <string.h>

int isPalindrome(char *str);

int main() {
    char input_string[10];

    // 1 : Palindrome
    // 0 : not
    int chk_result = 0;

    printf("Input String(length 10) to Verify Palindrome :  ");
    scanf("%s", input_string);

    chk_result = isPalindrome(input_string);

    if (chk_result == 1) {
        printf("\n\n[Result]%s is a Palindrome\n", input_string);
    } else if (chk_result == 0) {
        printf("\n\n[Result]%s is not a Palindrome\n.", input_string);
    }
    return 0;
}

int isPalindrome(char *str) {
    int index;
    int str_len = strlen(str);
    int pivot   = str_len / 2;

    for (index = 0; index < pivot; index++) {
        // 문자열의 처음과 끝을 비교 -> 문자의 가운데까지 검사
        if (str[index] == str[str_len - 1 - index]) {
            printf("\n%c and %c are same", str[index], str[str_len - 1 - index]);
        } else {
            printf("\n%c and %c are different", str[index], str[str_len - 1 - index]);
            // 다른 문자  발견 -> 더이상 검사하지 않고 종료(팰린드롬이 아니라고 판단)
            return 0;
        }
    }
    // 검사결과 팰린드롬이다
    return 1;
}
