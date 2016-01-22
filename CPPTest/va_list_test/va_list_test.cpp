////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// �������ڸ� ���� printf() �Լ� ����
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdarg.h>

// ... �� �������ڶ��Ѵ�.
void TestPrintf(const char *format, ...)
{
	// va_list �� char* �� ����Ǿ� �ִ�.
	va_list args = NULL;
	// �������� ����Ʈ�� ù��°�� args�� ��ġ��Ų��.
	va_start(args, format);
	// format �� �°� arg ����Ʈ�� ����Ѵ�.
	vfprintf(stdout, format, args);
	// args �� 0 ���� �����Ѵ�.
	va_end(args);
}

void main()
{
	int a=10, b=20;
	char *pTemp="YoonByoungHoon";
	TestPrintf("%d %d %s\n", a, b, pTemp);
}


