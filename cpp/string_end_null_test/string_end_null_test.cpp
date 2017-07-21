////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// NULL(\0) 로 문자열을 끝내자
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

int main()
{
	int len = 0;
	char szBuffer[3];
	memset(szBuffer, 0, sizeof(szBuffer));
	len = strlen(szBuffer);

	// 정상적인 문자열
	szBuffer[0] = 'a';
	szBuffer[1] = 'b';
	szBuffer[2] = '\0';
	len = strlen(szBuffer);
	printf("%s = len(%d)\n", szBuffer, len);

	// 문자열이 null 로 끝나지 않아 제대로 문자열을 출력할 수 없고, 길이도 정확하지 않다.
	szBuffer[0] = 'a';
	szBuffer[1] = 'b';
	szBuffer[2] = 'c';
	len = strlen(szBuffer);
	printf("%s = len(%d)\n", szBuffer, len);

	return 0;
}


