// ysoftman
// masking test
#include <stdio.h>
#include <ctype.h>

int main()
{
    // case1
    printf("### case1\n");
    char szValue1[50] = "ysoftman_123+asdf";
    printf("szValue1=%s\n", szValue1);
    char *p = szValue1;
    // a-z, 0-9 인경우 X 로 변환(마스킹)하기
    // 특수문자 전까지만 마스킹 된다.
    while (isalnum(*p))
    {
        *p = 'X';
        p++;
    }
    printf("szValue1=%s\n", szValue1);

    // case2
    printf("### case2\n");
    //char szValue2[50] = "ysoftman_123+asdf&";
    // &로 끝나지 않은 경우
    char szValue2[50] = "ysoftman_123+asdf";
    p = szValue2;
    while (*p != '\0' && *p != '&')
    {
        // printf("%d\n", *p);
        *p = 'X';
        p++;
    }
    printf("szValue2=%s\n", szValue2);
}
