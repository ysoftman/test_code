////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Fibonacci ���� ���ϱ�
// Fibonacci ����
// 1 1 2 3 5 8 13 21 34 55 89 144 ...
// 1 + 2 = 3, 2 + 3 = 5, ...
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

// Fibonacci �������� n��° ���� ��
// recursion method
int Fibonacci_r(int n)
{
	int result=0;

	if (n <= 0)
	{
		return 0;
	}
	if (n <= 2)
	{
		return 1;
	}
	// n�� 3�̻��϶�
	else
	{
		result = Fibonacci_r(n-2) + Fibonacci_r(n-1);
		if (result <= 0)
		{
			printf("\n%d��° ���� Overflow...");
			return -1;
		}
		return result;
	}
}

// Fibonacci �������� n��° ���� ��
// iteration method
int Fibonacci_i(int n)
{
	int result = 0;
	int temp1 = 1;
	int temp2 = 1;
	int i;
	
	if (n <= 0)
	{
		return 0;
	}
	if (n <= 2)
	{
		return 1;
	}
	// n�� 3�̻��϶�
	else
	{
		// 1 1 2 3 5 8 13 21 34 55 89 144 ...
		for(i=3; i<=n; i++)
		{
			result = temp1 + temp2;
			temp1 = temp2;
			temp2 = result;
			if (result <= 0)
			{
				printf("\n%d��° ���� Overflow...");
				return -1;
			}
		}
		return result;
	}
}

int main()
{
	int num = 0;
	int last_number = 0;

	// �ݺ��� �̿�
	printf("\n[Fibonacci]Input Number : ");
	scanf("%d", &num);
	last_number = Fibonacci_i(num);
	printf("\nIn %d, Fibonacci Number is %d\n", num, last_number);

	// ����Լ� �̿�(ū���� ������ ��� ����� ���� ��������)
	printf("\n[Fibonacci]Input Number : ");
	scanf("%d", &num);
	last_number = Fibonacci_r(num);
	printf("\nIn %d, Fibonacci Number is %d\n", num, last_number);

	return 0;
}


