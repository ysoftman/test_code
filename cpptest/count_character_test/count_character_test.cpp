////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Count Character - 문자 'a' 세기 프로그램
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>	// strlen()함수 사용

void main()
{
	char str[100];
	int n = 0;
	int i = 0;
	int cnt = 0;

	printf("\nInput String To Count Character 'a' :  ");
	scanf("%s", str);

	n = strlen(str);

	for (i=0; i<n; i++)
	{
		if (str[i] == 'a')
		{
			cnt++;
		}
	}

	printf("\nNumber of Character 'a' is  %2d\n", cnt);
}

