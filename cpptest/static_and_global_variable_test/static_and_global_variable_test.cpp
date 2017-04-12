////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// static �� �������� ����
// �Ѵ� ���α׷��� ���۵Ǹ� �����ǰ� ���α׷��� ����� ������ �����Ǵ� lifetime �� ����
// ������ static �� �ڽ��� ����� scope(��, �Լ�, ����...) �������� ���� �����ϴ�.
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

extern int nVar3;
extern int nVar4;

int nVar1 = 0;

void func1()
{
	static int nVar2 = 0;
	printf("nVar2 = %d\n", ++nVar2);
}

int main()
{
	for (int i=0; i<5; ++i)
	{
		printf("nVar1 = %d\n", ++nVar1);
		func1();
	}
	printf("extern int nVar3 = %d\n", nVar3);
	//printf("extern int nVar4 = %d\n", nVar4);	// ��Ÿ�� ���� - �ܺ��� static �� ������ �� ����.
	return 0;
}

