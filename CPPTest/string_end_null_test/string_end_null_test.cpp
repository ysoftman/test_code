////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// NULL(\0) �� ���ڿ��� ������
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

void main()
{
	int len = 0;
	char szBuffer[3];
	memset(szBuffer, 0, sizeof(szBuffer));
	len = strlen(szBuffer);

	// �������� ���ڿ�
	szBuffer[0] = 'a';
	szBuffer[1] = 'b';
	szBuffer[2] = '\0';
	len = strlen(szBuffer);
	printf("%s = len(%d)\n", szBuffer, len);

	// ���ڿ��� null �� ������ �ʾ� ����� ���ڿ��� ����� �� ����, ���̵� ��Ȯ���� �ʴ�.
	szBuffer[0] = 'a';
	szBuffer[1] = 'b';
	szBuffer[2] = 'c';
	len = strlen(szBuffer);
	printf("%s = len(%d)\n", szBuffer, len);
}


