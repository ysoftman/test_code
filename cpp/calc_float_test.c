/*
ysoftman
소수점이 있는 실수는 2진수로 바꾸는 과정에서 오차가 발생한다.
오차 발생 원인은 실수를 저장할때 (IEEE 표준) 부동(뜰 부, 움질일 동)소수점방식으로
메모리에 저장하게 되는데 소수점 아래는 2진수로 정확히 표현할 수 없기 때문이다.
예) 10.1
정수부분:10 -> 2진수 -> 1010 로 문제없이 계산 할 수 있다.
2  10
2   5 - 0
2   2 - 1
    1 - 0

소수점이하 부분 0.1  -> 2진수 -> 0.001100110011... 으로 문제가 된다.
0.1 * 2 = 0.4 - 정수부분 0
0.4 * 2 = 0.8 - 정수부분 0
0.8 * 2 = 1.6 - 정수부분 1
0.6 * 2 = 1.2 - 정수부분 1
0.2 * 2 = 0.4 - 정수부분 0
0.4 * 2 = 0.8 - 정수부분 0
0.8 * 2 = 1.6 - 정수부분 1
0.6 * 2 = 1.2 - 정수부분 1
... 무한 반복

참고로
0.5, 0.625 등은 무한 반복되지 않아 제대로 2진수 표현이 가능해서 문제 없다.
0.5 * 2 = 1.0 - 1
끝
0.5 = 0.1
0.01 10진수로 바꾸면: 1*2^-1 = 1*0.5 = 0.5

0.0625 * 2 = 0.125 - 정수부분 0
0.125 * 2 = 0.25 - 정수부분 0
0.25 * 2 = 0.5 - 정수부분 0
0.5 * 2 = 1.0 - 정수부분 1
끝
0.0625 = 0.0001
0.0001 10진수로 바꾸면: 0*2^-1 + 0*2^-2 + 0*2^-3 + 0*2^-4
= 0*0.5 + 0*0.25 + 0*0.125 + 1*0.0625 = 0.0625

float 보다는 double 이 크기 때문에 오차가 적다.
하지만 double 도 아주 정밀하게 들어가면 오차가 여전히 발생한다.
때문에 아주 정밀한 계산이 필요할 때는 새로운 타입을 생성해야 한다.
만약 그냥 float 나 double 을 사용할 경우 항상 오차범위를 고려해야 한다.
*/

#include <stdio.h>

int main()
{
	int i = 0;

	// float(4byte 실수표현) 타입을 사용할때
	float floatSum = 0;

	// 0.1을 10 번 더하면 1 이 될까?
	floatSum = 0;
	for (i = 0; i < 10; i++)
		floatSum += (float)0.1;
	printf("0.1 += ... floatSum = %f\n", floatSum);
	// 0.1을 100 번 더하면 10 이 될까?(오차 발생)
	floatSum = 0;
	for (i = 0; i < 100; i++)
		floatSum += (float)0.1;
	printf("0.1 += ... floatSum = %f\n", floatSum);
	// 0.1을 1000 번 더하면 100 이 될까?(오차 발생)
	floatSum = 0;
	for (i = 0; i < 1000; i++)
		floatSum += (float)0.1;
	printf("0.1 += ... floatSum = %f\n", floatSum);

	// double(8byte 실수표현) 타입을 사용할때
	double doubleSum = 0;

	// 0.1을 10 번 더하면 1 이 될까?
	doubleSum = 0;
	for (i = 0; i < 10; i++)
		doubleSum += 0.1;
	printf("0.1 += ... doubleSum = %f\n", doubleSum);
	// 0.1을 100 번 더하면 10 이 될까?
	doubleSum = 0;
	for (i = 0; i < 100; i++)
		doubleSum += 0.1;
	printf("0.1 += ... doubleSum = %f\n", doubleSum);
	// 0.1을 1000 번 더하면 100 이 될까?
	doubleSum = 0;
	for (i = 0; i < 1000; i++)
		doubleSum += 0.1;
	printf("0.1 += ... doubleSum = %f\n", doubleSum);
	// 0.1을 10000 번 더하면 1000 이 될까?
	doubleSum = 0;
	for (i = 0; i < 10000; i++)
		doubleSum += 0.1;
	printf("0.1 += ... doubleSum = %f\n", doubleSum);
	// 0.1을 100000 번 더하면 10000 이 될까?
	doubleSum = 0;
	for (i = 0; i < 100000; i++)
		doubleSum += 0.1;
	printf("0.1 += ... doubleSum = %f\n", doubleSum);
	// 0.1을 1000000 번 더하면 100000 이 될까?(오차발생)
	doubleSum = 0;
	for (i = 0; i < 1000000; i++)
		doubleSum += 0.1;
	printf("0.1 += ... doubleSum = %f\n", doubleSum);
	// 0.1을 10000000 번 더하면 1000000 이 될까?(오차발생)
	doubleSum = 0;
	for (i = 0; i < 10000000; i++)
		doubleSum += 0.1;
	printf("0.1 += ... doubleSum = %f\n", doubleSum);

	// 0.5을 10000000 번 더하면 1000000 이 될까?(0.5는 오차 없이 된다.)
	doubleSum = 0;
	for (i = 0; i < 20000000; i++)
		doubleSum += 0.5;
	printf("0.5 += ... doubleSum = %f\n", doubleSum);

	return 0;
}
