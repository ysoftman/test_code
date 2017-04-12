////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Common Permutation
// �ΰ��� ���ڿ��� ���������� ����� �ִ� �κ� ���ڿ� �� ���� �� ���ڿ� ����ϱ�
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>

#define min(x, y) ((x) < (y) ? (x) : (y))

void main()
{
	char *s;
	char str1[100];
	char str2[100];

	unsigned int cnt1[256];
	unsigned int cnt2[256];

	unsigned int i, j;

	printf("Common Permutation\n");

	while (1)
	{	
		printf("\nFirst String (0 to Exit): ");
		scanf("%s", str1);

		if (strcmp(str1, "0") == 0)
		{
			printf("\n\nExit...\n");
			break;
		}

		printf("\nSecond String : ");
		scanf("%s", str2);
		
		// �ʱ�ȭ
		for (i=0; i<256; i++)
		{
			cnt1[i] = cnt2[i] = 0;
		}
		
		for (s=str1; *s; s++)
		{
			cnt1[*s]++;
		}
		for (s=str2; *s; s++)
		{
			cnt2[*s]++;
		}
		
		
		for (i=0; i<256; i++)
		{
			for (j=0; j<min(cnt1[i], cnt2[i]); j++)
			{
				//printf("%d", j);
				putchar((char)i);
			}
		}
		printf("\n");
	}
}


