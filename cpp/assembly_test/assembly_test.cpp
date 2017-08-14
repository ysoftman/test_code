////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// assembly 사용 예제
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

int calc(int num1, int num2, int num3)
{
	// 어셈블리 코드 영역
	__asm
	{
		mov eax, num1
		mov ebx, num2
		add eax, ebx
		add eax, num3
	}
	// eax 값이 리턴되어진다.
}

int main()
{
	printf("result = %d\n", calc(7, 8, 9));
	return 0;
}



