// ysoftman
// 부동소수점은 2진수로 바꾸어 계산하는데 이 과정에서 오차가 발생한다.
// float 보다는 double 이 크기 때문에 오차가 적다.
// 하지만 double 도 아주 정밀하게 들어가면 오차가 여전히 발생한다.
// 때문에 아주 정밀한 계산이 필요할 때는 새로운 타입을 생성해야 한다.
// 만약 그냥 float 나 double 을 사용할 경우 항상 오차범위를 고려해야 한다.
#include <stdio.h>

int main()
{
	int i = 0;

	// float(4byte 실수표현) 타입을 사용할때
	float sum1 = 0;

	// 0.1을 10 번 더하면 1 이 될까?
	sum1 = 0;
	for (i = 0; i < 10; i++)
		sum1 += (float)0.1;
	printf("sum1 = %f\n", sum1);
	// 0.1을 100 번 더하면 10 이 될까?(오차 발생)
	sum1 = 0;
	for (i = 0; i < 100; i++)
		sum1 += (float)0.1;
	printf("sum1 = %f\n", sum1);
	// 0.1을 1000 번 더하면 100 이 될까?(오차 발생)
	sum1 = 0;
	for (i = 0; i < 1000; i++)
		sum1 += (float)0.1;
	printf("sum1 = %f\n", sum1);

	// double(8byte 실수표현) 타입을 사용할때
	double sum2 = 0;

	// 0.1을 10 번 더하면 1 이 될까?
	sum2 = 0;
	for (i = 0; i < 10; i++)
		sum2 += 0.1;
	printf("sum2 = %f\n", sum2);
	// 0.1을 100 번 더하면 10 이 될까?
	sum2 = 0;
	for (i = 0; i < 100; i++)
		sum2 += 0.1;
	printf("sum2 = %f\n", sum2);
	// 0.1을 1000 번 더하면 100 이 될까?
	sum2 = 0;
	for (i = 0; i < 1000; i++)
		sum2 += 0.1;
	printf("sum2 = %f\n", sum2);
	// 0.1을 10000 번 더하면 1000 이 될까?
	sum2 = 0;
	for (i = 0; i < 10000; i++)
		sum2 += 0.1;
	printf("sum2 = %f\n", sum2);
	// 0.1을 100000 번 더하면 10000 이 될까?
	sum2 = 0;
	for (i = 0; i < 100000; i++)
		sum2 += 0.1;
	printf("sum2 = %f\n", sum2);
	// 0.1을 1000000 번 더하면 100000 이 될까?(오차발생)
	sum2 = 0;
	for (i = 0; i < 1000000; i++)
		sum2 += 0.1;
	printf("sum2 = %f\n", sum2);
	// 0.1을 10000000 번 더하면 1000000 이 될까?(오차발생)
	sum2 = 0;
	for (i = 0; i < 10000000; i++)
		sum2 += 0.1;
	printf("sum2 = %f\n", sum2);

	return 0;
}
