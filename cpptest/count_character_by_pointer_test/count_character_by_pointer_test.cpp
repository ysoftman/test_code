////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 포인터를 이용한 문자열 길이 카운트
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

// 문자열 길이 카운트
int GetByteLength(char *pByte)
{
	int cnt = 0;
	while ((*pByte) != NULL)
	{
		cnt++;
		pByte++;
	}
	return cnt;
}

int main()
{
	char szData[50] = "ABCDEFGHIJ";
	char *pMunja = szData;
	int Len = GetByteLength(pMunja);
	fprintf(stderr, "Munja = %s\nLen = %d\n", pMunja, Len);
	return 0;
}

