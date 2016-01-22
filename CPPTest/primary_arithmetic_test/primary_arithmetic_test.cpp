////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Primary Arithmetic
// �� ���� �������� �ڸ��ø�(�� ������ ���� 10�� ���� ��� carry �߻�)�� �߻� �˷��ֱ�
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

void main()
{
	// �� ���� ���� �ڸ��� �ִ� 10�ڸ��� ����
	int num1[10];
	int num2[10];

	int i1, i2, d1, d2, carry, carrycnt;
	char line[256];
	char *c;
	

	printf("Primary Arithmetic...\n");
	printf("[Input 0 0 to Exit]\n");
	while (1)
	{
		printf("Input Two Num : ");
		// �Էµ� �� ���� �� ���� �� ���� ���� num1�� num2�� ������
		gets(line);
		i1 = 0;
		i2 = 0;
		c = line;
		// ������ �����ϱ�
		while (*c == ' ')
		{
			c++;
		}
		// ù ��° �� �о� ����
		while (*c >= '0' && *c <= '9')
		{
			num1[i1++] = *(c++) - '0';
		}
		// ������ �����ϱ�
		while (*c == ' ')
		{
			c++;
		}
		// �� ��° �� �о� ����
		while (*c >= '0' && *c <= '9')
		{
			num2[i2++] = *(c++) - '0';
		}
		// �ƹ����� �Էµ� ���� ������ ����
		if (num1[0] == 0 && num2[0] == 0)
		{
			printf ("Exit Program...\n");
			break;
		}
		
		carry = 0;
		carrycnt = 0;

		// �� ���� ���� �ڸ� ���� ����
		// �������� �� �迭�� �� ���� �ڸ��̴�.
		i1--;
		i2--;

		while (i1 >= 0 || i2 >= 0)
		{
			// �� ���� ���� �ڸ����� ���� ������
			d1 = (i1 >= 0 ? num1[i1] : 0);
			d2 = (i2 >= 0 ? num2[i2] : 0);
			// ���ؼ� 10�� ������ �߻�
			// ���� �ڸ����� ĳ���� �ö�� �� �ֱ� ������ �׻� �ɸ��� ����ؾ���(���Ѵ�)
			if (d1 + d2 + carry >= 10)
			{
				carry = 1;
				carrycnt++;
			}
			else
			{
				carry = 0;
			}
			i1--;
			i2--;
		}

		// ����ϱ�
		if (carrycnt >= 1)
		{
			printf("%d Carry Operation.\n", carrycnt);
		}
		else
		{
			printf("No Carry Operation.\n");
		}
	} // End of while (1)
}


