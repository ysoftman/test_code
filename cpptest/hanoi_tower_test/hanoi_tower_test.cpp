////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Hanoi Tower ���� Ǯ��
// 3���� ž(A, B, C)�� �ְ� Až�� ������ Cž���� �ű��.
// ��, �ѹ��� �Ѱ��� ������ �ű�� �ְ�, �׻� ū �������� ���� ������ �;��Ѵ�.
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

void MoveTower(char a, char b, char c, int n)
{
	if (n == 1)
		printf("\nMove %c To %c", a, c);
	else
	{
		MoveTower(a, c, b, n-1);
		printf("\nMove %c To %c", a, c);
		MoveTower(b, a, c, n-1);
	}
}

void main()
{
	int number;	// ������ ����
	
	printf("\nInput Number To Move :  ");
	scanf("%d", &number);

	//MoveTower1('A', 'B', 'C', number);
	MoveTower('A', 'B', 'C', number);
}

