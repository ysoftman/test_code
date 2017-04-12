////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Hanoi Tower 문제 풀이
// 3개의 탑(A, B, C)이 있고 A탑의 원반을 C탑으로 옮긴다.
// 단, 한번에 한개의 원반을 옮길수 있고, 항상 큰 원반위에 작은 원반이 와야한다.
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
	int number;	// 원판의 개수
	
	printf("\nInput Number To Move :  ");
	scanf("%d", &number);

	//MoveTower1('A', 'B', 'C', number);
	MoveTower('A', 'B', 'C', number);
}

