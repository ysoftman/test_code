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
    const int *pConst = NULL;   // pConst ���� �������� ����
    int *const pConst2 = &num;  // pConst2 �ּҸ� �������� ����

    printf("&num:%p\n", &num);
    printf("num:%d\n", num);

    pNormal = &num;
    // pNormal �� ����Ű�� num ���� �ּҰ�
    printf("&(pNormal->num):%p\n", pNormal);
    // pNormal �ּ� �� ���
    printf("&(pNormal):%p\n", &pNormal);
    // pNormal �� ����Ű�� num ���� �ּҰ��� ����Ǿ� �ִ� ��
    printf("*(pNormal):%d\n", *pNormal);

    // �Ϲ� ������ ������ ���� ���� �����ϴ�.
    *pNormal = 20;
    printf("*(pNormal):%d\n", *pNormal);

    
    printf("&(pConst):%p\n", pConst);
    pConst = &num;
    // pConst ������ ������ ���� ������ �� ����.
    // ������ pNormal �� num �� ���� �����ؼ� 20 ���� ǥ�õȴ�.
    // *pConst = 30;
    printf("&(pConst):%p\n", pConst);
    printf("*(pConst):%d\n", *pConst);
    

    // pConst2 ������ ������ ������ �� ����.
    // pConst2 = &num;
    // pConst2 ������ ������ ���� ������ �� �ִ�.
    // pConst2 ����� NULL �� �ƴѰ����� �ʱ�ȭ�Ǿ�� �Ѵ�.
    *pConst2 = 30;
    printf("*(pConst2):%d\n", *pConst2);
    // pConst2 �� num2 ������ ���� �����Ͽ���.
    printf("num:%d\n", num);

    return 0;
}
