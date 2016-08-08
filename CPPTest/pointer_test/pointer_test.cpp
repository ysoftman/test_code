////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ������ �׽�Ʈ
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// �޸� �Ҵ����� �ּҸ� caller �� �����Ϳ��� �������ֱ� ���� ���������� ���
void MakeName(char **pName)
{
	*pName = (char*)malloc(100);
	memset(*pName, 0, 100);
	// �����쿡���� ��� �� �� �־� �ּ� ó��
	// strncpy_s(*pName, 100, "ysoftman", strlen("ysoftman"));
	strncpy(*pName, "ysoftman", strlen("ysoftman"));
}

int main()
{
	int arr[3] = {1,2,3};
	int *ptr;
	ptr = arr;
	// 1���� �迭 �����ͷ� ǥ��
	printf("array[3] : arr[0]=%d, arr[1]=%d, arr[2]=%d\n", arr[0], arr[1], arr[2]);
	printf("*ptr : ptr[0]=%d, ptr[1]=%d, ptr[2]=%d\n", ptr[0], ptr[1], ptr[2]);


	// 2���� �迭 �����ͷ� ǥ��
	int arr2[2][3] = {1,2,3,4,5,6};
	int (*ptr2)[3];
	ptr2 = arr2;
	printf("array2[2][3] : arr2[0][0]=%d, arr2[0][1]=%d, arr2[0][2]=%d, arr2[1][0]=%d, arr2[1][1]=%d, arr2[1][2]=%d\n", arr2[0][0], arr2[0][1], arr2[0][2], arr2[1][0], arr2[1][1], arr2[1][2]);
	printf("(*ptr2)[3] : ptr2[0][0]=%d, ptr2[0][1]=%d, ptr2[0][2]=%d, ptr2[1][0]=%d, ptr2[1][1]=%d, ptr2[1][2]=%d\n", ptr2[0][0], ptr2[0][1], ptr2[0][2], ptr2[1][0], ptr2[1][1], ptr2[1][2]);


	// ���� �����ͷ� 1���� ������ �����ϱ�
	int a = 10;
	int *pp1 = NULL;
	pp1 = &a;
	int **pp2 = NULL;
	pp2 = &pp1;
	// a ������ �ּҰ�
 	printf("a:%p\n", &a);
	// pp1 ������ ������ ����Ű�� a ������ �ּҰ�
	printf("pp1: %p\n", pp1);
	// pp1 ������ ���� ��ü�� �ּҰ�
	printf("pp1: %p\n", &pp1);
	// pp1 ������ ������ ����Ű�� a ���� �ּҿ� ����Ǿ� �ִ� ��
	printf("*pp1: %d\n", *pp1);
	// pp2 ������ ������ ����Ű�� pp1 ������ �ּ� ��
	printf("pp2: %p\n", pp2);
	// pp2 ������ ������ ����Ű�� pp1, pp1 �����Ͱ� ����Ű�� a ���� �ּҿ� ����Ǿ� �ִ� ��
	// pp2 -> pp1 -> a=10
	printf("**pp2: %d\n", **pp2);


	// ���� ������ ����ϱ�
	char *pName = NULL;
	MakeName(&pName);
	printf("pName : %s\n", pName);
	if (pName != NULL)
	{
		free(pName);
	}

	// ������ ������ ���۷��� ������ ����
	int num = 12345;
	int *pInt = NULL;
	pInt = &num;
	//int &refer = NULL;	// ���۷��������� NULL �ʱ�ȭ �� �� ����.(�׻� NULL �ƴ� ���� ������ �Ѵ�.)
	int &refer = num;
	int num2 = num;
	printf("num:%d pInt:%p *pInt:%d &refer:%p refer:%d num2:%d\n", num, pInt, *pInt, &refer, refer, num2);
	num = 6789;
	printf("num:%d pInt:%p *pInt:%d &refer:%p refer:%d num2:%d\n", num, pInt, *pInt, &refer, refer, num2);

	return 0;
}

