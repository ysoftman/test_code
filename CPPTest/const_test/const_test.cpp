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
    const int *pConst = NULL;   // pConst 값을 변경하지 못함
    int *const pConst2 = &num;  // pConst2 주소를 변경하지 못함

    printf("&num:%p\n", &num);
    printf("num:%d\n", num);

    pNormal = &num;
    // pNormal 이 가르키는 num 변수 주소값
    printf("&(pNormal->num):%p\n", pNormal);
    // pNormal 주소 값 출력
    printf("&(pNormal):%p\n", &pNormal);
    // pNormal 이 가르키븐 num 변수 주소값에 저장되어 있는 값
    printf("*(pNormal):%d\n", *pNormal);

    // 일반 포인터 변수의 값은 변경 가능하다.
    *pNormal = 20;
    printf("*(pNormal):%d\n", *pNormal);

    
    printf("&(pConst):%p\n", pConst);
    pConst = &num;
    // pConst 포인터 변수의 값은 변경할 수 없다.
    // 하지만 pNormal 이 num 의 값을 변경해서 20 값이 표시된다.
    // *pConst = 30;
    printf("&(pConst):%p\n", pConst);
    printf("*(pConst):%d\n", *pConst);
    

    // pConst2 포인터 변수를 변경할 수 없다.
    // pConst2 = &num;
    // pConst2 포인터 변수의 값은 변경할 수 있다.
    // pConst2 선언시 NULL 이 아닌값으로 초기화되어야 한다.
    *pConst2 = 30;
    printf("*(pConst2):%d\n", *pConst2);
    // pConst2 가 num2 변수의 값을 변경하였다.
    printf("num:%d\n", num);

    return 0;
}
