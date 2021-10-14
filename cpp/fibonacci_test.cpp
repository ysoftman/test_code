// ysoftman
// Fibonacci 수열 구하기
// Fibonacci 수열
// 1 1 2 3 5 8 13 21 34 55 89 144 ...
// 1 + 2 = 3, 2 + 3 = 5, ...
#include <stdio.h>

int debug_count = 0; // 반복 횟수 파악을 위해

// Fibonacci 수열에서 n번째 항의 값
// 재귀함수 이용(큰수로 갈수록 계산 결과가 점점 느려진다) O(2^n)
int fibonacci_recursive(int n)
{
	debug_count++;
	int result = 0;
	if (n <= 0) // 0 번째 피보나치가 입력으로 들어온 경우에 대한 예외 처리
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

// 재귀함수 이용(이전에 계산된 값을 저장해 중복 계산을 막는다.) 2*N => 시간복잡도 표시에 상수는 제외 해서 => O(N)
int fibonacci_recursive_with_array(int n, int *arr)
{
	debug_count++;
	int result = 0;
	if (n <= 0) // 0 번째 피보나치가 입력으로 들어온 경우에 대한 예외 처리
	{
		return 0;
	}
	if (n <= 2)
	{
		return 1;
	}
	if (arr[n] > 0)
	{
		return arr[n];
	}
	result = fibonacci_recursive_with_array(n - 1, arr) + fibonacci_recursive_with_array(n - 2, arr);
	arr[n] = result;
	return result;
}

// Fibonacci 수열에서 n번째 항의 값
// 반복문 이용 O(N)
int fibonacci_iteration(int n)
{
	debug_count++;
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
		debug_count++;
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
	int result = 0;
	printf("[Fibonacci]Input Number : ");
	scanf("%d", &num);

	debug_count = 0;
	result = fibonacci_iteration(num);
	printf("[iteration] (debug_count:%d) In %d, Fibonacci Number is %d\n", debug_count, num, result);

	debug_count = 0;
	result = fibonacci_recursive(num);
	printf("[recursive] (debug_count:%d) In %d, Fibonacci Number is %d\n", debug_count, num, result);

	int *arr = new int[num];
	debug_count = 0;
	result = fibonacci_recursive_with_array(num, arr);
	printf("[recursive_with_array] (debug_count:%d) In %d, Fibonacci Number is %d\n", debug_count, num, result);

	return 0;
}
