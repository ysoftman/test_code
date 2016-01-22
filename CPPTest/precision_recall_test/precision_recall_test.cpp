////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Precision : �츮���� ���ڸ� ��Ȯ��, ����� �󸶳� ��Ȯ������ ��Ÿ����.
// Recall : �츮���� ���ڸ� ������, ����� ������ �󸶳� ���� ���ԵǾ� �ִ����� ��Ÿ����.
// A : ���� ����
// R : ��� ����
// C : ���� ����
// Precision = C / R
// Recall = C / A
// ��)
// ���� = �����ٶ󸶹ٻ������ (A = 10)
// ��� = �����ٶ󸶹� (R = 6 , C = 4)
// Precision = 4 / 6 = 0.66 (66%)
// Recall = 4 / 10 = 0.4 (40%)
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>

int main()
{
	int nA = 0;
	int nR = 0;
	int nC = 0;
	float fPrecision = 0.0f;
	float fRecall = 0.0f;

	char *szAnswer = "�����ٶ󸶹ٻ������";
	char *szResult = "�����ٶ󸶹�";
	printf("szAnswer = %s\n", szAnswer);
	printf("szResult = %s\n", szResult);
	
	nA = strlen(szAnswer);
	nR = strlen(szResult);
	for (int i=0; i<nR; i+=2)
	{
		if (i < nA)
		{
			if (szResult[i] == szAnswer[i] &&
				szResult[i+1] == szAnswer[i+1])
			{
				++nC;
			}
		}
	}
	nA /= 2;
	nR /= 2;
	fPrecision = (float)nC / (float)nR;
	fRecall = (float)nC / (float)nA;
	printf("fPrecision = %d / %d = %.2f\n", nC, nR, fPrecision);
	printf("fRecall = %d / %d = %.2f\n", nC, nA, fRecall);
	return 0;
}


