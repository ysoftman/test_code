////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// itoa() �����
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

void main()
{
	int Value = 1037626467;

	char Result[20] = {0,};
	char Temp[20] = {0,};

	int i=0;
	int j=0;
	while (Value/(int)10 > 0)
	{
		// 10 ���� ���� �������� ���
		// ����Ҷ� ASCII �ڵ� ������ ǥ���ѱ� ���ؼ� 0(48) ���� ���ؼ� �����Ѵ�.
		Temp[i] = (Value % (int)10) + '0';
		i++;
		// 10���� ���� �ڸ� ���� �ٿ�������.
		Value = Value / (int)10;
	}

	// ���ڸ� ���� �׷��� ����Ѵ�.
	Temp[i] = Value + '0';
	
	// ��ϵ� ������ �Ųٷ� �����Ѵ�.
	for (; i>=0; i--)
	{
		Result[j] = Temp[i];
		j++;
	}

	Result[j] = '\0';

	fprintf(stdout, "result = %s\n", Result);
}

