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
	strncpy_s(*pName, 100, "ysoftman", strlen("ysoftman"));
}

void main()
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
	//int &refer = NULL;	// ���۷��������� NULL �ʱ�ȭ �� �� ����.
	int &refer = num;
	printf("num:%d pInt:%d *pInt:%d &refer:%d refer:%d\n", num, pInt, *pInt, &refer, refer);
	num = 6789;
	printf("num:%d pInt:%d *pInt:%d &refer:%d refer:%d\n", num, pInt, *pInt, &refer, refer);

}

