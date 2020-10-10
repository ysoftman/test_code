// ysoftman
// Swap 방법들
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 임시 변수를 이용한 swap 방법
void swap1(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

// 변수 없이 swap 방법
void swap2(int *a, int *b)
{
	// a,b같을때 XOR 을 사용하게 되면 0으로 초기화 되버린다.
	if (*a != *b)
	{
		*b = *a ^ *b;
		*a = *a ^ *b;
		*b = *a ^ *b;
	}
}

// 변수 없는 방법을 간단하게 정의해 버릴 수 도 있다.
#define swap3(a, b) ((a) ^= (b) ^= (a) ^= (b));

int main()
{
	int a = 10, b = 20;
	swap1(&a, &b);
	printf("a = %d, b = %d\n", a, b);
	swap2(&a, &b);
	printf("a = %d, b = %d\n", a, b);
	swap3(a, b);
	printf("a = %d, b = %d\n", a, b);

	return 0;
}
