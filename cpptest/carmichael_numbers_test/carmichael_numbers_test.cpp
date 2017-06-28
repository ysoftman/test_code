////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Carmichael Numbers
// 주어진 수가 카마이클 수인지 아닌지 판별
// 페르마 테스트는 소수인지  판별(보통 이 테스트를 통과하면 소수라고 한다.->항상 참은 아니다.)
// 하지만 소수인데도 이 페르마 테스트를 통과하는 수를 카마이클 수라고 한다.
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

#define MAX		65000

static char Carmichael[MAX];

void CheckPrime()
{
	int i;
	int j;

	for (i=2; i<MAX; i++)
	{
		if (Carmichael[i] == 0)
		{
			Carmichael[i] = 2;
			for (j=i*2; j<MAX; j+=i)
			{
				Carmichael[j] = 1;
			}
		}
	}
}

unsigned long PowMod(unsigned long a, int b, int n)
{
	// a^b (mod n), a < n 이라고 가정
	unsigned long temp;

	if (b == 0)
	{
		return 1;
	}
	if (b == 1)
	{
		return a;
	}


	if (b%2)
	{
		return (PowMod(a, b-1, n) * a) % n;
	}
	else
	{
		temp = PowMod(a, b/2, n);
		return (temp*temp) % n;
	}
}

// 페르마 테스트 -> 빠른속도로 소수 여부 판단하는 확률적 소수 테스트 방법
// a>=2, a<=n-1 의 난수 
// a^n (mod m) = a 를 만족 하면 n은 소수일 가능성이 높다
int FermaTest(int a, int n)
{
	return (PowMod(a, n, n) == (unsigned long)a);
}

int main()
{
	int i;
	int j;
	int n;

	CheckPrime();

	for (i=3; i<MAX; i++)
	{
		if (Carmichael[i] == 1)
		{
			for (j=2; j<i; j++)
			{
				if (!FermaTest(j, i))
				{
					Carmichael[i] = 0;
					break;
				}
			}
		}
		else
		{
			Carmichael[i] = 0;
		}
	}

	printf("Find Carmichael Number in 1~65000...\n");

	for (n=1; n<MAX; n++)
	{
		if (Carmichael[n] == 1)
		{
			printf("%d is a Carmichael Number...\n", n);
		}
	}
	return 0;
}

