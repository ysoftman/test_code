//////////////////////////////////////////////////////////////////////////
// ysoftman
// realloc �׽�Ʈ
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>	// malloc calloc realloc free
#include <string.h>	// memset


void printData(char *pData, int size)
{
	for (int i=0;i<size;i++)
	{
		printf("%c", pData[i]);
	}
	printf("\n");
}
int main()
{
	printf("test1 malloc\n");
	// malloc ���� �Ҵ��Ѱ�� �ʱ�ȭ���� �ʾ� memset���� �ʱ�ȭ�ؾ� �Ѵ�.
	char *pData = (char*)malloc(sizeof(char)*100);
	if (pData != NULL)
	{
		printData(pData, 100);
		memset(pData, 0, sizeof(char)*100);
		printData(pData, 100);
	}


	printf("test2 calloc\n");
	// calloc ���� �Ҵ��Ѱ�� 0���� �ʱ�ȭ��
	char *pData2 = (char*)calloc(100, sizeof(char));
	if (pData2 != NULL)
	{
		printData(pData2, 100);
	}

	printf("test3 realloc\n");

	for (int i=0;i<100;i++)
	{
		pData2[i] = 'A';
	}
	printData(pData2, 100);
	// realloc ���� �޸� ũ�⸦ �ø��ų� ���� �� �ְ�
	// ũ�⸦ �ø��� ��� ���� ���� �� �޸𸮿� �����ϰ� �� �޸� �ּҰ��� �����Ѵ�.
	// ���̴� ��� malloc �� ����ϱ� ������ �þ �κп����ؼ��� �ʱ�ȭ�Ǿ� ���� �ʴ�.
	// ���̴� ���
	printf("pData2(%p)\n", pData2);
	pData2 = (char*)realloc(pData2, sizeof(char)*5);
	printData(pData2, 5);
	printf("pData2(%p)\n", pData2);

	// ���̴� ���
	printf("pData2(%p)\n", pData2);
	pData2 = (char*)realloc(pData2, sizeof(char)*100);
	printData(pData2, 100);
	printf("pData2(%p)\n", pData2);

	free(pData);
	free(pData2);

	return 0;
}

