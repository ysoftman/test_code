////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ASCII �ڵ� ���
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	// ASCII ���
	int number;
	for (number = 0; number < 128; number++)
	{
		printf("%d -> %c\n", number, number);
	}
}
