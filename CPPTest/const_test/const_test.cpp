// ysoftman
// const �׽�Ʈ
#include <stdio.h>

int main()
{
    const int ConstNum = 1;
    // const �� ������ ���ο� ���� �Ҵ� �� �� ����.
    // a = 2;
    printf("ConstNum=%d\n", ConstNum);


    int num = 10;
    int *pNormal = NULL;
    const int *pConst = NULL;

    pNormal = &num;
    printf("pNormal:%d\n", *pNormal);
    
    pConst = &num;
    printf("pConst:%d\n", *pConst);

    // �Ϲ� ������ ������ ���� ���氡���ϴ�.
    *pNormal = 20;
    printf("pNormal:%d\n", *pNormal);

    // Const ������ ������ ���� ������ �� ����.
    // ������ pNormal �� num �� ���� �����ؼ� �Ȱ��� ���� ǥ�õȴ�.
    // *pConst = 20;
    printf("pConst:%d\n", *pConst);
    
    return 0;
}
