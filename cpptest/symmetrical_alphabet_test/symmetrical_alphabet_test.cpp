////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ��Ī�Ǵ� ���ĺ� ���(A���� �Էµ� n��°����)
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

int main()
{ 
	int i, j, k,l;


	// �˹ٺ� ��Ī(����)��� �����
	for(i=1; i<=26*2; i++)
	{
		k=0;
		if(i>=27)
			l=27-i%26;
		else
			l=i;
		if(l==27)
			l=1;
		
		for(j=1;j<=26*2; j++)
		{
			if(j<=l) 
				printf("%c", 'A' + k++);
			else if (52-j<l)
				printf("%c", 'A' + --k);
			else
				printf(" ");
		}
		printf("\n");
	}

	// �Է��� ���� ��ŭ ��Ī ��� �����
	int n;
	printf("Input Numbe(<=26) : ");
	scanf("%d", &n);
	for (i=1; i<=n*2; i++)
	{
		k=0;

		if (i >= n+1)
		{
			l = (n+1)-(i%n);
		}
		else
		{
			l = i;
		}
		
		// �߱���� ��µǾ��� ��
		if (l == (n+1))
		{
			l = 1;
		}

		for (j=1; j<=n*2; j++)
		{
			if (j <= l)
			{
				printf("%c", 'A' + k++);
			}
			else if ((n*2)-j < l)
			{
				printf("%c", 'A' + --k);
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
	return 0;
}



