////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Levenshtein Distance �˰������� �� ������ ���̸� distance �� �������ش�.
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>

#define MIN(a, b)   ((a>b) ? b : a)
#define MAX_STR_LEN 20

int LevenshteinDistance(char* pInStr, char* pDicStr)
{
	char pStr1[MAX_STR_LEN];
	char pStr2[MAX_STR_LEN];
	memset(pStr1, 0, sizeof(char)*MAX_STR_LEN);
	memset(pStr2, 0, sizeof(char)*MAX_STR_LEN);

	// 0��°�� �ǹ� ���� ���ڸ� �߰��� �ش�.
	strcat(pStr1, "_");
	strcat(pStr2, "_");

	strcat(pStr1, pInStr);
	strcat(pStr2, pDicStr);

	int m = strlen(pStr1);
	int n = strlen(pStr2);

	int i = 0, j = 0;
	int cost = 0, distance = 0;

	// distace �� ����� m x n matrix
	int d[MAX_STR_LEN][MAX_STR_LEN];
	memset(d, 0, sizeof(char)*MAX_STR_LEN*MAX_STR_LEN);

	// ù��° ��� ���� �ʱ�ȭ�Ѵ�.
	for (i=0; i<m; i++)
	{
		d[0][i] = i;
	}
	for (j=0; j<n; j++)
	{
		d[j][0] = j;
	}

	for (j=1; j<n; j++)
	{
		for (i=1; i<m; i++)
		{
			if (pStr1[i] == pStr2[j]) cost = 0;
			else cost = 1; // replace cost

			// ���缿���� ����, ����, ������ �� �� �߿��� ���� ���� ���� �����Ѵ�.
			d[j][i] = MIN(d[j][i-1]+1, // insertion
					MIN(d[j-1][i]+1, // deletion
					d[j-1][i-1]+cost)); // substitution(replace)
			// ���� distance ��
			distance = d[j][i];
		}
	}

	// ����� �Ǿ����� Ȯ���ϱ� ���ؼ� m x n matrix �� ���¸� ����.
	// kitten �� sitting ���� replace cost=1��� 3�� ���� distance �� �ȴ�.
	//    k i t t e n 
	//  0 1 2 3 4 5 6 
	//s 1 1 2 3 4 5 6 
	//i 2 2 1 2 3 4 5 
	//t 3 3 2 1 2 3 4 
	//t 4 4 3 2 1 2 3 
	//i 5 5 4 3 2 2 3 
	//n 6 6 5 4 3 3 2 
	//g 7 7 6 5 4 4 3 <- distance
	for (j=0; j<n; j++)
	{
		if (j==0) 
		{
			for (i=0; i<m; i++)
			{
				if (i==0) fprintf(stderr, "  ");
				fprintf(stderr, "%c ", pStr1[i]);
			}
			fprintf(stderr, "\n");
		}

		fprintf(stderr, "%c ", pStr2[j]);
		for (i=0; i<m; i++)
		{
			fprintf(stderr, "%d ", d[j][i]);
		}
		fprintf(stderr, "\n");
	}


	return distance;
}

int main()
{
	// LevenshteinDistance �׽�Ʈ...
	LevenshteinDistance("kitten", "sitting");
	LevenshteinDistance("Saturday", "Sunday");
}


