// ysoftman
// 배열 초기화 하지 않았을 경우
#include <stdio.h>

int main()
{
	int a[10];

	int i;

	for (i = 0; i < 10; i++)
	{
		//a[i] = 0;
		printf("%d\n", a[i]);
	}

	return 0;
}
