////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 두 개의 수열(sequence) X, Y가 주어졌을 때  X와 Y의 
// 가장 긴 공통 부분 수열(longest common subsequence)을 찾는 문제
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>

#define MAX 1000

char X[MAX];
char Y[MAX];
int b[MAX][MAX];
int c[MAX][MAX];
 
int i, j, m, n;

int LCSlength();
void printLCS(int i, int j);

int main()
{
	printf("Input Two String : ");
	scanf("%s", X);
	scanf("%s", Y);

	printf("\nLongest Common Subsequence (Length) %d\n", LCSlength());
	printf("\nLongest Common Subsequence (String) ");
	printLCS(m, n);
	printf("\n");

	return 0;
}

int LCSlength()
{
	m = strlen(X);
	n = strlen(Y);
	
	for (i=1;i<=m;i++)
	{
		c[i][0]=0;
	}

	for (j=0;j<=n;j++)
	{
		c[0][j]=0;
	}
	
	for (i=1;i<=m;i++)
	{
		for (j=1;j<=n;j++)
		{
			if (X[i-1]==Y[j-1])
			{
				c[i][j]=c[i-1][j-1]+1;
				b[i][j]=1;
			}
			else if (c[i-1][j]>=c[i][j-1])
			{
				c[i][j]=c[i-1][j];
				b[i][j]=2;
			}
			else
			{
				c[i][j]=c[i][j-1];
				b[i][j]=3;
			}
		}
	}
	return c[m][n];
}

void printLCS(int i, int j)
{
	if (i==0 || j==0) 
	{
		return;
	}
	
	if (b[i][j]==1)
	{
		printLCS(i-1,j-1);
		printf("%c",X[i-1]);
	}
	else if (b[i][j]==2)
	{
		printLCS(i-1,j);
	}
	else
	{
		printLCS(i,j-1);
	}
}


