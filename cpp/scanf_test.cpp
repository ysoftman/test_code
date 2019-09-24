// ysoftman
// Visual C++ 6 과 Turbo C 2.0 의 차이
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *a;

	// Visual C++ 6 에서는 메모리를 할당해야 함
	a = (char *)malloc(1);

	scanf("%s", a);
	printf("%s", a);

	free(a);
	return 0;
}
