// ysoftman
// 통계 값 계산
#include <math.h>
#include <stdio.h>

float GetAverage(float *set, int num) {
    float average = 0.0;
    int i = 0;
    for (i = 0; i < num; i++) {
        average += set[i];
    }
    // 평균 (average) : 수들의 총합을 개수로 나눈 수
    average = float(average / num);
    return average;
}

float GetVariance(float *set, int num, float average) {
    float deviation = 0.0;
    float variance = 0.0;
    int i = 0;
    for (i = 0; i < num; i++) {
        // 편차(deviation) : 평균에서 각각의 수가 떨어진 정도
        deviation = set[i] - average;
        printf("deviation set[%d] = %.2f\n", i, deviation);

        variance += deviation * deviation;
    }
    // 분산(variance) : 편차의 제곱들의 합을 개수로 나눈 수
    variance = float(variance / num);
    return variance;
}

float GetStandardDeviation(float variance) {
    float sd = 0.0;
    // 표준편차(standard deviation) : 분산의 제곱근
    sd = sqrt(variance);
    return sd;
}

float GetCoVariance(float *setX, float *setY, int num, float averageX, float averageY) {
    float deviation = 0.0;
    float covariance = 0.0;
    int i = 0;
    for (i = 0; i < num; i++) {
        covariance += (setX[i] - averageX) * (setY[i] - averageY);
    }
    // 공분산(covariance) : setX와 setY의 편차곱들의 합을 개수로 나눈 수
    covariance = float(covariance / num);
    return covariance;
}

// PCC (Pearson Correlation Coefficient) 피어슨상관계수
// -1 <= PCC <= 1 사이의 값으로 상관 관계를 나타낸다.
// 1 에 가까울 수록 같은 방향의 상관성을 나타낸다.
// -1 에 가까울 수록 반대 방향의 상관성을 나타낸다.
// 0 에 가까울 수록 상관성이 없음을 나타낸다.
float GetPCC(float covariance, float sdX, float sdY) {
    float pcc = 0.0;
    // 피어슨 상관계수(Pearson Correlation Coefficient) : 공분산을 setX와 setY의 표준편차의 곱으로
    // 나눈 수
    pcc = covariance / (sdX * sdY);
    return pcc;
}

int main() {
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
    for (i = 0; i < num; i++) printf("%.2f ", setX[i]);
    printf("}\n");

    averageX = GetAverage(setX, num);
    printf("average = %.2f\n", averageX);
    variance = GetVariance(setX, num, averageX);
    printf("variance = %.2f\n", variance);
    sdX = GetStandardDeviation(variance);
    printf("standard deviation = %.2f\n", sdX);

    printf("\n");

    printf("setY = { ");
    for (i = 0; i < num; i++) printf("%.2f ", setY[i]);
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

    return 0;
}
