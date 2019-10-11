// ysoftman
// GCD(greatest common divisor) 최대 공약수 구하기
#include <stdio.h>

int GCD(int m, int n);

int main()
{
	int num1;
	int num2;
	int gcd;

	printf("Input Number 1 : ");
	scanf("%d", &num1);
	printf("\nInput Number 2 : ");
	scanf("%d", &num2);

	gcd = GCD(num1, num2);
	printf("\n\n\nGreatest Common Divisor is :   %d\n", gcd);

	return 0;
}

//재귀함수를 이용한 최대공약수 구하기
/*
ex)
m = 10
n = 15
10 5 ...  5 10%5
5  0 ...  5

m = 8
n = 2
8 2 ... 2 8%2
2 0 ... 2

m = 18
n = 12
18 12 ... 12 18%12
12 6 ... 6  12%6
6  0 ...  6
*/
int GCD(int m, int n)
{
	if (n == 0)
		//나머지 0이면 m이 최대공약수
		return m;
	else
	{
		printf("\n[divisor-> %5d \t remainder-> %5d]", n, m % n);
		//나머지가 0이 아니면
		//m/n의 나머지가  n값으로 대체되어 재귀(자신 함수 호출)
		return GCD(n, m % n);
	}
}
