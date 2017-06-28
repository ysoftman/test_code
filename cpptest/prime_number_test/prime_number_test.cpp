////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// PrimeNumber(소수) 구하기
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

void PrimeNumber(int);

void main()
{
	int num=0;

	printf("Input Number : ");
	scanf("%d", &num);

	PrimeNumber(num);
}

// 소수 구하는 함수
void PrimeNumber(int num)
{
	int i, j;
	int isPrime;

	if (num < 2)
	{
		printf("Wrong Number...\n");
		exit(1);
	}

	for (i=2; i<=num; i++)
	{
		isPrime = 1;
		for (j=2; j<=i-1; j++)
		{
			if (i%j == 0)
			{
				isPrime = 0;
				printf("%3d is not PrimeNumber(devide by %d ...etc)\n", i, j);
				break;
			}
		}
		if (isPrime == 1)
		{
			printf("%3d is PrimeNumber\n", i);
		}
	}
}

