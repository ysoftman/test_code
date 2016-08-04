// ysoftman
// const 테스트
#include <stdio.h>

int main()
{
    const int ConstNum = 1;
    // const 형 변수에 새로운 값을 할달 할 수 없다.
    // a = 2;
    printf("ConstNum=%d\n", ConstNum);


    int num = 10;
    int *pNormal = NULL;
    const int *pConst = NULL;

    pNormal = &num;
    printf("pNormal:%d\n", *pNormal);
    
    pConst = &num;
    printf("pConst:%d\n", *pConst);

    // 일반 포인터 변수의 값은 변경가능하다.
    *pNormal = 20;
    printf("pNormal:%d\n", *pNormal);

    // Const 포인터 변수의 값은 변경할 수 없다.
    // 하지만 pNormal 이 num 의 값을 변경해서 똑같은 값이 표시된다.
    // *pConst = 20;
    printf("pConst:%d\n", *pConst);
    
    return 0;
}
