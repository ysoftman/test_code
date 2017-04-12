////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Carmichael Numbers
// �־��� ���� ī����Ŭ ������ �ƴ��� �Ǻ�
// �丣�� �׽�Ʈ�� �Ҽ�����  �Ǻ�(���� �� �׽�Ʈ�� ����ϸ� �Ҽ���� �Ѵ�.->�׻� ���� �ƴϴ�.)
// ������ �Ҽ��ε��� �� �丣�� �׽�Ʈ�� ����ϴ� ���� ī����Ŭ ����� �Ѵ�.
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
	// a^b (mod n), a < n �̶�� ����
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

// �丣�� �׽�Ʈ -> �����ӵ��� �Ҽ� ���� �Ǵ��ϴ� Ȯ���� �Ҽ� �׽�Ʈ ���
// a>=2, a<=n-1 �� ���� 
// a^n (mod m) = a �� ���� �ϸ� n�� �Ҽ��� ���ɼ��� ����
int FermaTest(int a, int n)
{
	return (PowMod(a, n, n) == (unsigned long)a);
}

void main()
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
}

