////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Swap �����
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �ӽ� ������ �̿��� swap ���
void swap1(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

// ���� ���� swap ���
void swap2(int *a, int *b)
{
	// a,b������ XOR �� ����ϰ� �Ǹ� 0���� �ʱ�ȭ �ǹ�����.
	if (*a != *b)
	{
		*b = *a^*b;
		*a = *a^*b;
		*b = *a^*b;
	}
}

// ���� ���� ����� �����ϰ� ������ ���� �� �� �ִ�.
#define swap3(a, b)   ((a)^=(b)^=(a)^=(b));

void main()
{
	int a = 10, b = 20;
	swap1(&a, &b);
	printf("a = %d, b = %d\n", a, b);
	swap2(&a, &b);
	printf("a = %d, b = %d\n", a, b);
	swap3(a, b);
	printf("a = %d, b = %d\n", a, b);
}


