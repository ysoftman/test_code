////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// int -> string, string -> int �� ��ȯ�ϱ�
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string>
#include <sstream>


int main()
{
	int num = 0;
	
	// Numeric Type (int, float, double)�� string���� ��ȯ���ֱ� ���� ��ü
	std::ostringstream ostr;

	for (num=1; num<=10; num++)
	{
		// �ʱ�ȭ
		ostr.str("");
		// int�� string���� ��ȯ
		ostr << num;
		printf("[int -> string] ostr = %s\n", ostr.str().c_str());
	}

	std::string str = "12345";
	num = atoi(str.c_str());
	printf("[string -> int] num = %d\n", num);

	return 0;
}


