////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ���μ�(argument) �� ���μ�(parameter) ����
// �μ��� ���� �� �� �����ؼ� ����ؾ� �Ѵ�.
// ȣ���ϴ� ��, �������� �־����� ������ ���μ� �� argument ��� ���� ����.
// �ݸ� ȣ��޴� ��, ���� �޴� ������ parameter ��� ���� ����Ѵ�.
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a �� parameter
void func(int a)
{
	printf("%d", a);
}

int main()
{
	// 10 �� argument
	func(10);
	return 0;
}
