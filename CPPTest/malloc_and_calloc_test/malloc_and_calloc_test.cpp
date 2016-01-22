////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// malloc() �� calloc() �� ����
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{

	// malloc() �� �̿� �� ��� ���� �޸� �Ҵ縸 �ȴ�.
	int *p1 = (int*)malloc(sizeof(int)*100);
	// memset �� �̿��Ͽ� 0���� �ʱ�ȭ ����� �Ѵ�.
	memset(p1, 0, sizeof(int)*100);

	// calloc() �� �̿��� ��� ���� �Ҵ� �� �ڵ����� 0���� �ʱ�ȭ �����ش�.
	int *p2 = (int*)calloc(100, sizeof(int));

	free(p1);
	free(p2);
}

