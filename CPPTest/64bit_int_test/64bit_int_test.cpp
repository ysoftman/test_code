////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 64bit int �� ���
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

void main()
{
	int a			= 1000000000;
	__int64 b		= 10000000000;
	long long c		= 10000000000;
	__time32_t d	= 1000000000;
	__time64_t e	= 10000000000;

	// __int64 , long long�� 64bit(8byte) �ڷ������� %I64d �� %lld �������� ����ؾ� �Ѵ�.
	printf("int         %%d: %d %%I32d: %I32d %%I64d: %I64d %%lld: %lld\n", a, a, a, a);
	printf("__int64     %%d: %d %%I32d: %I32d %%I64d: %I64d %%lld: %lld\n", b, b, b, b);
	printf("long long   %%d: %d %%I32d: %I32d %%I64d: %I64d %%lld: %lld\n", b, c, c, c);
	printf("__time32_t  %%d: %d %%I32d: %I32d %%I64d: %I64d %%lld: %lld\n", d, d, d, d);
	printf("__time64_t  %%d: %d %%I32d: %I32d %%I64d: %I64d %%lld: %lld\n", e, e, e, e);

}

