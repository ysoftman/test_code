////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Precision : 우리말로 하자면 정확률, 결과가 얼마나 정확한지를 나타낸다.
// Recall : 우리말로 하자면 재현률, 결과에 정답이 얼마나 많이 포함되어 있는지를 나타낸다.
// A : 정답 개수
// R : 결과 개수
// C : 맞은 개수
// Precision = C / R
// Recall = C / A
// 예)
// 정답 = 가나다라마바사아자차 (A = 10)
// 결과 = 갸나다라마뱌 (R = 6 , C = 4)
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

	char *szAnswer = "가나다라마바사아자차";
	char *szResult = "갸나다라마뱌";
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


