// ysoftman
// malloc() 과 calloc() 의 차이
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

	// malloc() 를 이용 할 경우 동적 메모리 할당만 된다.
	int *p1 = (int *)malloc(sizeof(int) * 100);
	// memset 을 이용하여 0으로 초기화 해줘야 한다.
	memset(p1, 0, sizeof(int) * 100);

	// calloc() 를 이용할 경우 동적 할당 후 자동으로 0으로 초기화 시켜준다.
	int *p2 = (int *)calloc(100, sizeof(int));

	free(p1);
	free(p2);

	return 0;
}
