// ysoftman
// 포인터 테스트
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 메모리 할당후의 주소를 caller 의 포인터에게 전달해주기 위해 이중포인터 사용
void MakeName(char **pName) {
    *pName = (char *)malloc(100);
    memset(*pName, 0, 100);
    // 윈도우에서만 사용 할 수 있어 주석 처리
    // strncpy_s(*pName, 100, "ysoftman", strlen("ysoftman"));
    strncpy(*pName, "ysoftman", strlen("ysoftman"));
}

int main() {
    int  arr[3] = {1, 2, 3};
    int *ptr;
    ptr = arr;
    // 1차원 배열 포인터로 표현
    printf("array[3] : arr[0]=%d, arr[1]=%d, arr[2]=%d\n", arr[0], arr[1], arr[2]);
    printf("*ptr : ptr[0]=%d, ptr[1]=%d, ptr[2]=%d\n", ptr[0], ptr[1], ptr[2]);

    // 2차원 배열 포인터로 표현
    int arr2[2][3] = {1, 2, 3, 4, 5, 6};
    int (*ptr2)[3];
    ptr2 = arr2;
    printf(
        "array2[2][3] : arr2[0][0]=%d, arr2[0][1]=%d, arr2[0][2]=%d, arr2[1][0]=%d, arr2[1][1]=%d, "
        "arr2[1][2]=%d\n",
        arr2[0][0], arr2[0][1], arr2[0][2], arr2[1][0], arr2[1][1], arr2[1][2]);
    printf(
        "(*ptr2)[3] : ptr2[0][0]=%d, ptr2[0][1]=%d, ptr2[0][2]=%d, ptr2[1][0]=%d, ptr2[1][1]=%d, "
        "ptr2[1][2]=%d\n",
        ptr2[0][0], ptr2[0][1], ptr2[0][2], ptr2[1][0], ptr2[1][1], ptr2[1][2]);

    // 이중 포인터로 1차원 포인터 참조하기
    int  a    = 10;
    int *pp1  = NULL;
    pp1       = &a;
    int **pp2 = NULL;
    pp2       = &pp1;
    // a 변수의 주소값
    printf("a:%p\n", &a);
    // pp1 포인터 변수가 가르키는 a 변수의 주소값
    printf("pp1: %p\n", pp1);
    // pp1 포인터 변수 자체의 주소값
    printf("pp1: %p\n", &pp1);
    // pp1 포인터 변수가 가리키는 a 변수 주소에 저장되어 있는 값
    printf("*pp1: %d\n", *pp1);
    // pp2 포인터 변수가 가르키는 pp1 포인터 주소 값
    printf("pp2: %p\n", pp2);
    // pp2 포인터 변수가 가르키는 pp1, pp1 포인터가 가르키는 a 변수 주소에 저장되어 있는 값
    // pp2 -> pp1 -> a=10
    printf("**pp2: %d\n", **pp2);

    // 이중 포인터 사용하기
    char *pName = NULL;
    MakeName(&pName);
    printf("pName : %s\n", pName);
    if (pName != NULL) {
        free(pName);
    }

    // 포인터 변수와 레퍼런스 변수의 차이
    int  num  = 12345;
    int *pInt = NULL;
    pInt      = &num;
    // int &refer = NULL;	// 레퍼런스변수는 NULL 초기화 할 수 없다.(항상 NULL 아닌 값을 가져야
    // 한다.)
    int &refer = num;
    int  num2  = num;
    printf("num:%d pInt:%p *pInt:%d &refer:%p refer:%d num2:%d\n", num, pInt, *pInt, &refer, refer,
           num2);
    num = 6789;
    printf("num:%d pInt:%p *pInt:%d &refer:%p refer:%d num2:%d\n", num, pInt, *pInt, &refer, refer,
           num2);

    return 0;
}
