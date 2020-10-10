// ysoftman
// Fibonacci 수열 구하기
// Fibonacci 수열
// 1 1 2 3 5 8 13 21 34 55 89 144 ...
// 1 + 2 = 3, 2 + 3 = 5, ...
#include <stdio.h>

// Fibonacci 수열에서 n번째 항의 값
// recursion method
int fibonacci_recursive(int n)
{
	int result = 0;

	if (n <= 0)
	{
		return 0;
	}
	if (n <= 2)
	{
		return 1;
	}
	result = fibonacci_recursive(n - 2) + fibonacci_recursive(n - 1);
	if (result <= 0)
	{
		printf("stack overflow...\n");
		return -1;
	}
	return result;
}

// Fibonacci 수열에서 n번째 항의 값
// iteration method
int fibonacci_iteration(int n)
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
	// 1 1 2 3 5 8 13 21 34 55 89 144 ...
	for (i = 3; i <= n; i++)
	{
		result = temp1 + temp2;
		temp1 = temp2;
		temp2 = result;
		if (result <= 0)
		{
			printf("stack overflow...\n");
			return -1;
		}
	}
	return result;
}

int main()
{
	int num = 0;
	int last_number = 0;

	printf("[Fibonacci]Input Number : ");
	scanf("%d", &num);

	// 반복문 이용
	last_number = fibonacci_iteration(num);
	printf("[iteration] In %d, Fibonacci Number is %d\n", num, last_number);

	// 재귀함수 이용(큰수로 갈수록 계산 결과가 점점 느려진다)
	last_number = fibonacci_recursive(num);
	printf("[recursive] In %d, Fibonacci Number is %d\n", num, last_number);

	return 0;
}
