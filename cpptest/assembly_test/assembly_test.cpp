////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// assembly ��� ����
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

int calc(int num1, int num2, int num3)
{
	// ����� �ڵ� ����
	__asm
	{
		mov eax, num1
		mov ebx, num2
		add eax, ebx
		add eax, num3
	}
	// eax ���� ���ϵǾ�����.
}

void main()
{
	printf("result = %d\n", calc(7, 8, 9));
}



