////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ������ �Է� �޾� ���(1 ~ 9 ���ڸ�)
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <conio.h>

void main()
{
	
	int num1, num2;
	char ch;
	
	// ����� �� �Է� �ޱ�
	while(1)
	{
		printf("\nInput Number1   :  ");
		if ((ch = getchar()) != 0)
		{
			if (ch >= 49 && ch <= 57)
			{
				printf("\nInput number 1 is %d\n", ch-48);
				num1 = ch-48;
				break;
			}
			else
			{
				printf("\nInput number1 Again\n");
			}
		}
	}

	for (num2 = 1; num2 <= 10; num2++)
	{
		printf("\n %2d * %2d = %2d\n", num1, num2, num1*num2);
	}
}

