////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// �����͸� �̿��� ���ڿ� ���� ī��Ʈ
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

// ���ڿ� ���� ī��Ʈ
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

void main()
{
	char *pMunja = "ABCDEFGHIJ";
	int Len = GetByteLength(pMunja);
	fprintf(stderr, "Munja = %s\nLen = %d\n", pMunja, Len);
}

