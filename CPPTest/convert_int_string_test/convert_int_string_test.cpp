////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// int -> string, string -> int 로 변환하기
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string>
#include <sstream>


int main()
{
	int num = 0;
	
	// Numeric Type (int, float, double)을 string으로 변환해주기 위한 객체
	std::ostringstream ostr;

	for (num=1; num<=10; num++)
	{
		// 초기화
		ostr.str("");
		// int를 string으로 변환
		ostr << num;
		printf("[int -> string] ostr = %s\n", ostr.str().c_str());
	}

	std::string str = "12345";
	num = atoi(str.c_str());
	printf("[string -> int] num = %d\n", num);

	return 0;
}


