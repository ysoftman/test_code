// ysoftman
// 64bit int 값 출력
#include <stdio.h>

int main()
{
#if defined(_WIN32) || defined(_WIN64)
	int a = 1000000000;
	__int64 b = 10000000000;
	long long c = 10000000000;
	__time32_t d = 1000000000;
	__time64_t e = 10000000000;

	// __int64 , long long형 64bit(8byte) 자료형으로 %I64d 나 %lld 형식으로 출력해야 한다.
	printf("int         %%d: %d %%I32d: %I32d %%I64d: %I64d %%lld: %lld\n", a, a, a, a);
	printf("__int64     %%d: %d %%I32d: %I32d %%I64d: %I64d %%lld: %lld\n", b, b, b, b);
	printf("long long   %%d: %d %%I32d: %I32d %%I64d: %I64d %%lld: %lld\n", b, c, c, c);
	printf("__time32_t  %%d: %d %%I32d: %I32d %%I64d: %I64d %%lld: %lld\n", d, d, d, d);
	printf("__time64_t  %%d: %d %%I32d: %I32d %%I64d: %I64d %%lld: %lld\n", e, e, e, e);
#endif
	return 0;
}