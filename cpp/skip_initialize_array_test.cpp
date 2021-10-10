// ysoftman
// 배열 초기화 하지 않았을 경우
#include <stdio.h>

void print_array(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("[%d]:%d\n", i, arr[i]);
	}
	printf("-----\n");
}

int main()
{
	const int size = 100;
	int a[size];
	print_array(a, size);
	// int b[size] = {};  // invalid C but valid C++ way to zero-out a block-scope array
	int b[size] = {0}; // valid C and C++ way to zero-out a block-scope array
	print_array(b, size);

	return 0;
}
