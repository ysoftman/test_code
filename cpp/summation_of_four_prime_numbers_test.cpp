// ysoftman
// SummationOfFourPrimeNumbers
// 소수 4 개의 합
// 주어진 정수를 정확하게 소수 4 개의 합으로 표현하기
// 입력 정수 n<=10000000
#include <stdio.h>
#include <math.h>

static long n;
static long sum;
static long selected[4];

// 입력받은 수가 소수인지 아닌지 판단
bool IsPrime(long a)
{
	long i;

	// 0과 1은 소수가 아니다.
	if (a < 2)
	{
		return false;
	}
	for (i = 2; i <= sqrt(double(a)); i++)
	{
		if (a % i == 0)
		{
			return false;
		}
	}

	return true;
}

// n이 8이상인 경우 언제나 해가 존재한다.
bool PrimeSum(int a)
{
	long i;

	if (a < 0)
	{
		if (sum == n)
		{
			return true;
		}
		return false;
	}

	for (i = n - sum - 2 * a; i >= 2; i--)
	{
		if (IsPrime(i))
		{
			selected[a] = i;
			sum += i;
			if (PrimeSum(a - 1))
			{
				return true;
			}
			sum -= i;
		}
	}

	return false;
}

int main()
{
	printf("Summation Of 4 Prime Numbers...\n");
	printf("[Input 0 to Exit]\n");
	while (scanf("%ld", &n))
	{
		if (n == 0)
		{
			printf("Exit Program...\n");
			break;
		}
		sum = 0;
		if (PrimeSum(3))
		{
			printf("= %ld + %ld + %ld + %ld\n", selected[0], selected[1], selected[2], selected[3]);
		}
		// 소수의 4개의 합으로 나타낼수 없는 수일 경우
		else
		{
			printf("Impossible...\n");
		}
	}

	return 0;
}
