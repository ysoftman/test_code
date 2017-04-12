////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// OS ȯ�濡 ���� Data Type Range �˾ƺ���
//
//DataModel		char	short	int		long	long long		pointers/size_t		OS(64bit)
//LP64			8		16		32		64		X				64					Unix, Solaris, Linux, Mac OS
//LLP64			8		16		32		32		64				64					MS-Windows
//ILP64			8		16		64		64		X				64
//
//LP64 �� long �� pointer �� 64bit ��� ǥ��
//LLP64 �� long long �� pointer �� 64bit ��� ǥ��
//ILP64 �� int �� long �� pointer �� 64bit ��� ǥ��
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

int main()
{
	printf("sizeof(char) = %d\n", sizeof(char));
	printf("sizeof(short) = %d\n", sizeof(short));
	printf("sizeof(wchar_t) = %d\n", sizeof(wchar_t));
	printf("sizeof(int) = %d\n", sizeof(int));
	printf("sizeof(float) = %d\n", sizeof(float));
	printf("sizeof(long) = %d\n", sizeof(long));
	printf("sizeof(long long) = %d\n", sizeof(long long));
	printf("sizeof(double) = %d\n", sizeof(double));
	return 0;
}

