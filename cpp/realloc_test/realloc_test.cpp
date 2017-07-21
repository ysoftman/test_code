//////////////////////////////////////////////////////////////////////////
// ysoftman
// realloc 테스트
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
	// malloc 으로 할당한경우 초기화되지 않아 memset으로 초기화해야 한다.
	char *pData = (char*)malloc(sizeof(char)*100);
	if (pData != NULL)
	{
		printData(pData, 100);
		memset(pData, 0, sizeof(char)*100);
		printData(pData, 100);
	}


	printf("test2 calloc\n");
	// calloc 으로 할당한경우 0으로 초기화됨
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
	// realloc 으로 메모리 크기를 늘리거나 줄일 수 있고
	// 크기를 늘리는 경우 기존 값을 새 메모리에 복사하고 새 메모리 주소값을 리턴한다.
	// 늘이는 경우 malloc 을 사용하기 때문에 늘어난 부분에대해서는 초기화되어 있지 않다.
	// 줄이는 경우
	printf("pData2(%p)\n", pData2);
	pData2 = (char*)realloc(pData2, sizeof(char)*5);
	printData(pData2, 5);
	printf("pData2(%p)\n", pData2);

	// 늘이는 경우
	printf("pData2(%p)\n", pData2);
	pData2 = (char*)realloc(pData2, sizeof(char)*100);
	printData(pData2, 100);
	printf("pData2(%p)\n", pData2);

	free(pData);
	free(pData2);

	return 0;
}

