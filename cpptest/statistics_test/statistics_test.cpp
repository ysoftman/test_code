////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ��� �� ���
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <math.h>

float GetAverage(float* set, int num)
{
	float average = 0.0;
	int i = 0;
	for (i=0; i<num; i++)
	{
		average += set[i];
	}
	//��� (average) : ������ ������ ������ ���� �� 
	average = float(average/num);
	return average;
}

float GetVariance(float* set, int num, float average)
{
	float deviation = 0.0;
	float variance = 0.0;
	int i = 0;
	for (i=0; i<num; i++)
	{
		// ����(deviation) : ��տ��� ������ ���� ������ ����
		deviation = set[i] - average;
		printf("deviation set[%d] = %.2f\n", i, deviation);

		variance += deviation * deviation;
	}
	// �л�(variance) : ������ �������� ���� ������ ���� ��
	variance = float(variance/num);
	return variance;
}

float GetStandardDeviation(float variance)
{
	float sd = 0.0;
	// ǥ������(standard deviation) : �л��� ������
	sd = sqrt(variance);
	return sd;
}

float GetCoVariance(float* setX, float* setY, int num, float averageX, float averageY)
{
	float deviation = 0.0;
	float covariance = 0.0;
	int i = 0;
	for (i=0; i<num; i++)
	{
		covariance += (setX[i] - averageX) * (setY[i] - averageY);
	}
	// ���л�(covariance) : setX�� setY�� ���������� ���� ������ ���� ��
	covariance = float(covariance/num);
	return covariance;
}

// PCC (Pearson Correlation Coefficient) �Ǿ������
// -1 <= PCC <= 1 ������ ������ ��� ���踦 ��Ÿ����.
// 1 �� ����� ���� ���� ������ ������� ��Ÿ����.
// -1 �� ����� ���� �ݴ� ������ ������� ��Ÿ����.
// 0 �� ����� ���� ������� ������ ��Ÿ����.
float GetPCC(float covariance, float sdX, float sdY)
{
	float pcc = 0.0;
	// �Ǿ ������(Pearson Correlation Coefficient) : ���л��� setX�� setY�� ǥ�������� ������ ���� ��
	pcc = covariance/(sdX*sdY);
	return pcc;
}

void main()
{
	float averageX = 0.0;
	float averageY = 0.0;
	float variance = 0.0;
	float sdX = 0.0;
	float sdY = 0.0;
	float covariance = 0.0;
	float pcc = 0.0;
	float setX[4] = {10, 20, 30, 40};
	float setY[4] = {10, 40, 50, 70};
	int i = 0;
	int num = 4;

	printf("setX = { ");
	for (i=0; i<num; i++) printf("%.2f ", setX[i]);
	printf("}\n");

	averageX = GetAverage(setX, num);
	printf("average = %.2f\n", averageX);
	variance = GetVariance(setX, num, averageX);
	printf("variance = %.2f\n", variance);
	sdX = GetStandardDeviation(variance);
	printf("standard deviation = %.2f\n", sdX);

	printf("\n");

	printf("setY = { ");
	for (i=0; i<num; i++) printf("%.2f ", setY[i]);
	printf("}\n");

	averageY = GetAverage(setY, num);
	printf("average = %.2f\n", averageY);
	variance = GetVariance(setY, num, averageY);
	printf("variance = %.2f\n", variance);
	sdY = GetStandardDeviation(variance);
	printf("standard deviation = %.2f\n", sdY);

	printf("\n");

	covariance = GetCoVariance(setX, setY, num, averageX, averageY);
	printf("covariance = %.2f\n", covariance);

	pcc = GetPCC(covariance, sdX, sdY);
	printf("Pearson Correlation Coefficient = %.2f\n", pcc);
}


