////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// GCD(greatest common divisor) �ִ� ����� ���ϱ�
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

int GCD(int m, int n);

void main()
{
	int num1;
	int num2;
	
	int gcd;

	printf ("Input Number 1 : ");
	scanf ("%d", &num1);
	printf ("\nInput Number 2 : ");
	scanf ("%d", &num2);
	
	gcd = GCD (num1, num2);
	printf ("\n\n\nGreatest Common Divisor is :   %d\n", gcd);

}

//����Լ��� �̿��� �ִ����� ���ϱ�
int GCD(int m, int n)
{
	if (n == 0)
		//������ 0�̸� m�� �ִ�����
		return m;
	else {
		printf("\n[divisor-> %5d \t remainder-> %5d]", n, m%n);
		//�������� 0�� �ƴϸ�
		//m/n�� ��������  n������ ��ü�Ǿ� ���(�ڽ� �Լ� ȣ��)
		return GCD(n, m%n);
	}
}

