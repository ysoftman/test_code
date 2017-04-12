////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// atoi() 만들기
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

void main()
{
	char *pValue = "01020482278";

	int Result = 0;

	// 첫번째부터 0 까지 숫자 하나씩 변환
	while (*pValue != NULL)
	{
		// 전에 변환된 값은 자리수를 올리고 여기에 대상 ASCII ()값 - ASCII 0(48) 을 뺀 값을 더한다.
		Result = (Result*10) + (*pValue - '0');
		pValue++;
	}

	fprintf(stdout, "Result = %d\n", Result);
}

