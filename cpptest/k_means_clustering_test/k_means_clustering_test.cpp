////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// K-Means Clustering
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN(a,b) a > b ? b : a

const int MAX_SET = 10;

struct DOT{
	int x;			// x ��ǥ
	int y;			// y ��ǥ
	int group;		// ���� ���� ���� �׷�(Ŭ����)
};

bool KMeansClustering(DOT *pInput, int nClass);

int main()
{
	srand((unsigned int)time(NULL));
	DOT *pInput = new DOT[MAX_SET];
	// �Է����� ����� ������ �����ϰ� �����.
	for (int i=0; i<MAX_SET; i++)
	{
		pInput[i].x = rand()%10;
		pInput[i].y = rand()%10;
		pInput[i].group = 0;
		fprintf(stderr, "pInput[%3d] = (%3d,%3d)\n", i, pInput[i].x, pInput[i].y);
	}
	// ����ȭ ��Ų��.
	KMeansClustering(pInput, 3);

	delete[] pInput;
}

bool KMeansClustering(DOT *pInput, int nClass)
{
	int i=0, j=0, PreDist=0, CurDist=0, Cnt=0;
	bool bFind = false;

	DOT *pCenterDot = new DOT[nClass];
	// �ʱ��� �� Ŭ������ ��ǥ�� ������ �Է� ���÷� ���� �����Ѵ�.
	for (int i=0; i<nClass; i++)
	{
		pCenterDot[i].x = pInput[i].x;
		pCenterDot[i].y = pInput[i].y;
		pCenterDot[i].group = 0;
	}

	// �ݺ��� ������ �ٽ� ����ϱ� ���ؼ�
	DOT *pNewCenterDot = new DOT[nClass];
	memset(pNewCenterDot, 0, sizeof(DOT)*nClass);

	while (true)
	{
		// ���� ���� �� ���
		for (j=0; j<nClass; j++)
		{
			fprintf(stderr, "pCenterDot[%3d] = (%3d,%3d)\n", j, pCenterDot[j].x, pCenterDot[j].y);
		}
		// �־��� �������� �Ÿ��� ������� �Էµ����͸� classify
		for (i=0; i<MAX_SET; i++)
		{
			PreDist = 99999;
			for (j=0; j<nClass; j++)
			{
				// �Էµ����� ������ ���� �������� ���� ���� �� ���� ���� Ŭ������ �����Ѵ�.
				CurDist = 0;
				CurDist += abs(pCenterDot[j].x-pInput[i].x) + abs(pCenterDot[j].y-pInput[i].y);
				if (PreDist > CurDist)
				{
					pInput[i].group = j;
				}
				PreDist = MIN(PreDist,CurDist);
			}
			// ���� �Էµ����Ͱ� � Ŭ������ �з��Ǿ����� ���
			//fprintf(stderr, "pInput[%3d] = (%3d,%3d) ==> class%3d = (%3d,%3d)\n", i, pInput[i].x, pInput[i].y, pInput[i].group, pCenterDot[pInput[i].group].x, pCenterDot[pInput[i].group].y);
		}
		// classify �� �����͵�� �ٽ� ������ ����Ѵ�.
		memset(pNewCenterDot, 0, sizeof(DOT)*nClass);
		for (j=0; j<nClass; j++)
		{
			Cnt = 0;
			for (i=0; i<MAX_SET; i++)
			{
				if (j == pInput[i].group)
				{
					pNewCenterDot[j].x += pInput[i].x;
					pNewCenterDot[j].y += pInput[i].y;
					Cnt++;
				}
			}
			if (Cnt == 0)
			{
				fprintf(stderr, "error, divied by zero...\n");
				return false;
			}
			pNewCenterDot[j].x /= Cnt;
			pNewCenterDot[j].y /= Cnt;
		}

		// ���� ������ ���Ӱ� ���� ������ ������ ����������.
		for (j=0; j<nClass; j++)
		{
			if (pNewCenterDot[j].x == pCenterDot[j].x && pNewCenterDot[j].y == pCenterDot[j].y)
			{
				bFind = true;
			}
			else
			{
				bFind = false;
				break;
			}
		}
		if (bFind)
		{
			break;
		}

		// ���Ӱ� ���� ������ �ݿ��Ѵ�.
		for (j=0; j<nClass; j++)
		{
			pCenterDot[j].x = pNewCenterDot[j].x;
			pCenterDot[j].y = pNewCenterDot[j].y;
		}
	}

	delete[] pCenterDot;
	delete[] pNewCenterDot;

	return true;
}

