// ysoftman
// OS 환경에 따른 Data Type Range 알아보기
//
//DataModel		char	short	int		long	long long		pointers/size_t		OS(64bit)
//LP64			8		16		32		64		X				64					Unix, Solaris, Linux, Mac OS
//LLP64			8		16		32		32		64				64					MS-Windows
//ILP64			8		16		64		64		X				64
//
//LP64 는 long 과 pointer 만 64bit 라는 표시
//LLP64 는 long long 과 pointer 만 64bit 라는 표시
//ILP64 는 int 와 long 과 pointer 만 64bit 라는 표시
#include <stdio.h>

int main()
{
	printf("sizeof(bool) = %ld\n", sizeof(bool));
	printf("sizeof(char) = %ld\n", sizeof(char));
	printf("sizeof(short) = %ld\n", sizeof(short));
	printf("sizeof(wchar_t) = %ld\n", sizeof(wchar_t));
	printf("sizeof(int) = %ld\n", sizeof(int));
	printf("sizeof(float) = %ld\n", sizeof(float));
	printf("sizeof(long) = %ld\n", sizeof(long));
	printf("sizeof(long long) = %ld\n", sizeof(long long));
	printf("sizeof(double) = %ld\n", sizeof(double));
	return 0;
}
