////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// SummationOfFourPrimeNumbers
// �Ҽ� 4 ���� ��
// �־��� ������ ��Ȯ�ϰ� �Ҽ� 4 ���� ������ ǥ���ϱ�
// �Է� ���� n<=10000000
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <math.h>

static long n;
static long sum;
static long selected[4];

// �Է¹��� ���� �Ҽ����� �ƴ��� �Ǵ�
bool IsPrime(long a)
{
	long i;

	// 0�� 1�� �Ҽ��� �ƴϴ�.
	if (a<2)
	{
		return false;
	}
	for (i=2; i<=sqrt(double(a)); i++)
	{
		if (a%i == 0)
		{
			return false;
		}
	}

	return true;
}

// n�� 8�̻��� ��� ������ �ذ� �����Ѵ�.
bool PrimeSum(int a)
{
	long i;

	if (a<0)
	{
		if (sum = n)
		{
			return true;
		}
		return false;
	}

	for (i=n-sum-2*a; i>=2; i--)
	{
		if (IsPrime(i))
		{
			selected[a] = i;
			sum += i;
			if (PrimeSum(a-1))
			{
				return true;
			}
			sum -= i;
		}
	}

	return false;
}

void main()
{
	printf("Summation Of 4 Prime Numbers...\n");
	printf("[Input 0 to Exit]\n");
	while (scanf("%ld", &n))
	{
		if (n == 0)
		{
			printf ("Exit Program...\n");
			break;
		}
		sum = 0;
		if (PrimeSum(3))
		{
			printf("= %ld + %ld + %ld + %ld\n", selected[0], selected[1], selected[2], selected[3]);
		}
		// �Ҽ��� 4���� ������ ��Ÿ���� ���� ���� ���
		else
		{
			printf("Impossible...\n");
		}
	}
}


