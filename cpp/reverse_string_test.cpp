// ysoftman
// Reverse String
// 문자열 뒤집기
#include <stdio.h>
#include <string.h> // strlen()함수 사용

int main()
{
	int i = 0, n = 0;
	char ch[50];
	char result_str[50];

	// 영문
	printf("\nInput String[English] to Reverse :  ");
	scanf("%s", ch);

	n = strlen(ch);

	for (i = 0; i < n; i++)
	{
		result_str[i] = ch[n - i - 1];

		// 문장의 마지막에 끝을 표시
		if (i == n - 1)
		{
			// NULL, 0, \0 다 같은 의미로 쓰임
			result_str[i + 1] = NULL;
		}
	}

	printf("\n[string length : %d]\n%s -> %s\n", n, ch, result_str);

	// 한글
	printf("\nInput String[Korean] to Reverse :  ");
	scanf("%s", ch);

	n = strlen(ch);

	for (i = 0; i < n; i += 2)
	{

		result_str[i] = ch[n - i - 2];
		result_str[i + 1] = ch[n - i - 1];

		// 문장의 마지막에 끝을 표시
		if (i == n - 2)
		{
			// NULL, 0, \0 다 같은 의미로 쓰임
			result_str[i + 2] = NULL;
		}
	}

	printf("\n[string length : %d]\n%s -> %s\n", n, ch, result_str);

	return 0;
}
